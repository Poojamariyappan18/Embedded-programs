#include <xc.h>
#include <stdio.h>
#include <stdint.h>

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 20000000
// Define I2C address of ADS1015
#define ADS1015_ADDRESS 0x48

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
    int a,b,c,d,e,f,g,h,i,j,k;
    
    
       a= adc;
  
       b=a/10;
       c=a%10;
       
       d=b/10;
       e=b%10;
       
       f=d/10;
       g=d%10;
       
       h=f+(0x30);
       dat(h);
       i=g+(0x30);
       dat(i);
       j=e+(0x30);
       dat(j);
       k=c+(0x30);
       dat(k); 
}

// Function to initialize I2C
void I2C_Init() {
    // Configure I2C for master mode, 100 kHz
    SSPCON = 0b00101000;
    SSPADD =0x09; // For 100 kHz at 4 MHz clock
    SSPSTAT = 0;
}

// Function to start I2C communication
void I2C_Start() {
    SEN = 1; // Initiate start condition
    while (SEN); // Wait for start condition to finish
}

// Function to write data over I2C
void I2C_Write(uint8_t data) {
    SSPBUF = data; // Write data to SSPBUF register
    while (SSPIF == 0); // Wait for transmission to complete
    SSPIF = 0; // Clear SSPIF flag
}

// Function to read data over I2C
uint8_t I2C_Read() {
    RCEN = 1; // Enable reception
    while (!SSPIF); // Wait for reception to complete
    SSPIF = 0; // Clear SSPIF flag
    return SSPBUF; // Return received data
}

// Function to stop I2C communication
void I2C_Stop() {
    PEN = 1; // Initiate stop condition
    while (PEN); // Wait for stop condition to finish
}

void main() {
    uint16_t result;
    
    TRISC3 = 1; // SDA pin as input
    TRISC4 = 1; // SCL pin as input
    TRISD=0x00;
    TRISB=0x00;
    TRISC0=0;
    TRISC1=0;
    TRISC2=0;
    
    I2C_Init(); // Initialize I2C
    
    while (1) {
        // Start I2C communication
        I2C_Start();
        
        // Send ADC conversion command (channel 0, single-shot mode)
        I2C_Write(ADS1015_ADDRESS<<1 ); // Send device address (write)
        I2C_Write(0x01); 
        I2C_Write(0xC3); // MSB: 11000011, LSB: 00000000 (channel 0, single-shot mode, +/-2.048V range)
        
        // Stop I2C communication
   //     I2C_Stop();
        
        // Delay for conversion (adjust as needed)
        __delay_ms(100);
        
        // Start I2C communication again
       I2C_Start();
        
        // Read conversion result
        I2C_Write(ADS1015_ADDRESS<<1 ); // Send device address (write)
        __delay_ms(100);
        I2C_Write(0x00); // Send conversion register address
        __delay_ms(100);
        // Restart I2C communication
      I2C_Start();
        
        I2C_Write((ADS1015_ADDRESS<<1 ) | 0x01); // Send device address (read)
        __delay_ms(100);
     I2C_Read();
        result =  I2C_Read(); // Read MSB and LSB
        

               fun(result);
        // Stop I2C communication
        I2C_Stop();
        
        // Process the ADC result (result variable)
        // You can convert it to voltage using the ADS1015's configuration.
        fun(result);
        // Add your code here to do something with the ADC result
        
        // Delay before the next reading (adjust as needed)
        __delay_ms(1000);
    }
}
