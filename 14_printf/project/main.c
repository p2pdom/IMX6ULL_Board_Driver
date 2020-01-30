#include "main.h"

#define read_reg *((volatile unsigned int *)0x021b0850)

int main(void)
{
    unsigned char state;
    state = 0;

    Int_Init();     //中断初始化
    Imx6ull_Clk_Init();
    
    Led_Init();
    Beep_Init();
    Bsp_Key_Init();
    Bsp_Key_Init_withInterrupt();
    EPIT1_Init(0, 66000*30, 0);
    GPT1_Init();
    Uart1_Init();
   
    while (1)
    {
        state = !state;
        LED_State_Switch(state);
        printf("0x%x\r\n",read_reg);
        gpt1_delay_ms(500);
    }
}

