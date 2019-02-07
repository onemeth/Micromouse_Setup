
#include"miscFunctions.h"
#include"gpIO.h"

void delay(void){
    int i=0;
    while(i<3280){
        i++;
    }
}

void buzz(void){
    BUZZ = 1;
    delay();
    BUZZ = 0;
    delay();
    BUZZ = 1;
    delay();
    BUZZ = 0;
}