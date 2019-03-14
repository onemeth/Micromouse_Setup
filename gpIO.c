/********************************************************
 * Description                                          
 *      File name : gpIO.c                              
 *      Project   : Week_8_LAB4                         
 *      Author(s) : O.Németh                            
 *      Device    : Firecracker                        
 *      Function  : IO config source file               
 ********************************************************
 * Change History                                       
 *      Released  : 18-10-2018                          
 *      Rev       : 1.0                                 
 *      Alt A     :                                     
 ********************************************************/

/***** HEADER FILES *****/
#include"gpIO.h"
#include"UARTfunctions.h"
#include<stdio.h>
#include"PWMfunctions.h"
/***** FUNCTIONS *****/

/********************************************************
 * Description                                          
 *      Name      : gpIOSetup                                                  
 *      Author(s) : O.Németh                                                  
 *      Function  : IO set up function              
 ********************************************************
 * Change History                                       
 *      Released  : 18-10-2018                          
 *      Rev       : 1.0                                 
 *      Alt A     :                                     
 ********************************************************/
void gpIOSetup(void) {
    // Set IO
    // Outputs
    TRISCbits.TRISC13   = 0;    // Buzzer output
    TRISEbits.TRISE1    = 0;    // LH motor forward rotation output
    TRISEbits.TRISE3    = 0;    // LH motor backward rotation output
    TRISEbits.TRISE5    = 0;    // RH motor forward rotation output
    TRISEbits.TRISE8    = 0;    // RH motor backward rotation output
    TRISDbits.TRISD1    = 0;    // Side IR LED TX switch output  
    TRISDbits.TRISD2    = 0;    // Front IR LED TX switch output  
    TRISDbits.TRISD3    = 0;    // Post IR LED TX switch output 
    
    // Inputs
    TRISDbits.TRISD0    = 1;    // Button input
    TRISBbits.TRISB4    = 1;    // Encoder 1 A input
    TRISBbits.TRISB5    = 1;    // Encoder 1 B input
    
}

void Move_forwards(void){
    MTR_LF = 1;
    MTR_LB = 0;
    MTR_RF = 1;
    MTR_RB = 0;
}

void Move_forwards_one_cell(void){
    POSCNT = 32767;
    while((32767-2847) < POSCNT){ 
        MTR_LF = 1;
        MTR_LB = 0;
        MTR_RF = 1;
        MTR_RB = 0; 
        //PID_controllerL
        //PID_controllerR
        //PID_controller_SENSOR
    }
    Stop(); 
}

void Move_forwards_half_cell(void){
    POSCNT = 32767;
    while((32767-1422) < POSCNT){ 
        MTR_LF = 1;
        MTR_LB = 0;
        MTR_RF = 1;
        MTR_RB = 0; 
    }
    Stop(); 
}

void Move_backwards(void){
    MTR_LF = 0;
    MTR_LB = 1;
    MTR_RF = 0;
    MTR_RB = 1;   
}

void Turn_right(void){
    POSCNT = 0x7fff;
    while((32767-662) < POSCNT){ //820
        MTR_LF = 1;
        MTR_LB = 0;
        MTR_RF = 0;
        MTR_RB = 1; 
    }
    Stop();  
}

void Turn_left(void){
    POSCNT = 0x7fff;
    unsigned long ans = (long int)32767+ (long int)662;
    
    while((ans) > POSCNT){
        MTR_LF = 0;
        MTR_LB = 1;
        MTR_RF = 1;
        MTR_RB = 0; 
    }
    Stop(); 
}

void Turn_180(void){
    POSCNT = 0x7fff;
    while((32767-1719) < POSCNT){
        MTR_LF = 1;
        MTR_LB = 0;
        MTR_RF = 0;
        MTR_RB = 1; 
    }
    Stop();     
}

void Stop(void){
    MTR_LF = 1;
    MTR_LB = 1;
    MTR_RF = 1;
    MTR_RB = 1;
}

void TX_side(int state){
    TX_S = state;
}
void TX_front(int state){
    TX_F = state;
}
void TX_post(int state){
    TX_P = state;  
}


/******************************************
 * PID velocity controller function
 * ===================
 * Returns a floating point valued drive
 * Expects to receive a floating point argument as the desired velocity
 * 
 * Desired velocity:    at 7.4V - Max 7 min 5
 *                      at 6V - Max ? min ? Test this
 ******************************************/
void PID_controllerR(float desired_velocity)
{
    int actual_velocity;                            // Measured velocity ( note: this is signed int )
    float Proportional_Component;                   // }
    float Derivative_Component;                     // } Separate components of controller
    float drive;                                   // Output of the controller
    float error;                                    // Difference between desired and actual velocities
    static float error_1 = 0;                       // Previous difference between desired and actual velocities
    float error_deriv;                              // change in difference between desired and actual velocities
    float Kp, Kd;                                   // PID Gains
    extern float velR;
    int PDC_Val;                                    // Value to send to control PDC
    
    // Set gains (THESE MUST BE TUNED!)
    Kp = 5; //25                                      // Proportional gain = 20.0
    Kd = 3; //0.25                                      // Derivative gain is value divide by 100, i.e. Kd=.2 = 20.0
    
    // Calculate difference between desired and actual velocities, i.e., calculate ERROR
    actual_velocity = velR;                         //getEncoderVelocity(); // from next weeks lecture
    error = desired_velocity - (float)actual_velocity; // cast an int to a float
    
    // Calculate Proportional component
    Proportional_Component = error * Kp;

    // Calculate Derivative component
    error_deriv = error - error_1;                  // current error ? previous error
    Derivative_Component = error_deriv * Kd;
    error_1 = error;                                // update previous error for next control iteration
    
    // sum the components
    drive = Proportional_Component + Derivative_Component ; 
    
    
    if (drive < 0)                                  // Slow down!
       PDC_Val = ((int)(drive*-1)/100);                   // Set PDC to lower value
    if(drive > 0){                             // Speed up!
        PDC_Val = (int)100*((drive));                // Set PDC to higher value
    }    
    if(PDC_Val > 2000)                          // Set PDC's max value
        PDC_Val = 2000;
    //dutycycleR(PDC_Val);                            // Adjust Speed
    PDC1 = PDC_Val;
    
    static int countP = 0;
    if(countP==100){
        char result[100];
        //sprintf(result," drive = %.1f VelR = %.3f PDC_Val = %d", drive, velR, PDC_Val);
        sprintf(result," %.3f ", velR);
        mySendString(result);
        countP = 0;
    }
    countP++; 
}
/******************************************
 * PID velocity controller function
 * ===================
 * Returns a floating point valued drive
 * Expects to receive a floating point argument as the desired velocity
 * 
 * Desired velocity:    at 7.4V - Max 7 min 5
 *                      at 6V - Max ? min ? Test this
 ******************************************/
void PID_controllerL(float desired_velocity)
{
    int actual_velocity; // Measured velocity ( note: this is signed int )
    float Proportional_Component; // }
    float Derivative_Component; // } Separate components of controller
    float Integral_Component; // }
    float drive ; // Output of the controller
    float error; // Difference between desired and actual velocities
    static float error_1 = 0; // Previous difference between desired and actual velocities
    static float integrator_sum = 0; // Sum of all differences between desired and actual velocities
    float error_deriv; // change in difference between desired and actual velocities
    float Kp, Ki, Kd; // PID Gains
    extern float velL;
    int PDC_Val;                                    // Value to send to control PDC
    
    // Set gains (THESE MUST BE TUNED!)
    Kp = 8; //25                                   // Proportional gain = 20.0
    //Ki = 0;                                         // Integral gain value is times 100, i.e. Ki=100 = 1.0
    Kd = 3; //0.25                                 // Derivative gain is value divide by 100, i.e. Kd=.2 = 20.0
    
    // Calculate difference between desired and actual velocities, i.e., calculate ERROR
    actual_velocity = velL;                         //getEncoderVelocity(); // from next weeks lecture
    error = desired_velocity - (float)actual_velocity; // cast an int to a float
    
    // Calculate Proportional component
    Proportional_Component = error * Kp;

        // Calculate Integral component
//    if(integrator_sum > 32000) //32000
//        integrator_sum = 32000; // To prevent integral overflow
//    if(integrator_sum < -32000)
//        integrator_sum = -32000; // To prevent integral underflow
//    
//    integrator_sum = integrator_sum + error; // update the integral sum with current error
//    Integral_Component = integrator_sum * Ki;
    
    // Calculate Derivative component
    error_deriv = error - error_1; // current error ? previous error
    Derivative_Component = error_deriv * Kd;
    error_1 = error; // update previous error for next control iteration
    //drive = Proportional_Component + Integral_Component + Derivative_Component ; // sum the components
    drive = Proportional_Component + Derivative_Component ; // sum the components
    
    if (drive < 0)                                  // Slow down!
      // Move_backwards(); 
       PDC_Val = ((int)(drive*-1)/100);                   // Set PDC to lower value
    if(drive > 0){                             // Speed up!
      //  Move_forwards();
        PDC_Val = (int)100*((drive));                // Set PDC to higher value
    }    
    if(PDC_Val > 2000)                          // Set PDC's max value
        PDC_Val = 2000;
    //dutycycleR(PDC_Val);                            // Adjust Speed
    PDC2 = PDC_Val;
    
    //static int countP = 0;
    //if(countP==10000){
        //char result[100];
        //sprintf(result," drive = %.1f VelL = %.3f PDC_Val = %d", drive, velL, PDC_Val);
        //sprintf(result," VelL = %.3f ", velL);
        //mySendString(result);
        //countP = 0;
    //}
    //countP++; 
}


    