#include "main.h"

int main(int argc, char *argv[])
{
    Led_Init();

    while (1)
    {
        LED_Off();
        delay(300);
        LED_On();
        delay(300);
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

    /*函数初始化IO*/
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0 );
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0x10B0);

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