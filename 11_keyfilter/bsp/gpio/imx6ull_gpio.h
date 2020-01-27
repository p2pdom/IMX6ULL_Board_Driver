#ifndef __IMX6ULL_GPIO_H
#define __IMX6ULL_GPIO_H

#include "imx6ull.h"

/*GPIO方向 */
typedef enum _gpio_pin_direction
{
    GPIO_DigitalInput  = 0U,  		/* 输入 */
    GPIO_DigitalOutput = 1U, 		/* 输出 */
}gpio_pin_direction_t;

/*GPIO电平 */
typedef enum _gpio_pin_level
{
    GPIO_Level_low  = 0u,
    GPIO_Level_high = 1u,
}gpio_pin_level_t;

/*GPIO中断方式 */
typedef enum _gpio_interrupt_mode
{
    GPIO_NoIntmode      = 0U, 		    /* 无中断功能 */
    GPIO_IntLowLevel    = 1U, 			/* 低电平触发	*/
    GPIO_IntHighLevel   = 2U, 			/* 高电平触发 */
    GPIO_IntRisingEdge  = 3U, 			/* 上升沿触发	*/
    GPIO_IntFallingEdge = 4U, 			/* 下降沿触发 */
    GPIO_IntRisingOrFallingEdge = 5U, 	/* 上升沿和下降沿都触发 */
}gpio_interrupt_mode_t;

/*GPIO配置结构体 */
typedef struct
{
    gpio_pin_direction_t  direction;      //输出方向
    gpio_pin_level_t      outputLogic;    //默认输出电平
    gpio_interrupt_mode_t interruptMode;  //中断方式
}gpio_pin_config_t;



//function declaration
void gpio_init(GPIO_Type *base, unsigned int pin,  gpio_pin_config_t *config);
void gpio_interrupt_config(GPIO_Type *base, unsigned int pin, gpio_interrupt_mode_t interruptMode);

void gpio_pin_interrupt_enable(GPIO_Type *base, unsigned int pin);
void gpio_pin_interrupt_disable(GPIO_Type *base, unsigned int pin);

void gpio_clear_interruptFlags(GPIO_Type* base, unsigned int pin);

void gpio_pin_set(GPIO_Type *base, unsigned int pin, gpio_pin_level_t outputLogic);
unsigned int gpio_pin_read(GPIO_Type *base, unsigned int pin);

#endif
