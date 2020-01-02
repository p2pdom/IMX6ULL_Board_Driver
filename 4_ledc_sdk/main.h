#ifndef __MAIN_H
#define __MAIN_H

#include "MCIMX6Y2.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"

/*函数定义*/
void Led_Init(void);
void delay_short(volatile  unsigned int n);
void delay(volatile unsigned int n);

void LED_On(void);
void LED_Off(void);

#endif // ! __MAIN_H