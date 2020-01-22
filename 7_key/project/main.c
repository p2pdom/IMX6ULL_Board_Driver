#include "main.h"

int main(int argc, char *argv[])
{
    clk_all_enable();
    Led_Init();
    Beep_Init();
    Bsp_Key_Init();

    while (1)
    {
        if(Bsp_Key_Getvalue(PRESS_RETURN) == KEY_PRESS)
        {
            LED_On();
            Beep_set_status(BEEP_ON);
        }
        if(Bsp_Key_Getvalue(PRESS_RETURN) == KEY_LOOSE)
        {
            LED_Off();
            Beep_set_status(BEEP_OFF);
        }
    }
}
