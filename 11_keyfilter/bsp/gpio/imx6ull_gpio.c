#include "imx6ull_gpio.h"


void gpio_init(GPIO_Type *base, unsigned int pin,  gpio_pin_config_t *config)
{
    gpio_pin_interrupt_disable(base, pin);  //关闭GPIOn_pin管脚的中断

    //配置输入输出
    if(config->direction == GPIO_DigitalInput)
    {
        base->GDIR &= ~(1u<<pin);
    }
    else if(config->direction == GPIO_DigitalOutput)
    {
        base->GDIR |=  (1u<<pin);
        gpio_pin_set(base, pin, config->outputLogic);
    }
    gpio_interrupt_config(base, pin, config->interruptMode);

}

/*中断初始化函数 */
void gpio_interrupt_config(GPIO_Type *base, unsigned int pin, gpio_interrupt_mode_t interruptMode)
{
    volatile unsigned int *icr;
    unsigned int icrShift;
    
    icrShift = pin;
    base->EDGE_SEL &= ~(1u<<pin);  //关闭边沿中断

    if(pin < 16)
    {
        icr = &(base->ICR1);
    }
    else
    {
        icr = &(base->ICR2);
        icrShift -= 16;
    }

    switch (interruptMode)
    {
    case GPIO_NoIntmode:
        base->IMR &= ~(1u<<pin);  //关闭GPIOx_pin管脚的中断
        break;

    case GPIO_IntLowLevel:
        *icr &= ~(3u << (icrShift*2));  //00：低电平中断
        break;
    
    case GPIO_IntHighLevel:
        *icr &= ~(3u << (icrShift*2));
        *icr |=  (1u << (icrShift*2));  //01：高电平中断
        break;

    case GPIO_IntRisingEdge:
        *icr &= ~(3u << (icrShift*2));
        *icr |=  (2u << (icrShift*2));  //10：上升沿中断
        break;

    case GPIO_IntFallingEdge:
        *icr |=  (3u << (icrShift*2));  //11：下降沿中断
        break;

    case GPIO_IntRisingOrFallingEdge:
        base->EDGE_SEL |=  (1u<<pin);   //设置边沿中断
        break;

    default:
        break;
    }
}

void gpio_pin_interrupt_enable(GPIO_Type *base, unsigned int pin)
{
    base->IMR |=  (1u << pin);
}
void gpio_pin_interrupt_disable(GPIO_Type *base, unsigned int pin)
{
    base->IMR &= ~(1u << pin);
}

void gpio_clear_interruptFlags(GPIO_Type* base, unsigned int pin)
{
    base->ISR |= (1u << pin);
}


/*GPIO管脚设置函数 */
void gpio_pin_set(GPIO_Type *base, unsigned int pin, gpio_pin_level_t outputLogic)
{
    if(outputLogic == 0u)
    {
        base->DR &= ~(1u<<pin);
    }
    else if(outputLogic == 1u)
    {
        base->DR |=  (1u<<pin);
    }
}

unsigned int gpio_pin_read(GPIO_Type *base, unsigned int pin)
{
    return ((base->DR >> pin)&0x01);
}
