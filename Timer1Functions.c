/********************************************************
 * Description                                          
 *      File name : Timer1Functions.c
 *      Project   : Week_8_LAB4
 *      Author(s) : O.Nemeth
 *      Device    : Firecracker
 *      Function  : Timer1 config source file. Timer 1
 *                  config function. Configured for 
 *                  triggering every 10ms.               
 ********************************************************
 * Change History                                       
 *      Released  : 01-11-2018
 *      Rev       : 1.0
 *      Alt A     :
 ********************************************************/

/***** HEADER FILES *****/
#include"Timer1Functions.h"
#include"gpIO.h"
#include"PWMfunctions.h"
#include"UARTfunctions.h"
#include<stdio.h>

/***** EXT VARS    *****/
float velR;

/***** FUNCTIONS *****/
void timer1Setup(void){
    T1CONbits.TON   = 0;        // switches the timer off during setup (good practice)
    T1CON           = 0;    
    TMR1            = 0;        // resets the timer to 0
    T1CONbits.TCKPS = 3;        // pre-scale value 0=1:1, 1=1:8, 2=1:64, 3=256
    PR1             = 625;      // 
    T1CONbits.TCS   = 0;        // chooses internal clock
    // TSYNC = x                   TSYNC is ignored when using the internal clock
    T1CONbits.TSIDL = 1;        // stop timer in idle mode
    T1CONbits.TGATE = 0;        // do not gate the timer
    IFS0bits.T1IF   = 0;        // clear the interrupt flag
    IPC0bits.T1IP   = 1;        // choose interrupt priority
    IEC0bits.T1IE   = 1;        // enable Timer1 interrupt
    T1CONbits.TON   = 1;        // switches the Timer 1 on!
}   
    
/***** INTERRUPT SERVICE ROUTINES *****/
/********************************************************
 * Description                                          
 *      Name      : gpIOSetup                                                  
 *      Author(s) : O.Németh                                                  
 *      ISR       : Maintains a static counter that logs
 *                  a count every 10ms.             
 ********************************************************
 * Change History                                       
 *      Released  : 15-11-2018                          
 *      Rev       : 1.0                                 
 *      Alt A     :                                     
 ********************************************************/
void __attribute__((interrupt, auto_psv)) _T1Interrupt(void){    
    IFS0bits.T1IF = 0;                      // Reset the timer 1 interrupt flag
    ADCON1bits.ASAM = 1;                    // start ADC sampling
    extern int rollover_counter;
    static int POSsample = 0, position; 
    
    /*
   
    if(count == 1000){
        PID_controllerR(0);
        PID_controllerL(0);
       // Stop();
        count = 0;
    }
    else if(count > 900){
        Move_forwards();
        float speed = 6;
        PID_controllerR(speed);
        PID_controllerL(speed);
        
    }
    count++;
    */
   
        static int speed =0;
        static int count = 0;
        static int countl = 0;
        Move_forwards();
        
        PID_controllerR(speed);
        PID_controllerL(speed);
        
        if(countl = 10000){
        if(count <= 6)
            speed++;
        if(count > 6 && count <= 12)
            speed--;
        if(count == 13)
            count =0;
        countl = 0;
        }
        countl++;
        
    position = (POSCNT) + (rollover_counter*32768);
    velR = (position - POSsample)*0.1; 
    POSsample = position;

    /*
    static int count = 0;
    if(count==100){
    char result[100];
    sprintf(result,"VelR = %.3f, VelL = %.3f \n", velR, velL);
    mySendString(result);
    count = 0;
    }
    count++;  
     */
    
}
