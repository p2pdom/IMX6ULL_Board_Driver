#ifndef __IMX6ULL_UART_H
#define __IMX6ULL_UART_H

//头文件包含
#include "imx6ull.h"
#include "imx6ull_gpio.h"


//function declaration
void Uart1_Init(void);
void Uart1_IO_Init(void);

void send_character(unsigned char temp);
void send_HelloWorld(void);

#endif

