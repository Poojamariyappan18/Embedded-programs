

#include <xc.h>

int  main(void) {
    TRISB=0x00;
    TRISC=0xff;
    while(1)
    {
        if(RC0==1)
        {
            RB0=1;
        }
        else
        {
            RB0=0;
        }
        
       }
   
}
