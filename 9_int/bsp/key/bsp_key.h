/*
 *  KEY外设说明：
 *      管脚：原理图上为KEY0，UART1_CTS
 *           芯片手册为 GPIO1_IO18
 * 
 */

#ifndef __BSP_KEY_H
#define __BSP_KEY_H

//寄存器宏定义
#define CCM_CCGR1 *((volatile unsigned int *)0x020C406C)
#define KEY_MUX IOMUXC_SW_MUX_CTL_PAD_UART1_CTS_B
#define IOMUXC_SW_MUX_CTL_PAD_UART1_CTS_B *((volatile unsigned int *)0x020E008C)
#define KEY_PAD IOMUXC_SW_PAD_CTL_PAD_UART1_CTS_B
#define IOMUXC_SW_PAD_CTL_PAD_UART1_CTS_B *((volatile unsigned int *)0x020E0318)
#define GPIO1_DR   *((volatile unsigned int *)0x0209C000)
#define GPIO1_GDIR *((volatile unsigned int *)0x0209C004)    

//必要值定义
typedef unsigned char u8;
#define KEY_PRESS 0
#define KEY_LOOSE 1
#define PRESS_RETURN 1
#define LOOSE_RETURN 0

//宏定义型函数
#define KEY_VALUE ((GPIO1_DR>>18)&0x01)

//function declaration
void Bsp_Key_Init(void);
u8 Bsp_Key_Getvalue(u8 mode);

#endif // !__BSP_KEY_H

