#include "main.h"

int main(void)
{
    Int_Init();     //中断初始化
    Imx6ull_Clk_Init();
    
    Led_Init();
    Beep_Init();
    Bsp_Key_Init();
    
    Bsp_Key_Init_withInterrupt();
   
    while (1)
    {
        LED_On();
        delay(500);
        LED_Off();
        delay(500);
    }
}