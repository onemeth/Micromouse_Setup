/********************************************************
 * Description                                          
 *      File name : UARTfunctions.h                              
 *      Project   : LAb_5_Ex2                       
 *      Author(s) : O.Németh                            
 *      Device    : Firecracker                         
 *      Function  : UART config header file               
 ********************************************************
 * Change History                                       
 *      Released  : 22-11-2018                         
 *      Rev       : 1.0                                
 *      Alt A     :                                    
 ********************************************************/

/***** GAURD *****/ 
#ifndef UARTfunctions_HEADER
#define	UARTfunctions_HEADER

/***** HEADER FILES *****/
#include <xc.h> 
#include <libpic30.h>
/***** DEFINITIONS *****/


/***** PROTOTYPES *****/
void UART1Setup(void);
void UART2Setup(void);
void mySendString(char *);
void decode(char);
/***** END GUARD *****/
#endif	

