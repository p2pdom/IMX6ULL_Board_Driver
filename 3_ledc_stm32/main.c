#include "main.h"
#include "imx6u.h"

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
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0xFFFFFFFF;
    CCM->CCGR2 = 0xFFFFFFFF;
    CCM->CCGR3 = 0xFFFFFFFF;
    CCM->CCGR4 = 0xFFFFFFFF;
    CCM->CCGR5 = 0xFFFFFFFF;
    CCM->CCGR6 = 0xFFFFFFFF;



    IOMUX_SW_MUX->GPIO1_IO03 = 0x00000005;
    IOMUX_SW_PAD->GPIO1_IO03  = 0x000010B0;

    GPIO1->GDIR = 0x00000008;
    GPIO1->DR = 0x0;
}

//开灯
void LED_On(void)
{
    GPIO1->DR &= ~(1<<3);
}

//关灯
void LED_Off(void)
{
    GPIO1->DR |=  (1<<3);
}