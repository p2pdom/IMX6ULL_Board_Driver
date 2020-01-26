#ifndef __BSP_BEEP_H
#define __BSP_BEEP_H

#include "imx6ull.h"

/*寄存器定义*/


/*参数宏定义*/
#define BEEP_ON  1
#define BEEP_OFF 0

//宏定义型函数
#define Beep_On()  (GPIO5->DR &= ~(1<<1))
#define Beep_Off() (GPIO5->DR |=  (1<<1))

//function declaration
void Beep_Init(void);
void Beep_set_status(char status);


#endif // !__BEEP_H

