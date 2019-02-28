/********************************************************
 * Description                                          
 *      File name : gpIO.h                              
 *      Project   : Week_8_LAB4                        
 *      Author(s) : O.Németh                            
 *      Device    : Firecracker                         
 *      Function  : IO config header file               
 ********************************************************
 * Change History                                       
 *      Released  : 18-10-2018                         
 *      Rev       : 1.0                                
 *      Alt A     :                                    
 ********************************************************/

/***** GAURD *****/ 
#ifndef gpIO_HEADER
#define	gpIO_HEADER

/***** HEADER FILES *****/
#include <xc.h> 

/***** DEFINITIONS *****/
// ALWAYS READ FROM PORT, ! complements the port (inverts switch)
// ALWAYS WRITE TO LATCH

// Buzzer
#define BUZZ        LATCbits.LATC13     // Write to latch to toggle buzzer

// Button
#define BUTTON      !PORTDbits.RD0      // Read from inverted button

// Motor direction controls
#define MTR_RF      LATEbits.LATE1      // RH motor forward rotation 
#define MTR_RB      LATEbits.LATE3      // RH motor backward rotation 
#define MTR_LB      LATEbits.LATE5      // LH motor backward rotation 
#define MTR_LF      LATEbits.LATE8      // LH motor forward rotation 

// IR TX
#define TX_S        LATDbits.LATD1      // Side IR LED TX switch
#define TX_F        LATDbits.LATD2      // Front IR LED TX switch 
#define TX_P        LATDbits.LATD3      // Post IR LED TX switch 

/***** PROTOTYPES *****/
void gpIOSetup(void);

void Move_forwards(void);
void Move_forwards_one_cell(void);
void Move_forwards_half_cell(void);
void Move_backwards(void);
void Turn_right(void);
void Turn_left(void);
void Turn_180(void);
void Stop(void);

void TX_side(int);
void TX_front(int);
void TX_post(int);

float PID_controller (float);

/***** END GUARD *****/
#endif	

