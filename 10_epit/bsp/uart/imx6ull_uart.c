#include "imx6ull_uart.h"

void Uart1_Init(void)
{
    //变量定义
    volatile unsigned int CCM_CCGR5 = *((volatile unsigned int *)0x020C407C);

    volatile unsigned int IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA = *((volatile unsigned int *)0x020E0088);
    volatile unsigned int IOMUXC_SW_PAD_CTL_PAD_UART1_RX_DATA = *((volatile unsigned int *)0x020E0314);

    volatile unsigned int IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA = *((volatile unsigned int *)0x020E0084);
    volatile unsigned int IOMUXC_SW_PAD_CTL_PAD_UART1_TX_DATA = *((volatile unsigned int *)0x020E0310);
   /*   uart管脚说明
    *   UART1_RX_DATA：GPIO1_IO17 ALT0
    *   UART1_TX_DATA：GPIO1_IO16 ALT0
    */       
    //设置UART1_RX_DATA管脚复用
    IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA &= ~(0x1F<<0);
    IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA |=  (0x00<<0);
    //设置UART1_RX_DATA管脚属性
    IOMUXC_SW_PAD_CTL_PAD_UART1_RX_DATA  = 0;
    IOMUXC_SW_PAD_CTL_PAD_UART1_RX_DATA  = IOMUXC_SW_PAD_CTL_PAD_UART1_RX_DATA |0x1041;

    //设置UART1_TX_DATA管脚复用
    IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA &= ~(0x1F<<0);
    IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA |=  (0x00<<0);
    //设置UART1_TX_DATA管脚属性
    IOMUXC_SW_PAD_CTL_PAD_UART1_TX_DATA  = 0;
    IOMUXC_SW_PAD_CTL_PAD_UART1_TX_DATA  = IOMUXC_SW_PAD_CTL_PAD_UART1_TX_DATA |0x1041;

    //开启UART1时钟
    CCM_CCGR5 |=  (3<<24);
    UART1_SELF->UCR1 &= ~(1<<0);  //关闭UART1

    UART1_SELF->UCR2 &= ~(1<<0);
    while((UART1_SELF->UCR2 & 0x01)==0);  //软件复位UART1

    /* 初始化UART1*/
    UART1_SELF->UCR1  = 0;
    UART1_SELF->UCR2 |=  ((1<<1)|(1<<2)|(1<<5)|(1<<14));
    UART1_SELF->UCR2 &= ~((1<<6)|(1<<8));
    UART1_SELF->UCR3 |= 1<<2;

    /*设置波特率*/
    UART1_SELF->UFCR = 5<<7; /* ref freq 等于 ipg_clk/1=80Mhz */
    UART1_SELF->UBIR = 71;
    UART1_SELF->UBMR = 3124;

    UART1_SELF->UCR1 |=  (1<<0);  //使能UART1

}

void putc_self(unsigned char c)
{
    while(((UART1_SELF->USR2 >> 3) &0X01) == 0);/* 等待上一次发送完成 */
    UART1_SELF->UTXD = c & 0XFF; /* 发送数据 */
}

void puts_self(char *str)
{
    char *p = str;
    while(*p)
    putc_self(*p++);
}

void print_reg(volatile unsigned int reg)
{

}

