#ifndef __IMX6ULL_ELCDIF_H
#define __IMX6ULL_ELCDIF_H

#include "imx6ull.h"
#include "imx6ull_gpt.h"
#include "bsp_lcd.h"
#include "bsp_led.h"

extern unsigned int frame_buffer0[];
extern unsigned int frame_buffer1[];

void eLCDIF_Init(void);
void Enable_eLCDIF(void);

#endif // !__IMX6ULL_ELCDIF_H

