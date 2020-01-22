#include "bsp_led.h"

void Led_Init(void)
{
    /*开启GPIO1时钟*/
    CCM_CCGR1 &= ~(3<<26);
    CCM_CCGR1 |=  (3<<26);
    /*函数初始化IO*/
    LED0_MUX = 0x5;
    LED0_PAD = 0x10B0;

    GPIO1_GDIR |= (1<<3);
    GPIO1_DR   |= (1<<3);
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

