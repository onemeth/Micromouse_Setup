/********************************************************
 * Description                                          
 *      File name : ADCfunctions.c
 *      Project   : Micromouse
 *      Author(s) : O.Németh
 *      Device    : Micromouse
 *      Function  :               
 ********************************************************
 * Change History                                       
 *      Released  : 27-01-2019
 *      Rev       : 1.0
 *      Alt A     :
 ********************************************************/

/***** HEADER FILES *****/
#include"ADCfunctions.h"
#include"UARTfunctions.h"
#include"gpIO.h"
#include <stdio.h>               // for sprintf
#include<string.h>

/***** FUNCTIONS *****/

/********************************************************
 * Description                                          
 *      Name      : ADCSetup                                                 
 *      Author(s) : UWE                                                  
 *      Function  :              
 ********************************************************
 * Change History                                       
 *      Released  : 27-01-2019
 *      Rev       : 1.0
 *      Alt A     :                                   
 ********************************************************/
void ADCsetup(void){
    ADCON1bits.ADON=0;          // Disable ADC
    ADPCFG=0xffff;              // All digital inputs
    // ADC inputs
    ADPCFGbits.PCFG0=0;         // Set AN0 as analog input
    ADPCFGbits.PCFG1=0;         // Set AN1 as analog input
    ADPCFGbits.PCFG2=0;         // Set AN2 as analog input
    ADPCFGbits.PCFG6=0;         // Set AN6 as analog input
    ADPCFGbits.PCFG7=0;         // Set AN7 as analog input
    ADPCFGbits.PCFG8=0;         // Set AN8 as analog input
    // Channel scan
    ADCSSLbits.CSSL0=1;         // Select channels to scan
    ADCSSLbits.CSSL1=1;
    ADCSSLbits.CSSL2=1;
    ADCSSLbits.CSSL6=1;
    ADCSSLbits.CSSL7=1;
    ADCSSLbits.CSSL8=1;
    
    ADCON2bits.CSCNA=1;         // Enable channel scanning
    ADCHSbits.CH0NA=0;
    ADCHSbits.CH0SA=0b0000;     // We scan through the other channels (ignore)
    ADCON1bits.SIMSAM=0;        // Sequential sampling, not simultaneous sampling
    ADCON2bits.CHPS=0b00;       // Only sample and hold unit 0 (Ch0)
    ADCON2bits.SMPI= 5;         // Generate an interrupt after conversion of 6 channels
                                // Select the conversion clock
    ADCON2bits.ALTS=0;          // Multiplexer settings A, i.e. scanning through inputs
    ADCON2bits.BUFM=0;          // Select conversion buffer to use all 16 words (not 2x8 words)
    ADCON2bits.VCFG=0b000;      // Select AVdd and AVss as voltage reference
    ADCON1bits.FORM=0b00;       // Conversion type = unsigned int
    ADCON3bits.ADRC=0;          // Clock is derived from internal clock;
    ADCON3bits.ADCS=0b111111;   // Sets the conversion period to 32 x Tcyc (slowest possible)
    ADCON3bits.SAMC=0b11111;    // Sets the auto sample speed to 32xTad -> slowest setting
    ADCON1bits.SSRC=0b111;      // Conversion (not sampling) is started with ADC clock
    ADCON1bits.SAMP=1;          // Ready to sample
    ADCON1bits.ASAM=0;          // Set autosample in timer1
    IFS0bits.ADIF=0 ;           // Clear the interrupt flag (in case it was on)
    IPC2bits.ADIP=5 ;           // Set the ADC priority to 5
    IEC0bits.ADIE=1;            // Enable ADC interrupts
    ADCON1bits.ADON=1;          // Enable ADC
}

/***** INTERRUPT SERVICE ROUTINES *****/

/********************************************************
 * Description                                          
 *      Name      : ADCInterrupt                                                 
 *      Author(s) : O.Nemeth                                                  
 *      ISR       :             
 ********************************************************
 * Change History                                       
 *      Released  : 27-01-2019                          
 *      Rev       : 1.0                                 
 *      Alt A     :                                     
 ********************************************************/
void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void){
    // 5/1024: 5 volts max with resolution of 1024 gives 0.00488v increase per bit 
    static int count=0;
    char RX_String[] = " RX: ";
    char result[10];
    IFS0bits.ADIF=0;            //reset the interrupt flag
    ADCON1bits.ASAM=0;          //stop the sampling
                                //now read the data from the buffers ADCBUF0, ADCBUF1 etc.
    sprintf(result, "%.2f", RX_LF);
    strcat(RX_String, result);
    
    if(count == 100){
        mySendString(RX_String);
        count = 0;
    }
    count++;
}
