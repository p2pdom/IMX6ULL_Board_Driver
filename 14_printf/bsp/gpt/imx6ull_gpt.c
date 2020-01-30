#include "imx6ull_gpt.h"

/*
 *  初始化GPT1计数器，计数频率为1MHz。
 */
void GPT1_Init(void)
{
    /*
     *  GPTx_CR寄存器：
     *      [31] FO3
     *      [30] FO2
     *      [29] FO1：写0无影响，写1使得输出比较引脚按着OMn的设置强制活动
     *      [26-28] OM3
     *      [23-25] OM2
     *      [20-22] OM1：设置输出比较，00->关闭输出比较
     *      [18-19] IM2
     *      [16-17] IM1：设置中断捕获，00->关闭中断捕获
     *      [15] 软件复位：
     *      [11-14] 保留
     *      [10] 24MHz clock控制：0->关闭24MHz时钟
     *      [9] Free-Run或Restart mode：用于输入捕获，设置为1
     *      [6-8] GPT时钟选择: 001->Peripheral Clock (ipg_clk)
     *      [5] GPT Stop模式：0->关闭Stop模式
     *      [4] GPT Doze模式：0->关闭Doze模式
     *      [3] GPT Wait模式：0->关闭等待模式
     *      [2] GPT debug模式：0->关闭debug模式
     *      [1] GPT使能模式：1->使能后从0开始计数
     *      [0] GPT使能控制：0-关闭 1-使能
     */
    GPT1->CR &= ~(1u<<0);  //关闭GPT1
    GPT1->CR |=  (1u<<15);
    while((GPT1->CR>>15)&0x01);  //软件复位
    GPT1->CR |=  (1u<<1);  //GPT1使能后，从0开始向上计数
    GPT1->CR |=  (0x1u<<6);  //选择IPG_CLK为GPT1时钟源

    GPT1->PR |=  (65u<<0);

    GPT1->CR |=  (1u<<0);  //使能GPT1
}

void gpt1_delay_ms(unsigned int temp)
{
    /*
     *  记1个数所需要的时间为1/1000000s即1/1000ms
     *  那么记（temp）ms需要temp*1000个数
     *  计数器最大为0xFFFFFFFF，即规定最大定时不超过1000ms
     */
    unsigned int count_aim,count_start,count;
    GPT1->SR |=  (1u<<5);
    count_aim = temp*1000;
    count_start = GPT1->CNT;
    do
    {
        if((GPT1->SR>>5)&0x01)
        {
            count  = (0xFFFFFFFF-count_start);
            count += GPT1->CNT;
        }
        else
        {
            count = GPT1->CNT - count_start;
        }
        
    } while (count_aim>count);
    
    GPT1->SR |=  (1u<<5);
}

