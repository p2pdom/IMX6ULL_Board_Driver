#include "bsp_key.h"

void inside_key_delay(volatile unsigned int n) 
{
    unsigned int temp = 0x7FF;
    while(n--)
    {
        while (temp--);
    }
}

void Bsp_Key_Init(void)
{
    //时钟使能
    CCM->CCGR1 &= ~(3<<26);
    CCM->CCGR1 |=  (3<<26);

    //配置管脚复用和管脚属性
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    //设置GPIO1_IO18为输入
    GPIO1->GDIR &= ~(1<<18);
}

u8 Bsp_Key_Getvalue(u8 mode)
{
    u8 temp = KEY_LOOSE;
    if(KEY_VALUE == 0)
    {
        inside_key_delay(10);
        if (KEY_VALUE == 0)
        {
            temp = KEY_PRESS;
        }
    }
    else temp = KEY_LOOSE;
    if(mode == LOOSE_RETURN)
    {
        while(KEY_VALUE == 0);
    }
    return temp;
}


/*使用中断的函数*/
void Bsp_Key_Init_withInterrupt(void)
{
    gpio_pin_config_t gpioPinConfig;

    //配置管脚复用和管脚电气属性
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    //初始化GPIO
    gpioPinConfig.direction = GPIO_DigitalInput;
    gpioPinConfig.interruptMode = GPIO_IntFallingEdge; 
    gpioPinConfig.outputLogic = GPIO_Level_high;
    gpio_init(GPIO1, 18, &gpioPinConfig);
    //使能GIC中断、注册中断服务函数、使能对应中断管脚
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    sys_irqhandler_register(GPIO1_Combined_16_31_IRQn, (system_irq_handler_t)gpio1_io18_irqHandler, NULL);
    gpio_pin_interrupt_enable(GPIO1, 18);  //开启GPIOn_pin管脚中断
}

/*中断服务函数 */
void gpio1_io18_irqHandler(unsigned int gicciar, void *param)
{
    EPIT1->CR |=  (1u<<0);
    gpio_clear_interruptFlags(GPIO1, 18);
}
