#include "main.h"

int main(int argc, char *argv[])
{
    Led_Init();

    while (1)
    {
         LED_Off();
        delay(500);
        LED_On();
        delay(500);
    }
}

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

void Led_Init(void)
{
    CCM_CCGR0 = 0xFFFFFFFF;
    CCM_CCGR1 = 0xFFFFFFFF;
    CCM_CCGR2 = 0xFFFFFFFF;
    CCM_CCGR3 = 0xFFFFFFFF;
    CCM_CCGR4 = 0xFFFFFFFF;
    CCM_CCGR5 = 0xFFFFFFFF;
    CCM_CCGR6 = 0xFFFFFFFF;



    IOMUXC_MUX_GPIO1_IO03 = 0x00000005;
    IOMUXC_PAD_GPIO1_IO03  = 0x000010B0;

    GPIO1_GDIR = 0x00000008;
    GPIO1_DR = 0x0;
}

//开灯
void LED_On(void)
{
    GPIO1_DR &= ~(1<<3);
}

//关灯
void LED_Off(void)
{
    GPIO1_DR |=  (1<<3);
}