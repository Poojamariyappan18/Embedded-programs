/*
 * File:   newmain.c
 * Author: Admin
 *
 * Created on 16 September, 2023, 3:34 PM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#include <xc.h>
void delay();
void main(void) {
    
    
    TRISD=0x00;
    TRISB0=0;
    TRISB1=0;
    
    
    int a[]={0xC0,0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90},i,j,k,l;
    for( i=0;i<100;i++)
    {
        j=i%10;
        RB0=1;
        RB1=0;
        PORTD=a[j];
        delay();
        
        
        j=i/10;
        RB0=0;
        RB1=1;
       PORTD= a[j];
        delay(); 
    }
    
    return;
}
void delay()
{
    int i,j;
    for(i=0;i<1000;i++)
        for(j=0;j<100;j++);




}