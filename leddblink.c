#include <xc.h>


    #define _XTAL_FREQ 20000000 //Specify the XTAL crystall FREQ


void main() //The main function

{

TRISB=0X00; //Instruct the MCU that the PORTB pins are used as Output.

PORTB=0X00; //Make all output of RB3 LOW


while(1) //Get into the Infinie While loop

{

    RB3=1; //LED ON

    __delay_ms(100); //Wait

    RB3=0; //LED OFF

    __delay_ms(100); //Wait

    

    //Repeat. 

}


}



