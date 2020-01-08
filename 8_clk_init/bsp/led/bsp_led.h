#ifndef __BSP_LED_H
#define __BSP_LED_H

/*寄存器定义*/
#define CCM_CCGR1 *((volatile unsigned int *)0x020C406C)
#define LED0_MUX IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03
#define IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 *((volatile unsigned int *)0x020E0068)
#define LED0_PAD IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03
#define IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 *((volatile unsigned int *)0x020E02F4)
#define GPIO1_DR   *((volatile unsigned int *)0x0209C000)
#define GPIO1_GDIR *((volatile unsigned int *)0x0209C004)

//function declaration
void Led_Init(void);
void LED_On(void);
void LED_Off(void);


#endif // !__BSP_LED_H