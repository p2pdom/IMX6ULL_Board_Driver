#include "main.h"

int main(void)
{

    Imx6ull_Clk_Init();
    Led_Init();
    Beep_Init();
    Bsp_Key_Init();
   
    while (1)
    {

        LED_Off();
        delay(300);   
        LED_On();            
		delay(300);
    }
}