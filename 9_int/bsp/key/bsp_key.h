/*
 *  KEY外设说明：
 *      管脚：原理图上为KEY0，UART1_CTS
 *           芯片手册为 GPIO1_IO18
 * 
 */

#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "imx6ull.h"

#include "imx6ull_gpio.h"
#include "imx6ull_int.h"

#include "bsp_beep.h"
 
//必要值定义
typedef unsigned char u8;
#define KEY_PRESS 0
#define KEY_LOOSE 1
#define PRESS_RETURN 1
#define LOOSE_RETURN 0

//宏定义型函数
#define KEY_VALUE ((GPIO1->DR>>18)&0x01)

//function declaration
void Bsp_Key_Init(void);
u8 Bsp_Key_Getvalue(u8 mode);

void Bsp_Key_Init_withInterrupt(void);
void gpio1_io18_irqHandler(unsigned int gicciar, void *param);
#endif // !__BSP_KEY_H

