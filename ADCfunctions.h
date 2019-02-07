/********************************************************
 * Description                                          
 *      File name : ADCfunctions.h                              
 *      Project   : Micromouse                       
 *      Author(s) : O.Németh                            
 *      Device    : Micromouse                        
 *      Function  : ADC config file               
 ********************************************************
 * Change History                                       
 *      Released  : 27-01-2019                         
 *      Rev       : 1.0                                
 *      Alt A     :                                    
 ********************************************************/

/***** GAURD *****/ 
#ifndef ADCfunctions_HEADER
#define	ADCfunctions_HEADER

/***** HEADER FILES *****/
#include <xc.h> 

/***** DEFINITIONS *****/

#define RX_LS (ADCBUF0 * 0.00488)      // Assign samples in sample sequence order ie BUF0 to 5
#define RX_LF (ADCBUF1 * 0.00488)
#define RX_LP (ADCBUF2 * 0.00488)
#define RX_RP (ADCBUF3 * 0.00488)     
#define RX_RF (ADCBUF4 * 0.00488)
#define RX_RS (ADCBUF5 * 0.00488)

/***** PROTOTYPES *****/
void ADCsetup(void);

/***** END GUARD *****/
#endif	

