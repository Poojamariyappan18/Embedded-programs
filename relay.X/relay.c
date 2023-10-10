#include <xc.h>

/*

 Hardware related definition

 */

#define _XTAL_FREQ 200000000 //Crystal Frequency, used in delay

#define SW PORTBbits.RB0

#define RELAY PORTBbits.RB1

#define LED PORTBbits.RB2


/*

 Other Specific definition

 */

void system_init(void);


void main(void) {

    system_init(); // System getting ready    

    while(1){

        if(SW == 1){ //switch is pressed

            __delay_ms(50); // debounce delay

            if (SW == 1){ // switch is still pressed

                LED = !LED; // inverting the pin status.

                RELAY = !RELAY;

            }

        }

     }

    return;

    }

    

/*

 This Function is for system initialisations.

 */


void system_init(void){

    TRISBbits.TRISB0 = 1; // Setting Sw as input

    TRISBbits.TRISB1 = 0; // setting LED as output

    TRISBbits.TRISB2 = 0; // setting relay pin as output

    LED = 0;

    RELAY = 0;

    }

