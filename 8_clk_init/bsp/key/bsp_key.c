#include "bsp_key.h"

void inside_key_delay(volatile unsigned int n) 
{
    unsigned int temp;
    while(n--)
    {
        while (temp--);
    }
}

void Bsp_Key_Init(void)
{
    //时钟使能
    CCM_CCGR1 &= ~(3<<26);
    CCM_CCGR1 |=  (3<<26);

    //配置管脚复用和管脚属性
    KEY_MUX &= ~(0x1F<<0);
    KEY_MUX |=  (0x05<<0);

    KEY_PAD  = 0xF000;

    //设置GPIO1_IO18为输入
    GPIO1_GDIR &= ~(1<<18);
}

u8 Bsp_Key_Getvalue(u8 mode)
{
    u8 temp = KEY_LOOSE;
    if(KEY_VALUE == 0)
    {
        inside_key_delay(10);
        if (KEY_VALUE == 0)
        {
            temp = KEY_PRESS;
        }
    }
    else temp = KEY_LOOSE;
    if(mode == LOOSE_RETURN)
    {
        while(KEY_VALUE == 0);
    }
    return temp;
}

