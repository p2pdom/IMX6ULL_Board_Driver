#include "beep.h"

/*
 *  SNVS_TAMPER1即GPIO5_IO1管脚
 *  高电平打开、低电平关闭
 */

void Beep_Init(void)
{
    //开启时钟
    CCGR1 &= ~(3<<30);
    CCGR1 |=  (3<<30);    

    //设置管脚属性
    BEEP_MUX &= ~(0xF<<0);
    BEEP_MUX |=  (0x5<<0);
    
    BEEP_PAD  = 0x9;

    //讲GPIO5_IO1设置为输出
    GPIO5_GDIR &= ~(1<<1);
    GPIO5_GDIR |=  (1<<1);

    //默认设置BEEP关闭
    GPIO5_DR |= (1<<1);
}

/*
 *  蜂鸣器状态设置函数
 *  参数：status
 *          BEEP_ON  ：关闭蜂鸣器
 *          BEEP_OFF ：打开蜂鸣器
 */
void Beep_set_status(char status)
{
    switch (status)
    {
    case BEEP_ON:
        Beep_On();
        break;
    
    case BEEP_OFF:
        Beep_Off();
        break;

    default:
        break;
    }
}

