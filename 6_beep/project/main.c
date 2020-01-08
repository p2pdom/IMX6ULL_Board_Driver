#include "main.h"

int main(int argc, char *argv[])
{
    clk_all_enable();
    Led_Init();
    Beep_Init();

    while (1)
    {
        LED_Off();
        Beep_set_status(BEEP_OFF);
        delay(1000);
        LED_On();
        Beep_set_status(BEEP_ON);
        delay(1000);
    }
}
