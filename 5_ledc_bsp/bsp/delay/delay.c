#include "delay.h"

/*短延时函数*/
void delay_short(volatile  unsigned int n)
{
    while (n--)
    {
    }
    
}

/*延时函数*/
void delay(volatile unsigned int n)
{
    while (n--)
    {
        /* code */
        delay_short(0x7FF); 
    }
    
}

