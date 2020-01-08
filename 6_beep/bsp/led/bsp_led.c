#include "bsp_led.h"

void Led_Init(void)
{
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

