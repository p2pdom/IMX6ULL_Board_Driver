#ifndef __BSP_LED_H
#define __BSP_LED_H


#include "MCIMX6Y2.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"

//function declaration
void Led_Init(void);
void LED_On(void);
void LED_Off(void);


#endif // !__BSP_LED_H