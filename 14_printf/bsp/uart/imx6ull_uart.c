#include "imx6ull_uart.h"

/*
 *  初始化uart1
 *  波特率为115200
 */
void Uart1_Init(void)
{
    /*开启Uart1时钟 */
    CCM->CCGR5 |=  (3u<<24);

    /*初始化IO */
    Uart1_IO_Init();

    /*初始化Uart1 */
    UART1->UCR1 &= ~(1u<<0);  //关闭串口
    UART1->UCR2 &= ~(1u<<0);
    while((UART1->UCR2&0x01)==0);  //软件复位

    /*初始化UCR1 */
    UART1->UCR1 = 0x00;

    /*初始化UCR2 */
    UART1->UCR2 |=  (1u<<1);  //使能接收器
    UART1->UCR2 |=  (1u<<2);  //使能发送器
    UART1->UCR2 &= ~(1u<<3);  //关闭AGTIM中断
    UART1->UCR2 &= ~(1u<<4);  //关闭RTS中断
    UART1->UCR2 |=  (1u<<5);  //8字
    UART1->UCR2 &= ~(1u<<6);  //1个停止位
    UART1->UCR2 &= ~(1u<<8);  //关闭奇偶校验
    UART1->UCR2 &= ~(1u<<11);  //关闭转义
    UART1->UCR2 |=  (1u<<14);  //忽略RTS引脚
    UART1->UCR2 &= ~(1u<<15);  //关闭转义中断

    /*初始化UCR3 */
    UART1->UCR3  = 0;
    UART1->UCR3 |= ((1u<<2)|(1u<<6));  //使RXD引脚复用为输入，启用接收中断

    /*初始化UCR4 */
    UART1->UCR4  = 0;

    /*设置波特率 */
    UART1->UFCR = 5<<7; //ref freq等于ipg_clk/1=80Mhz
	UART1->UBIR = 71;
	UART1->UBMR = 3124;

    UART1->UCR1 |=  (1u<<0);  //使能串口
}

/*
 *  Uart1所使用的IO管脚：
 *      UART1_RX_DATA
 *      UART1_TX_DATA
 */
void Uart1_IO_Init(void)
{
    IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX,0);
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX,0);

    IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX, 0x10B0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX, 0x10B0);
}

void send_character(unsigned char temp)
{
    while(((UART1->USR2>>3) &0X01) == 0);/* 等待上一次发送完成 */
    UART1->UTXD |= temp&0xFF;
    while(((UART1->USR2>>3) &0X01) == 0);/* 等待上一次发送完成 */
}


void send_HelloWorld(void)
{
    unsigned char HelloWorld[] = "Hello World!!\r\n";
    unsigned int number,counter;
    number = sizeof(HelloWorld);

    for(counter=0;counter<number;counter++)
    {
        send_character(HelloWorld[counter]);
    }
    
}
