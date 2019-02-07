/********************************************************
 * Description                                          
 *      File name : PWMfunctions.c
 *      Project   : Week_8_LAB4
 *      Author(s) : O.Németh
 *      Device    : Firecracker
 *      Function  : PWM config file               
 ********************************************************
 * Change History                                       
 *      Released  : 15-11-2018
 *      Rev       : 1.0
 *      Alt A     :
 ********************************************************/

/***** HEADER FILES *****/
#include"PWMfunctions.h"
#include"gpIO.h"

/***** FUNCTIONS *****/
void pwmSetup(void){            
    PTCONbits.PTEN    = 0;      // Switch off PWM time base during configuration
    PTCONbits.PTCKPS  = 1;      // Choose time base prescaler
    PTPERbits.PTPER   = 1000;   // Set the PWM period for 4000Hz
    //PWM 1
    PWMCON1bits.PMOD1 = 1;      // Set PWM unit 1 into the independent mode
    PWMCON1bits.PEN1L = 1;      // Enable PWM 1 low-side driver
    PWMCON1bits.PEN1H = 0;      // Disable PWM 1 high-side driver
    // PWM 2
    PWMCON1bits.PMOD2 = 1;      // Set PWM unit 2 into the independent mode
    PWMCON1bits.PEN2L = 1;      // Enable PWM 2 low-side driver
    PWMCON1bits.PEN2H = 0;      // Disable PWM 2 high-side driver   
    // PWM 3
    PWMCON1bits.PMOD3 = 1;      // Set PWM unit 3 into the independent mode
    PWMCON1bits.PEN3L = 1;      // Enable PWM 3 low-side driver
    PWMCON1bits.PEN3H = 0;      // Disable PWM 3 high-side driver     
    PTCONbits.PTEN    = 1;      // Switch on the PWM generator
    // Set duty cycle of PWM's
    PDC1 = 2000;                // Set LH motor to 100% duty cycle
    PDC2 = 2000;                // Set RH motor to 100% duty cycle
    PDC3 = 1000;                // Set buzzer to 50% duty cycle
}   

void dutycycle(dc){ 
    static int dutycycle = 0;
    dutycycle = (2000/100)*dc;
    PDC1 = dutycycle;           // Modify duty cycle of PWM1
    PDC2 = dutycycle;           // Modify duty cycle of PWM2
}                               // End function