#ifndef __IMX6ULL_EPIT_H
#define __IMX6ULL_EPIT_H

#include "imx6ull.h"
#include "imx6ull_int.h"
#include "imx6ull_gpio.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_lcd.h"
#include "printf.h"

//function declaration
void EPIT1_Init(unsigned int prescalar, unsigned int lr_value, unsigned int cmpr_value);
void epit1_irqHandler(unsigned int gicciar, void *param);

#endif

