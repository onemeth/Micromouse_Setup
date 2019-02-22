/********************************************************
 * Description                                
 *      File name   : main.c                           
 *      Project     : MicroMouse-Setup                
 *      Author(s)   : O.Nemeth                          
 *      Device      : MicroMouse                     
 *      Function    : General setup and config               
 ********************************************************
 * Change History                                      
 *      Released    : 17-01-2019                          
 *      Rev         : 1.1                                
 *      Alt A       : Pragma set up used     
 ********************************************************
 * Pin Assignments 
 * PIN NO:        FUNC:       ID:          DESC:               TESTED:                             
 *        Pin 19:      AN0       RX_LS          Left side RX          Y
 *        Pin 20:      AN1       RX_LF          Left front RX         Y
 *        Pin 21:      AN2       RX_LP          Left post RX          Y                   
 *        Pin 23:      QEA                      Encoder 1 A                     
 *        Pin 24:      QEB                      Encoder 1 B
 *        Pin 25:      AN6       RX_RP          Right post RX         Y
 *        Pin 26:      AN7       RX_RF          Right front RX        Y
 *        Pin 27:      AN8       RX_RS          Right side RX         Y
 *        Pin 32:      RC13      BUZZ           Buzzer switch         Y
 *        Pin 42:      RD0       BUTTON         Push button           Y
 *        Pin 37:      RD1       TX_S           Side TX switch        Y
 *        Pin 41:      RD2       TX_F           Front TX switch       Y
 *        Pin 38:      RD3       TX_P           Post TX switch        Y
 *        Pin 15:      PWM1L     PDC1           LH motor PWM          Y
 *        Pin 14:      RE1       MTR_LB         LH motor reverse      Y
 *        Pin 11:      PWM2L     PDC2           RH motor PWM          Y
 *        Pin 10:      RE3       MTR_LF         LH motor forward      Y
 *        Pin 9 :      PWM3L     PDC3           Buzzer                Y
 *        Pin 8 :      RE5       MTR_RF         RH motor forward      Y
 *        Pin 36:      QEB       MTR_RB         RH motor backwards    Y
 *                           
 ********************************************************/

/***** HEADER FILES *****/
#include <p30Fxxxx.h> 
#include <xc.h>                                      
#include "gpIO.h" 
#include "Timer1Functions.h"
#include "PWMfunctions.h"
#include "UARTfunctions.h"
#include "ADCfunctions.h"
#include "miscFunctions.h"
#include "QEIfunctions.h"

/***** CONFIGURATION BITS *****/
//primary oscillator with 8 times pll no clock switching
#pragma config FOS = PRI
#pragma config FPR = XT_PLL8
#pragma config FCKSMEN = CSW_FSCM_OFF
//watch dog is disabled
#pragma config WDT = WDT_OFF
//brown out disabled, master-clear enabled, power on reset time = 64ms
#pragma config BOREN = PBOR_OFF
#pragma config MCLRE = MCLR_EN
#pragma config FPWRT = PWRT_64
// pwm low side is active high, pwm high side is active low, 
//reset state controlled with HPOL/LPOL bits    
#pragma config LPOL = PWMxL_ACT_HI
#pragma config HPOL = PWMxH_ACT_LO
#pragma config PWMPIN = RST_PWMPIN

/***** MAIN *****/
int main(void){
    gpIOSetup();                       // Configures the IO
    pwmSetup();                        // Configures the PWM generator
    timer1Setup();                     // Configures timer1 
    UART2Setup();                      // Configures UART
    ADCsetup();
    
    int state1 = 0, state2 = 0, start = 0;
    TX_F = 1;
    buzz();
    while(1){                          // Infinite loop       
        if (BUTTON && !state1){
            state1 = 1;
            start = 1;
        }    
        if (state1 && !BUTTON)
            state1=0;
        
        while(start){ 
            if(RX_LF <= 1 && RX_RF <= 1){
                MTR_LF = 1;
                MTR_LB = 0;
                MTR_RF = 1;
                MTR_RB = 0;
            }
            else if(RX_LF >= 4 && RX_RF >= 4){
                MTR_LF = 0;
                MTR_LB = 1;
                MTR_RF = 0;
                MTR_RB = 1;
            }
            else{
                MTR_LF = 0;
                MTR_LB = 0;
                MTR_RF = 0;
                MTR_RB = 0;
            }
            if (BUTTON && !state2){
                state2 = 1;
                start = 0;
                MTR_LF = 0;
                MTR_LB = 0;
                MTR_RF = 0;
                MTR_RB = 0;
            }    
            if (state2 && !BUTTON)
                state2=0;
            
            //}
        }
    }
    return 0;                          // We should never really return
}                                      // End function

