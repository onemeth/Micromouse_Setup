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
float vel;

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
    IPC0bits.T1IP   = 3;        // choose interrupt priority
    IEC0bits.T1IE   = 1;        // enable Timer1 interrupt
    T1CONbits.TON   = 1;        // switches the Timer 1 on!
}   
    
/***** INTERRUPT SERVICE ROUTINES *****/
/********************************************************
 * Description                                          
 *      Name      : gpIOSetup                                                  
 *      Author(s) : O.Németh                                                  
 *      ISR       : Maintains a static counter that logs
 *                  a count every 10ms. Also calls
 *                  mySendString function.              
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
    extern float vel2;
   // float angVel;
    static int POSsample = 0; 
    int position;

    
    position = (POSCNT) + (rollover_counter*32768);
    
    
    vel = (position - POSsample)*0.1; 
    POSsample = position;
    
    //angVel = vel*(((2*3.14)/16)/(33*4));
 
  

    /*
    static int count = 0;
    if(count==100){
    char result[100];
    sprintf(result,"Vel = %.3f, Vel2 = %.3f \n", vel, vel2);
    mySendString(result);
    count = 0;
    }
    count++;  
    */
}
