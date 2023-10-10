#pragma config FOSC = HS     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
# include<xc.h>
#define _XTAL_FREQ 4000000
void I2C_Init(void)
{
	
	SSPSTAT = 0x80;
	SSPCON = 0x28;   
	SSPADD = 0x28;   
}

void I2C_Start()
{
	SEN = 1;        
	while(SEN);     
                   
}
 

void I2C_Stop()
{
	PEN = 1;       
	while(PEN);    
                
}
 
void I2C_Restart()
{
	RSEN = 1;        
	while(RSEN);    
}
 

void I2C_Ack()
{
	ACKDT = 0;      
	ACKEN = 1;      
	while(ACKEN);   
}
 

void I2C_Nak()
{
	ACKDT = 1;     
	ACKEN = 1;      
	while(ACKEN);   
}
 
void I2C_Wait()
{
	while ((SSPCON2 &  0x1F ) || ( SSPSTAT & 0x04 ));

}
 

void I2C_Send(unsigned char dat)
{
	SSPBUF = dat;   
	while(BF);       
	I2C_Wait();     
}
 

unsigned char I2C_Read(void)
{
	unsigned char temp;

	RCEN = 1;        
	while(!BF);     
	temp = SSPBUF;  
	I2C_Wait();       
	return temp;  
}
void main()
{
    TRISC3 = 0;     
	TRISC4 = 0;    
    I2C_Start;
    I2C_Ack;
            I2C_Nak;
    I2C_Stop;
    while(1)
    {
     I2C_Start;
    I2C_Read;
    I2C_Send;
      I2C_Stop;
            
    }
    
    
    
}
