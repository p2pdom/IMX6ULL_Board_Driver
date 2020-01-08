#include "main.h"

int main(void)
{
    int i = 0;
    unsigned int led_state = 0;
    Imx6ull_Clk_Init();
    Led_Init();
    Beep_Init();
    Bsp_Key_Init();
   
    while (1)
    {
		i++;
		if(i==50)
		{
			i = 0;
			led_state = !led_state;
			if (led_state)
            {
                LED_Off();
            }
            else LED_On();            
		}
		delay(10);
    }
}