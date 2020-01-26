#include "bsp_led.h"

void Led_Init(void)
{
    /*开启GPIO1时钟*/
    CCM->CCGR1 &= ~(3<<26);
    CCM->CCGR1 |=  (3<<26);
    /*函数初始化IO*/
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0X10B0);

    GPIO1->GDIR |= (1<<3);
    GPIO1->DR   |= (1<<3);
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

