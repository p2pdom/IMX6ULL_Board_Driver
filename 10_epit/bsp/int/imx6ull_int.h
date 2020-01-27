#ifndef __IMX6ULL_INT_H
#define __IMX6ULL_INT_H

//头文件包含
#include "imx6ull.h"
#include "bsp_led.h"

typedef void (*system_irq_handler_t)(unsigned int gicciar, void *param);


/*中断处理函数结构体 */
typedef struct _sys_irq_handler
{
    system_irq_handler_t irqHandler;  /*中断处理函数    */
    void *userParam;                  /*中断处理函数参数 */
}sys_irq_handler_t;


//函数声明
void Int_Init(void);
void system_irqTable_init(void);
void default_irqhandler(unsigned int giccIar, void *userParam);

void sys_irqhandler_register(unsigned int irq_number, system_irq_handler_t functionName, void *parameter);
void system_irqhandler(volatile unsigned int regtemp);


#endif // !__IMX6ULL_INT_H


