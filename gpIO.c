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

    while((32767+662) > POSCNT){
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
    MTR_LF = 0;
    MTR_LB = 0;
    MTR_RF = 0;
    MTR_RB = 0;
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