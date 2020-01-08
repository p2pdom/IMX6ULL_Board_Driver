#include "main.h"

int main(int argc, char *argv[])
{
    clk_all_enable();
    Led_Init();

    while (1)
    {
        LED_Off();
        delay(300);
        LED_On();
        delay(300);
    }
}
