#include "imx6ull_int.h"


/* 中断嵌套计数器 */
static unsigned int irqNesting;
/*中断处理函数表 */
static sys_irq_handler_t irqTable[NUMBER_OF_INT_VECTORS];


/*中断初始化 */
void Int_Init(void)
{
    GIC_Init();
    system_irqTable_init();
    /*中断向量偏移设置 */
    //__set_VBAR(0x87800000);
}

//中断向量表初始化
void system_irqTable_init(void)
{
    unsigned int temp;

    irqNesting = 0;
    for(temp=0;temp<NUMBER_OF_INT_VECTORS;temp++)
    {
        irqTable[temp].irqHandler = default_irqhandler;
        irqTable[temp].userParam  = NULL;
    }
}
void default_irqhandler(unsigned int giccIar, void *userParam) 
{
	while(1) 
    {}
}


//中断服务函数注册
void sys_irqhandler_register(unsigned int irq_number, system_irq_handler_t functionName, void *parameter)
{
    irqTable[irq_number].irqHandler = functionName;
    irqTable[irq_number].userParam  = parameter;
}


void system_irqhandler(unsigned int giccIar)
{
   unsigned int intNum = giccIar & 0x3FFUL;
   /* 检查中断号是否符合要求 */
   if (intNum >= NUMBER_OF_INT_VECTORS)
   {
	 	return;
   }
 
   irqNesting++;	/* 中断嵌套计数器加一 */

   /* 根据传递进来的中断号，在irqTable中调用确定的中断服务函数*/
   irqTable[intNum].irqHandler(intNum, irqTable[intNum].userParam);
 
   irqNesting--;	/* 中断执行完成，中断嵌套寄存器减一 */
}





