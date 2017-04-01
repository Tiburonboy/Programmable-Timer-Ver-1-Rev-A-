/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15
        Device            :  PIC16F18855
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SQW aliases
#define SQW_TRIS               TRISAbits.TRISA0
#define SQW_LAT                LATAbits.LATA0
#define SQW_PORT               PORTAbits.RA0
#define SQW_WPU                WPUAbits.WPUA0
#define SQW_OD                ODCONAbits.ODCA0
#define SQW_ANS                ANSELAbits.ANSA0
#define SQW_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define SQW_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define SQW_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define SQW_GetValue()           PORTAbits.RA0
#define SQW_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define SQW_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define SQW_SetPullup()      do { WPUAbits.WPUA0 = 1; } while(0)
#define SQW_ResetPullup()    do { WPUAbits.WPUA0 = 0; } while(0)
#define SQW_SetPushPull()    do { ODCONAbits.ODCA0 = 1; } while(0)
#define SQW_SetOpenDrain()   do { ODCONAbits.ODCA0 = 0; } while(0)
#define SQW_SetAnalogMode()  do { ANSELAbits.ANSA0 = 1; } while(0)
#define SQW_SetDigitalMode() do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set RELAY aliases
#define RELAY_TRIS               TRISBbits.TRISB5
#define RELAY_LAT                LATBbits.LATB5
#define RELAY_PORT               PORTBbits.RB5
#define RELAY_WPU                WPUBbits.WPUB5
#define RELAY_OD                ODCONBbits.ODCB5
#define RELAY_ANS                ANSELBbits.ANSB5
#define RELAY_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RELAY_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RELAY_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RELAY_GetValue()           PORTBbits.RB5
#define RELAY_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RELAY_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RELAY_SetPullup()      do { WPUBbits.WPUB5 = 1; } while(0)
#define RELAY_ResetPullup()    do { WPUBbits.WPUB5 = 0; } while(0)
#define RELAY_SetPushPull()    do { ODCONBbits.ODCB5 = 1; } while(0)
#define RELAY_SetOpenDrain()   do { ODCONBbits.ODCB5 = 0; } while(0)
#define RELAY_SetAnalogMode()  do { ANSELBbits.ANSB5 = 1; } while(0)
#define RELAY_SetDigitalMode() do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set RC0 procedures
#define RC0_SetHigh()    do { LATCbits.LATC0 = 1; } while(0)
#define RC0_SetLow()   do { LATCbits.LATC0 = 0; } while(0)
#define RC0_Toggle()   do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define RC0_GetValue()         PORTCbits.RC0
#define RC0_SetDigitalInput()   do { TRISCbits.TRISC0 = 1; } while(0)
#define RC0_SetDigitalOutput()  do { TRISCbits.TRISC0 = 0; } while(0)
#define RC0_SetPullup()     do { WPUCbits.WPUC0 = 1; } while(0)
#define RC0_ResetPullup()   do { WPUCbits.WPUC0 = 0; } while(0)
#define RC0_SetAnalogMode() do { ANSELCbits.ANSC0 = 1; } while(0)
#define RC0_SetDigitalMode()do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set LED_blue aliases
#define LED_blue_TRIS               TRISCbits.TRISC1
#define LED_blue_LAT                LATCbits.LATC1
#define LED_blue_PORT               PORTCbits.RC1
#define LED_blue_WPU                WPUCbits.WPUC1
#define LED_blue_OD                ODCONCbits.ODCC1
#define LED_blue_ANS                ANSELCbits.ANSC1
#define LED_blue_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define LED_blue_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define LED_blue_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define LED_blue_GetValue()           PORTCbits.RC1
#define LED_blue_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define LED_blue_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define LED_blue_SetPullup()      do { WPUCbits.WPUC1 = 1; } while(0)
#define LED_blue_ResetPullup()    do { WPUCbits.WPUC1 = 0; } while(0)
#define LED_blue_SetPushPull()    do { ODCONCbits.ODCC1 = 1; } while(0)
#define LED_blue_SetOpenDrain()   do { ODCONCbits.ODCC1 = 0; } while(0)
#define LED_blue_SetAnalogMode()  do { ANSELCbits.ANSC1 = 1; } while(0)
#define LED_blue_SetDigitalMode() do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set SCL aliases
#define SCL_TRIS               TRISCbits.TRISC3
#define SCL_LAT                LATCbits.LATC3
#define SCL_PORT               PORTCbits.RC3
#define SCL_WPU                WPUCbits.WPUC3
#define SCL_OD                ODCONCbits.ODCC3
#define SCL_ANS                ANSELCbits.ANSC3
#define SCL_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SCL_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SCL_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SCL_GetValue()           PORTCbits.RC3
#define SCL_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SCL_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SCL_SetPullup()      do { WPUCbits.WPUC3 = 1; } while(0)
#define SCL_ResetPullup()    do { WPUCbits.WPUC3 = 0; } while(0)
#define SCL_SetPushPull()    do { ODCONCbits.ODCC3 = 1; } while(0)
#define SCL_SetOpenDrain()   do { ODCONCbits.ODCC3 = 0; } while(0)
#define SCL_SetAnalogMode()  do { ANSELCbits.ANSC3 = 1; } while(0)
#define SCL_SetDigitalMode() do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set SDA aliases
#define SDA_TRIS               TRISCbits.TRISC4
#define SDA_LAT                LATCbits.LATC4
#define SDA_PORT               PORTCbits.RC4
#define SDA_WPU                WPUCbits.WPUC4
#define SDA_OD                ODCONCbits.ODCC4
#define SDA_ANS                ANSELCbits.ANSC4
#define SDA_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SDA_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SDA_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SDA_GetValue()           PORTCbits.RC4
#define SDA_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SDA_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define SDA_SetPullup()      do { WPUCbits.WPUC4 = 1; } while(0)
#define SDA_ResetPullup()    do { WPUCbits.WPUC4 = 0; } while(0)
#define SDA_SetPushPull()    do { ODCONCbits.ODCC4 = 1; } while(0)
#define SDA_SetOpenDrain()   do { ODCONCbits.ODCC4 = 0; } while(0)
#define SDA_SetAnalogMode()  do { ANSELCbits.ANSC4 = 1; } while(0)
#define SDA_SetDigitalMode() do { ANSELCbits.ANSC4 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/