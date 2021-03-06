/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F1825
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set TEMP aliases
#define TEMP_TRIS                 TRISAbits.TRISA0
#define TEMP_LAT                  LATAbits.LATA0
#define TEMP_PORT                 PORTAbits.RA0
#define TEMP_WPU                  WPUAbits.WPUA0
#define TEMP_ANS                  ANSELAbits.ANSA0
#define TEMP_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define TEMP_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define TEMP_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define TEMP_GetValue()           PORTAbits.RA0
#define TEMP_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define TEMP_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define TEMP_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define TEMP_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define TEMP_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define TEMP_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set CURRENT aliases
#define CURRENT_TRIS                 TRISAbits.TRISA1
#define CURRENT_LAT                  LATAbits.LATA1
#define CURRENT_PORT                 PORTAbits.RA1
#define CURRENT_WPU                  WPUAbits.WPUA1
#define CURRENT_ANS                  ANSELAbits.ANSA1
#define CURRENT_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define CURRENT_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define CURRENT_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define CURRENT_GetValue()           PORTAbits.RA1
#define CURRENT_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define CURRENT_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define CURRENT_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define CURRENT_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define CURRENT_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define CURRENT_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set RELAY aliases
#define RELAY_TRIS                 TRISCbits.TRISC3
#define RELAY_LAT                  LATCbits.LATC3
#define RELAY_PORT                 PORTCbits.RC3
#define RELAY_WPU                  WPUCbits.WPUC3
#define RELAY_ANS                  ANSELCbits.ANSC3
#define RELAY_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RELAY_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RELAY_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RELAY_GetValue()           PORTCbits.RC3
#define RELAY_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RELAY_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RELAY_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define RELAY_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define RELAY_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define RELAY_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

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