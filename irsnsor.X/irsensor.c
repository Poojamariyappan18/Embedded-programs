#include <xc.h>
#define _XTAL_FREQ 20000000 
#define IR RC0
#define led RB2
#define buzzer RB3
void main() 
{

TRISB=0X00; 
TRISC=0Xff;
PORTB=0X00; 
while(1) 
{
    if(IR ==0){

        led=1;
        buzzer=1;

        __delay_ms(1000);   
    }
    else{

        led=0;
        buzzer=1;
 }
}
}

 