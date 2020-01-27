#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "imx6ull.h"

//function declaration
void Led_Init(void);
void LED_On(void);
void LED_Off(void);
void LED_State_Switch(unsigned char state);


#endif // !__BSP_LED_H