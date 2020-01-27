#include "main.h"

int main(void)
{
    Int_Init();     //中断初始化
    Imx6ull_Clk_Init();
    
    Led_Init();
    Beep_Init();
    Bsp_Key_Init();

    EPIT1_Init(0, 33000000, 0);
   
    while (1)
    {
    }
}

