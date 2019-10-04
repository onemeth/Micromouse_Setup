
#include"miscFunctions.h"
#include"gpIO.h"

void delay(int timemS){
    int i, j;
    for(i=0; i<timemS; i++){
        for(j=0; j<1958; j++){   
        }
    }
}

void buzz(void){
    BUZZ = 1;
    delay(1000);
    BUZZ = 0;
}
