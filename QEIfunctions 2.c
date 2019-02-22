/********************************************************
 * Description                                          
 *      File name : QEIfunctions.c
 *      Project   : Micromouse
 *      Author(s) : O.Németh
 *      Device    : Micromouse
 *      Function  :               
 ********************************************************
 * Change History                                       
 *      Released  : 07-02-2019
 *      Rev       : 1.0
 *      Alt A     :
 ********************************************************/

/***** HEADER FILES *****/
#include "QEIfunctions.h"
#include "UARTfunctions.h"
#include <stdio.h>               // for sprintf
#include <string.h>

/***** FUNCTIONS *****/

/********************************************************
 * Description                                          
 *      Name      : QEISetup                                                 
 *      Author(s) : UWE                                                  
 *      Function  :              
 ********************************************************
 * Change History                                       
 *      Released  : 07-02-2019
 *      Rev       : 1.0
 *      Alt A     :                                   
 ********************************************************/
void QEIsetup(void){
    // configure analogue pins as digital channels
    ADPCFGbits.PCFG5    = 1;        // QEB on pin 7 shared with AN5
    ADPCFGbits.PCFG4    = 1;        // QEA on pin 6 shared with AN4
    // note: IND pin is not connected on firecracker board
    // Configure QEI module
    QEICONbits.QEISIDL  = 1;        // Discontinue operation when in idle mode
    QEICONbits.QEIM     = 0b111;    // x4 edge gain and reset POSCNT when == MAXCNT
    QEICONbits.SWPAB    = 0;        // Do not swap the polarity of phase comparison
    QEICONbits.PCDOUT   = 0;        // Disable counter direction pin (normal I/O operation)
    QEICONbits.POSRES   = 0;        // index pulse does not reset POSCNT
    QEICONbits.TQCS     = 0;        // internal clock source (Tcy)
    DFLTCONbits.QEOUT   = 0;        // disable digital filters  
    // set initial counter value and maximum range
    MAXCNT              = 0xffff;   // set the highest possible time out
    POSCNT              = 0x7fff;   // set POSCNT into middle of range
    // Configure Interrupt controller
    IFS2bits.QEIIF      = 0;        // clear interrupt flag
    IEC2bits.QEIIE      = 1;        // enable QEI interrupt
    IPC10bits.QEIIP     = 5;        // set QEI interrupt priorities
}

/***** INTERRUPT SERVICE ROUTINES *****/
/********************************************************
 * Description                                          
 *      Name      : QEIInterrupt                                                 
 *      Author(s) : O.Nemeth                                                  
 *      ISR       :             
 ********************************************************
 * Change History                                       
 *      Released  : 27-01-2019                          
 *      Rev       : 1.0                                 
 *      Alt A     :                                     
 ********************************************************/
void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void){
    static int count=0;
    char POSCNT_String[] = " POSCNT: ";
    char result[10];
    IFS2bits.QEIIF = 0; // clear interrupt flag
    //if(POSCNT<32768)
        // over-run condition caused interrupt
    //else
        // under-run condition caused interrupt
    sprintf(result, "%d", POSCNT);
    strcat(POSCNT_String, result);
    if(count == 100){
        mySendString(POSCNT_String);
        count = 0;
    }
    count++;
}

