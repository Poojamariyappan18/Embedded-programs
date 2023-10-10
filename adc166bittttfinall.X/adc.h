
#ifndef  XC_adc_h
#define XC_adc_h

#include <xc.h>
#ifdef	__cplusplus
extern "C" {
#endif 

void i2c_flag()
{
    while(SSPIF==0);
    SSPIF=0;
}
void i2c_start()
{
    SEN=1;
    i2c_flag();
}
void i2c_stop()
{
    PEN=1;
    i2c_flag();
}
void i2c_restart()
{
    RSEN=1;
    i2c_flag();
}
void i2c_ack()
{
    ACKDT=0;
    ACKEN=1;
    i2c_flag();
}
void i2c_nack()
{
    ACKDT=1;
    ACKEN=1;
    i2c_flag();
}
void i2c_send(char b)
{
    SSPBUF=b;
    i2c_flag();
    while(ACKSTAT==1);
    
}

char i2c_read()
{
    RCEN=1;
    i2c_flag();
    return SSPBUF;
}

    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

