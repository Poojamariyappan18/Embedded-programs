/*
 * File:   newmain.c
 * Author: 91994
 *
 * Created on 1 October, 2023, 7:00 AM
 */

// PIC16F877A Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include"adc.h"
#define _XTAL_FREQ 4000000

#define lcd PORTD
#define rs RC0
#define rw RC1
#define en  RC2
   

void delay()
{
    int i;
    for(i=0;i<1000;i++);
}
void cmd(unsigned int x)
{
    lcd=x;
    rs=0;
    rw=0;
      en=1;
    delay();
    en=0;
}
void dat(unsigned int y)
{  
    lcd=y;
    rs=1;
    rw=0;
      en=1;
    delay();
    en=0;
}
void cmmd()
{
    cmd(0x38);
    cmd(0x0c);
    cmd(0x06);
    cmd(0x01);
    cmd(0x80);
}
void fun(unsigned int adc)
{

    cmmd();
    unsigned int a,b,c,d,e,f,g,h,i,j,k,m,n,l;
    
    
       a= adc;
  
       b=a/10;
       c=a%10;
       
       d=b/10;
       e=b%10;
       
       f=d/10;
       g=d%10;
       
       l=f/10;
       m=f%10;
       
         n=l+(0x30);
     dat(n);
       h=m+(0x30);
       dat(h);
       i=g+(0x30);
       dat(i);
       j=e+(0x30);
       dat(j);
       k=c+(0x30);
       dat(k); 
   
}



void main(void) {

    TRISC0=0;
       TRISC1=0;
          TRISC2=0;
    TRISD=0x00;
unsigned int result;

    SSPCON=0X28;
    SSPADD=9;
    i2c_start();
    i2c_send(0x90);
    i2c_send(0x01);
    i2c_send(0xC2);
    i2c_send(0x03);
    i2c_stop();
    __delay_ms(10);
    
    while(1){
        result=0;
    i2c_start();
    i2c_send(0x90);
    i2c_send(0x00);
    i2c_stop();
    __delay_ms(10);
    i2c_start();
    i2c_send(0x91);
    result|=i2c_read();
    i2c_ack();
    result|=i2c_read()<<8;
    i2c_nack();
    i2c_stop();
    fun(result);
   // fun(result);    
    }
    
}
