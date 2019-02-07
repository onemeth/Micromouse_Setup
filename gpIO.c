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
