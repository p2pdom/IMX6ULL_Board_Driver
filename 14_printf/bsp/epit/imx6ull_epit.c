#include "imx6ull_epit.h"

/*
 *  参数说明：
 *      prescalar  ：时钟分频值
 *      lr_value   ：重加载寄存器值
 *      cmpr_value ：比较寄存器值
 */
void EPIT1_Init(unsigned int prescalar, unsigned int lr_value, unsigned int cmpr_value)
{
    if(prescalar > 0xFFF)
    {
        prescalar = 0xFFF;
    }

    //EPIT外设初始化
    /*
     *  EPITx_CR寄存器：
     *      [26-31] 保留
     *      [24-25] 时钟源选择 = 01：选择IPG时钟66MHz
     *      [22-23] 设置EPIT输出 = 00：关闭输出
     *      [21] 设置EPIT是否为停止模式 = 0：EPIT关闭停止模式
     *      [20] 保留
     *      [19] 设置EPIT是否为等待模式 = 0：EPIT关闭等待模式
     *      [18] 设置EPIT是否为debug模式
     *      [17] EPIT覆盖写入使能 = 1：更改load register寄存器后立即更改计数器值
     *      [16] 软件复位    
     *      [4-15] 分频
     *      [3] RLD位 = 1
     *      [2] 比较中断使能位 = 1：比较中断使能
     *      [1] EPIT使能模式 = 1：EPIT从load value（RLD=1）的值开始计数或从0xFFFFFFFF(RLD=0)的值开始计数
     *      [0] EPIT使能位   = 1：EPIT使能
     */
    EPIT1->CR &= ~(1u<<0);  //关闭EPIT1
    EPIT1->CR |=  (1u<<16);  //进行软件复位,默认CR寄存器全为0
    while((EPIT1->CR>>16)&0x01);  //等待软件复位结束

    EPIT1->CR &= ~(3u<<24);
    EPIT1->CR |=  (1u<<24);  //设置时钟为IPG时钟
    EPIT1->CR &= ~(3u<<22);  //EPIT1输出管脚关闭
    EPIT1->CR &= ~(1u<<21);  //EPIT1关闭停止模式
    EPIT1->CR &= ~(1u<<19);  //EPIT1关闭等待模式
    EPIT1->CR &= ~(1u<<18);  //不激活debug模式
    EPIT1->CR |=  (1u<<17);  //重加载寄存器值更改后立即修改计数器值
    EPIT1->CR &= ~(0xFFF<<4);
    EPIT1->CR |=  (prescalar<<4);  //设置分频值
    EPIT1->CR |=  (1u<<3);  //设置计数器为set-and-forget模式
    EPIT1->CR |=  (1u<<1);  //启动计数器后，从重加载寄存器中读取值

    /*设置重加载寄存器 */
    EPIT1->LR = lr_value;

    /*设置比较寄存器 */
    EPIT1->CMPR = cmpr_value;

    /*EPIT中断初始化 */
    GIC_EnableIRQ(EPIT1_IRQn);
    sys_irqhandler_register(EPIT1_IRQn, (system_irq_handler_t)epit1_irqHandler, NULL);

    EPIT1->CR |=  (1u<<2);  //开启比较使能中断
    //EPIT1->CR |=  (1u<<0);  //开启EPIT1计数器
}

void epit1_irqHandler(unsigned int gicciar, void *param)
{
    EPIT1->CR &= ~(1u<<0);
    if((EPIT1->SR)&0x01)
    {
        if(gpio_pin_read(GPIO1, 18)==GPIO_Level_low)
        {
        }               
    }
    EPIT1->SR |=  (1u<<0);
}

