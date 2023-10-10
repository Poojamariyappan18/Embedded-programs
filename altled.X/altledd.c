#include<xc.h>
#define _XTAL_FREQ 20000000 
void main() 
{
TRISB=0X00; 
PORTB=0X00; 
while(1) 
{
  RB3=1; 
    RB2=0;
    __delay_ms(1000); 
   
    RB3=0;
    RB2=1;

    __delay_ms(1000);

}
}