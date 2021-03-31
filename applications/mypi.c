#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"

#include "mypi.h"



void piledinit()
{
    rt_pin_mode(LED1, PIN_MODE_OUTPUT);
    rt_pin_mode(LED2, PIN_MODE_OUTPUT);
    rt_pin_mode(LED3, PIN_MODE_OUTPUT);
    rt_pin_mode(LED4, PIN_MODE_OUTPUT);
    rt_pin_mode(LED5, PIN_MODE_OUTPUT);
}

void pikainit()
{
    rt_pin_mode(KA1, PIN_MODE_OUTPUT);
    rt_pin_mode(KA2, PIN_MODE_OUTPUT);

    rt_pin_write(KA1, PIN_HIGH);
    rt_pin_write(KA2, PIN_HIGH);
}

int pireadkey()
{
    int8_t kv1,kv2,kv3,kv4;

    rt_pin_mode(ROW1, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(ROW2, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(ROW3, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(ROW4, PIN_MODE_INPUT_PULLUP);

    rt_pin_mode(LINE1, PIN_MODE_OUTPUT);
    rt_pin_write(LINE1, PIN_LOW);
    rt_pin_mode(LINE2, PIN_MODE_OUTPUT);
    rt_pin_write(LINE2, PIN_HIGH);

    kv1=rt_pin_read(ROW1);
    kv2=rt_pin_read(ROW2);
    kv3=rt_pin_read(ROW3);
    kv4=rt_pin_read(ROW4);

    if(kv1==0)  return 1;
    if(kv2==0)  return 2;
    if(kv3==0)  return 3;
    if(kv4==0)  return 4;

    rt_pin_mode(LINE2, PIN_MODE_OUTPUT);
    rt_pin_write(LINE2, PIN_LOW);
    rt_pin_mode(LINE1, PIN_MODE_OUTPUT);
    rt_pin_write(LINE1, PIN_HIGH);

    kv1=rt_pin_read(ROW1);
    kv2=rt_pin_read(ROW2);
    kv3=rt_pin_read(ROW3);
    kv4=rt_pin_read(ROW4);

    if(kv1==0)  return 5;
    if(kv2==0)  return 6;
    if(kv3==0)  return 7;
    if(kv4==0)  return 8;

    return 0;
}

void pimotoinit(int s)
{
    switch(s)
    {
        case 1:rt_pin_mode(S1, PIN_MODE_OUTPUT);
               break;

        case 2:rt_pin_mode(S1, PIN_MODE_OUTPUT);
               rt_pin_mode(S2, PIN_MODE_OUTPUT);
               break;

        case 3:rt_pin_mode(S1, PIN_MODE_OUTPUT);
               rt_pin_mode(S2, PIN_MODE_OUTPUT);
               rt_pin_mode(S3, PIN_MODE_OUTPUT);
               break;

        case 4:rt_pin_mode(S1, PIN_MODE_OUTPUT);
               rt_pin_mode(S2, PIN_MODE_OUTPUT);
               rt_pin_mode(S3, PIN_MODE_OUTPUT);
               rt_pin_mode(S4, PIN_MODE_OUTPUT);
               break;

        case 5:rt_pin_mode(S1, PIN_MODE_OUTPUT);
               rt_pin_mode(S2, PIN_MODE_OUTPUT);
               rt_pin_mode(S3, PIN_MODE_OUTPUT);
               rt_pin_mode(S4, PIN_MODE_OUTPUT);
               rt_pin_mode(S5, PIN_MODE_OUTPUT);
               break;

        case 6:rt_pin_mode(S1, PIN_MODE_OUTPUT);
               rt_pin_mode(S2, PIN_MODE_OUTPUT);
               rt_pin_mode(S3, PIN_MODE_OUTPUT);
               rt_pin_mode(S4, PIN_MODE_OUTPUT);
               rt_pin_mode(S5, PIN_MODE_OUTPUT);
               rt_pin_mode(S6, PIN_MODE_OUTPUT);
               break;

        case 7:rt_pin_mode(S1, PIN_MODE_OUTPUT);
               rt_pin_mode(S2, PIN_MODE_OUTPUT);
               rt_pin_mode(S3, PIN_MODE_OUTPUT);
               rt_pin_mode(S4, PIN_MODE_OUTPUT);
               rt_pin_mode(S5, PIN_MODE_OUTPUT);
               rt_pin_mode(S6, PIN_MODE_OUTPUT);
               rt_pin_mode(S7, PIN_MODE_OUTPUT);
               break;
    }
}


