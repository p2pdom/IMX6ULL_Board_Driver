#include "bsp_beep.h"

/*
 *  SNVS_TAMPER1即GPIO5_IO1管脚
 *  高电平打开、低电平关闭
 */

void Beep_Init(void)
{
    //开启时钟
    CCM->CCGR1 &= ~(3<<30);
    CCM->CCGR1 |=  (3<<30); 
   
    //设置管脚属性
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0X10B0);

    //讲GPIO5_IO1设置为输出
    GPIO5->GDIR &= ~(1<<1);
    GPIO5->GDIR |=  (1<<1);

    //默认设置BEEP关闭
    GPIO5->DR |= (1<<1);
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

