/********************************************************
 * Description                                          
 *      File name : PWMfunctions.h                              
 *      Project   : Week_8_LAB4                        
 *      Author(s) : O.Németh                            
 *      Device    : Firecracker                         
 *      Function  : PWM config header file               
 ********************************************************
 * Change History                                       
 *      Released  : 15-11-2018                         
 *      Rev       : 1.0                                
 *      Alt A     :                                    
 ********************************************************/

/***** GAURD *****/ 
#ifndef PWMfunctions_HEADER
#define	PWMfunctions_HEADER

/***** HEADER FILES *****/
#include <xc.h> 

/***** DEFINITIONS *****/


/***** PROTOTYPES *****/
void pwmSetup(void);                  // PWM set up prototype
void dutycycle(int);									// Dutycycle prototype
/***** END GUARD *****/
#endif	

