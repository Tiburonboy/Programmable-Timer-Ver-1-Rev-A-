/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15
        Device            :  PIC16F18855
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*/

#include "mcc_generated_files/mcc.h"

/*
Main application
Programmable Timer V2
Code to bit bang SDA and SCL lines
Hardware configuration: PIC16F18855
MCU configuration
Pin: function: connection
1: Vpp/MCLR/RE3: ICSP 1
2: RA0: SQW
3: RA1:
4: RA2:
5: RA3:
6: RA4: NC
7: RA5: NC
8: Vss: ground
9: RA7: NC
10: RA6: NC
11: RC0: NCO, 2KHz to Buzzer
12: RC1: LED, blue
13: RC2: TMR0 output test point
14: RC3: SCK

15: RC4: SDA
16: RC5: NC
17: RC6: NC
18: RC7: NC
19: Vss: ground
20: Vdd: +5VDC
21: RB0: this pin always seems to be low when configured as an input
22: RB1: NC
23: RB2: NC
24: RB3: NC 
25: RB4: NC
26: RB5: NC
27: RB6: ICSPCLK: ICSP 5
28: RB7: ICSPDAT: ICSP 4 

Author: Tony Cirineo
Date: 12/18/2016 coding started
Revision History
Original version:   
 */

//defines 
typedef unsigned char byte;
typedef unsigned int word;
#define DS1307_ADDRESS 0x68
#define BUZZER  NCO1CONbits.N1EN
#define buzzer_on()    NCO1CONbits.N1EN = 1
#define buzzer_off()    NCO1CONbits.N1EN = 0
#define BUZZER  NCO1CONbits.N1EN

byte decToBcd(byte val);
byte bcdToDec(byte val);
void set_time_date(void);
void get_time_date(void);

void write_ds1307(byte wdr_addrs, byte *ptr, byte len);
void read_ds1307(byte wrd_addrs, byte *ptr, byte len);

byte i2c_read(void);
void i2c_write(byte output_data);
void i2c_stop(void);
void i2c_start(void);
void delay_100us(void);
void delay_10us(void);

// I/O pins used in the design
byte r_flg, s_flg;  // used to keep track of the phase of the SQW 1Hz signal
byte relay_on_flg;
byte second;
byte minute;
byte hour; 		// 24 hour time
byte weekDay; 	// 1-7 = Sunday - Saturday
byte monthDay;
byte month;
byte year;
byte rtc_config;
byte pData[60]; //actually only 56 bytes in the DS1307 address space

unsigned int millis, seconds; 
byte buzzer_flg, LED_blue_flg;

void main(void)
{
byte i;
    // initialize the device
    SYSTEM_Initialize();
    BUZZER = 0;         // deactive buzzer
    RELAY_LAT = LOW;    //deactivate relay
    millis = seconds = 0; 
    buzzer_flg = LED_blue_flg = 0;

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
 
    //I2C initialization
    // set the SDA line low and use TRIS to control the state
    SDA_SetLow();
    SDA_SetDigitalInput();  //SDA is Hi Z

    // set the SCL line as an output
    SCL_SetDigitalOutput();   
    SCL_SetHigh();
    SQW_SetDigitalInput();

    // Create a start condition followed by a stop condition	
	i2c_start();
	i2c_stop();	

    //set_time_date();    //comment out after running once to set the time

    while (1)
    {
        // check for a new 1Hz rising edge        
        if(SQW_GetValue() && !s_flg)
            r_flg = 1;
        if(!SQW_GetValue() && !r_flg)
            s_flg = 0;

        // check millis and update seconds
        if(r_flg){
            seconds++;
            millis = 0;
            LED_blue_flg = 1; 
            LED_blue_SetLow();
            s_flg = 1;
            r_flg = 0;
        }        
        
        // read time and date every 10 seconds
        if(seconds > 9){
            seconds = 0;
            get_time_date();

            // check day of week, hour and min
            if((hour == 10) && (minute == 0) && ((weekDay == 2) || (weekDay == 4) || (weekDay == 6)) && !relay_on_flg){
                relay_on_flg = 1;
                // activate buzzer
                buzzer_flg = 1;
                buzzer_on();
            }
            if((hour == 10) && (minute == 15) && ((weekDay == 2) || (weekDay == 4) || (weekDay == 6)) && relay_on_flg){
                relay_on_flg = 0;
                // activate buzzer
                buzzer_flg = 1;
                buzzer_on();               
            }
        }

        // control relay
        if(relay_on_flg)
            RELAY_LAT = HIGH; // energize relay
        else
            RELAY_LAT = LOW;  //deactivate relay

        // control LED
        if((millis > 25) && LED_blue_flg){
            LED_blue_SetHigh();
            LED_blue_flg = 0; 
        }

        // control buzzer
        if((millis > 100) && (millis <= 199) && buzzer_flg){
            buzzer_off();
        }
         if((millis > 200) && (millis <= 299) && buzzer_flg){
            buzzer_on();
        }       
        if((millis > 300) && (millis <= 399) && buzzer_flg){
            buzzer_off();
        } 
        if((millis > 400) && (millis <= 499) && buzzer_flg){
            buzzer_on();
        } 
        if((millis > 500) && buzzer_flg){
            buzzer_off();
            buzzer_flg = 0;
        }
    }
}

/************************************
*       get time and date           *
************************************/
/*
Name: get time and date
Synopsis:
Requires: na
Description:
Author: Tony Cirineo
Date:
Revision History:

*/
void get_time_date(void)
{
byte dev_addrs;
byte i;

  read_ds1307(0, pData, 8);

  second = bcdToDec(pData[0]);
  minute = bcdToDec(pData[1]);
  hour = bcdToDec(pData[2] & 0b111111); //24 hour time
  weekDay = bcdToDec(pData[3]); //0-6 -> Sunday - Saturday
  monthDay = bcdToDec(pData[4]);
  month = bcdToDec(pData[5]);
  year = bcdToDec(pData[6]);
  rtc_config = pData[7];
}

/************************************
*       set time and date           *
************************************/
/*
Name: get time and date
Synopsis:
Requires: na
Description:
Author: Tony Cirineo
Date:
Revision History:

*/
void set_time_date(void)
{
byte dev_addrs;
byte i;

    // put formated data into array for sending
    // set values for clock
    second =      0; //0-59, this also set the CH bit to zero = osc runs
    minute =      14; //0-59
    hour =        18; //0-23
    weekDay =     3; //1-7
    monthDay =    10; //1-31
    month =       1; //1-12
    year  =       17; //0-99
    rtc_config = 0x10; //turn on SQW 1Hz    
    
    pData[0] = decToBcd(second);
    pData[1] = decToBcd(minute);
    pData[2] = decToBcd(hour);
    pData[3] = decToBcd(weekDay);
    pData[4] = decToBcd(monthDay);
    pData[5] = decToBcd(month);
    pData[6] = decToBcd(year);
    pData[7] = rtc_config;    
    
    write_ds1307(0, pData, 8);
}

/************************************
*      Dec & BCD Conversions        *
************************************/
/*
Name: 
Synopsis: 
Requires:
Description: 
Author: Tony Cirineo
Date:  8/5/03
Revision History:
*/
byte decToBcd(byte val){
// Convert normal decimal numbers to binary coded decimal
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val)  {
// Convert binary coded decimal to normal decimal numbers
  return ( (val/16*10) + (val%16) );
}

/************************************
*       write ds1307                *
************************************/
/*
Name: write ds1307
Synopsis: writes data to the DS1307 real time clock
Requires: 
wrd_addrs:  word address or register pointer 
*ptr: pointer to list of data
len: length of data list to send
pointer to data and number of bytes to write
Description:
Author: Tony Cirineo
Date:
Revision History:
*/
void write_ds1307(byte wrd_addrs, byte *ptr, byte len)
{
byte dev_addrs;
byte i;

	// build device address
	dev_addrs = DS1307_ADDRESS << 1;    // leave R/W bit as a zero

	// write device address, word address, then len bytes of data
	i2c_start();
	i2c_write(dev_addrs);	// device address
	i2c_write(wrd_addrs);	// word address
	for(i = 0;i < len;i++)
		i2c_write(*ptr++);
	i2c_stop();	// create a stop condition
}

/************************************
*       read ds1307                 *
************************************/
/*
Name: data read ds1307
Synopsis: 
Data Read (Write Pointer, Then Read)—Slave Receive and Transmit

Requires: 
wrd_addrs:  word address or register pointer 
*ptr: pointer to list of data
len: length of data list to send
pointer to data and number of bytes to write
Description:
Author: Tony Cirineo
Date:
Revision History:
*/
void read_ds1307(byte wdr_addrs, byte *ptr, byte len)
{
byte dev_addrs;
byte i,j,input_data;

	// write device address, then word address followed by repeated start
	dev_addrs = DS1307_ADDRESS << 1;    //leave w/r set to 0
	i2c_start();
	i2c_write(dev_addrs);	// device address
	i2c_write(wdr_addrs);	// word address
	i2c_start();	// send start condition

    // read the data from the device
	dev_addrs |= 0x01;      //set the w/r bit to 1 for read
	i2c_write(dev_addrs);	// device address   

    // read len-1 bytes of data followed by ACK
    SDA_SetDigitalInput();        	// set SDA pin as input
    delay_10us();
    for(i = 0;i < len-1;i++){
        input_data = 0x00;
        for(j = 0; j < 8; j++){	// read 8 bits from the I2C Bus
            input_data <<= 1;   // Shift the byte by one bit
            SCL_SetHigh();         // Clock the data into the I2C Bus
            delay_10us();
            input_data |= SDA_GetValue();  // Input the data from the I2C Bus
            delay_10us();
            SCL_SetLow();
            delay_10us();
        }
        // send ACK
        SDA_SetLow();    	// send ACK valid
        SDA_SetDigitalOutput();   // Put port pin to output   
        delay_10us();
        SCL_SetHigh();		// Clock the ACK from the I2C Bus
        delay_10us();
        SCL_SetLow();
        delay_10us();
        SDA_SetDigitalInput(); //return SDA to Hi Z	
        *ptr++ = input_data;        //save received data
    }
    
    // now read last byte of data followed by NACK
    input_data = 0x00;
    for(j = 0; j < 8; j++){	// read 8 bits from the I2C Bus
        input_data <<= 1;   // Shift the byte by one bit
        SCL_SetHigh();         // Clock the data into the I2C Bus
        delay_10us();
        input_data |= SDA_GetValue();  // Input the data from the I2C Bus
        delay_10us();
        SCL_SetLow();
        delay_10us();
    }
    // send NACK
    SDA_SetHigh();    	// send NACK valid
    SDA_SetDigitalOutput();   // Put port pin to output   
    delay_10us();
    SCL_SetHigh();		// Clock the ACK from the I2C Bus
    delay_10us();
    SCL_SetLow();
    delay_10us();
    SDA_SetDigitalInput(); //return SDA to Hi Z	  
    
    *ptr = input_data;        //save last received data    

	i2c_stop();	// create a stop condition
}

/************************************
*           delay_???us             *
************************************/
/*
Name: delay_???us
Synopsis: various fixed delays
Requires: na
Description: Delay used to allow data lines
to stabilize from the key fill device.
count vs delay
_nop(); 10us
1       20  us
14		100 us
Author: Tony Cirineo
Date:  
Revision History:
*/
void delay_10us(void)
{
    _nop();
}
void delay_100us(void)
{
word i;
    for(i = 0;i < 14;i++);	// loop for a small delay, 100 us
}

/************************************
*            i2c_start              *
************************************/
/*
Name: i2c_start
Synopsis: Sends I2C start condition.
Requires: na
Description: This function toggles the scl and sda
lines initiate the start condition
Author: Copied from the Keil Software web page with some changes
Date:  7/22/03
Revision History:
5/5/2015: updated
*/
void i2c_start(void)
{
    //SDA_SetHigh();     // Set data line high
    SDA_SetDigitalInput(); // let the pull up control the line
    delay_10us();
    SCL_SetHigh();     // Set clock line high
	delay_10us();
    //SDA_SetLow();      // Set data line low (START SIGNAL)
    SDA_SetDigitalOutput();
	delay_10us();
    SCL_SetLow();      // Set clock line low
	delay_10us();
}

/************************************
*            i2c_stop               *
************************************/
/*
Name: i2c_stop
Synopsis: Sends I2C Stop condition
Requires: na
Description: This function toggles the scl and sda
lines initiate the stop condition
Author: Copied from the Keil Software web page with some changes
Date:  7/22/03
Revision History:
5/5/2015: updated
*/
void i2c_stop(void)
{
byte input_var;

    SCL_SetLow();          // Set clock line low
    delay_10us();
    SDA_SetLow();          // Set data line low
    SDA_SetDigitalOutput(); // set SDA to output
	delay_10us();
    SCL_SetHigh();         // Set clock line high
	delay_10us();
    SDA_SetDigitalInput(); //release the line
	delay_10us();
}

/************************************
*            i2c_write              *
************************************/
/*
Name: i2c_write
Synopsis: Writes data over the I2C bus
Requires: na
Description: This function toggles the scl and sda
lines to write a byte of data. Clocks acknowledge (ACK)
but ignores it.  
Author: Copied from the Keil Software web page with some changes
Date:  7/22/03
Revision History:
*/
void i2c_write(byte output_data)
{
byte i;
    SDA_SetHigh();      //SDA line is normally pulled high
    SDA_SetDigitalOutput();  //set as output
    delay_10us();
    for(i = 0; i < 8; i++){	// Send 8 bits to the I2C Bus
        // Output the data bit to the I2C Bus
        SDA_LAT = ((output_data & 0x80) ? 1 : 0);
        delay_10us();
        output_data  <<= 1; // Shift the byte by one bit
        SCL_SetHigh();         // Clock the data into the I2C Bus
		delay_10us();
        SCL_SetLow();
        delay_10us();
    }
	// get the ACK & ignore
    SDA_SetDigitalInput();  	// release pin (open drain output)
	delay_10us();
    SCL_SetHigh();     // Clock the ACK from the I2C Bus
	delay_10us();
    SCL_SetLow();
	delay_10us();
    SDA_SetLow();   // leave SDA LAT as low and Hi Z
}

/************************************
*            i2c_read               *
************************************/
/*
Name: i2c_read
Synopsis: Reads data from the I2C bus
Requires: na
Description: This function toggles the scl and sda
lines to read data from the bus. Clocks acknowledge (ACK)
but ignores it.
Author: Copied from the Keil Software web page with some changes
Date:  7/22/03
Revision History:
5/5/2015: updated
*/
#if 0
byte i2c_read(void)
{
byte i, input_data;

    SDA_SetDigitalInput();        	// set pin as input
	delay_10us();

    input_data = 0x00;
    for(i = 0; i < 8; i++){	// read 8 bits from the I2C Bus
        input_data <<= 1;   // Shift the byte by one bit
        SCL_SetHigh();         // Clock the data into the I2C Bus
		delay_10us();
        input_data |= SDA_GetValue();  // Input the data from the I2C Bus
		delay_10us();
        SCL_SetLow();
		delay_10us();
    }
	// send ACK
    SDA_SetLow();    	// send ACK valid
    SDA_SetDigitalOutput();   // Put port pin to output   
	delay_10us();
    SCL_SetHigh();		// Clock the ACK from the I2C Bus
	delay_10us();
    SCL_SetLow();
	delay_10us();
    SDA_SetDigitalInput(); //return SDA to Hi Z	
    return input_data;
}
#endif
/*
 End of File
*/