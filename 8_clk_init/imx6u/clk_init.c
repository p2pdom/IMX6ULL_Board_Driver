#include "clk_init.h"

void Imx6ull_Clk_Init(void)
{
    PLL_Init();
    Clock_Tree_Init();
}

/*
 *  按时钟树初始化
 */
void Clock_Tree_Init(void)
{
    ARM_CLK_ROOT_Init();     //528MHz
    MMDC_CLK_ROOT_Init();
    FABRIC_CLK_ROOT_Init();
    AXI_CLK_ROOT_Init();
    AHB_CLK_ROOT_Init();     //132MHz
    PERCLK_CLK_ROOT_Init();  //66MHz
    IPG_CLK_ROOT_Init();     //66MHz
    USDHC1_CLK_ROOT_Init();
    USDHC2_CLK_ROOT_Init();
    BCH_CLK_ROOT_Init();
    GPMI_CLK_ROOT_Init();
    ACLK_EIM_SLOW_CLK_ROOT_Init();
    SPDIF0_CLK_ROOT_Init();
    SAI1_CLK_ROOT_Init();
    SAI2_CLK_ROOT_Init();
    SAI3_CLK_ROOT_Init();
    ESAI_CLK_ROOT_Init();
    LCDIF1_CLK_ROOT_Init();
    EPDC_CLK_ROOT_Init();
    QSPI1_CLK_ROOT_Init();
    ENFC_CLK_ROOT_Init();
    CAN_CLK_ROOT_Init();
    ECSPI_CLK_ROOT_Init();
    UART_CLK_ROOT_Init();
}

void ARM_CLK_ROOT_Init(void)
{
    /*  arm内核时钟，设置为696MHz
     *  PLL1的输出，即pll1_sw_clk经过分频后即为系统的内核时钟
     *  ARM_CLK_ROOT = pll1_main_clk/PODF = 晶振×DIV_SEL/2/PODF = 24*66/2/1 = 792MHz
     */
}

void MMDC_CLK_ROOT_Init(void)
{

}

void FABRIC_CLK_ROOT_Init(void)
{
    /*FABRIC_CLK_ROOT = MMDC_CLK_ROOT*/
}

void AXI_CLK_ROOT_Init(void)
{

}

void AHB_CLK_ROOT_Init(void)
{
    /*
     *  AHB_CLK_ROOT供给PERCLK_CLK_ROOT、IPG_CLK_ROOT时钟源
     *  最小6MHz，最大132MHz
     */

    //设置CBCMR[PRE_PERIPH_CLK_SEL]选择PLL2_PFD2（396MHz）为时钟源头
    CCM_SELF->CBCMR &= ~(3<<18);
    CCM_SELF->CBCMR |=  (1<<18);
    //设置CBCDR[PERIPH_CLK_SEL]将进一步传递（396MHz)
    CCM_SELF->CBCDR &= ~(1<<25);
    while((CCM_SELF->CDHIPR>>5)&0x01); //等待握手信号完成
    while((CCM_SELF->CDHIPR>>2)&0x01); //等待MMDC握手信号完成

#if 0
    /* 修改 AHB_PODF 位的时候需要先禁止 AHB_CLK_ROOT 的输出，但是
     * 我没有找到关闭 AHB_CLK_ROOT 输出的的寄存器，所以就没法设置。
     * 下面设置 AHB_PODF 的代码仅供学习参考不能直接拿来使用！！
     * 内部 boot rom 将 AHB_PODF 设置为了 3 分频，即使我们不设置 AHB_PODF，
     * AHB_ROOT_CLK 也依旧等于 396/3=132Mhz。
     */
    //设置CBCDR[AHB_PODF]分频系数为3（396/3=132MHz）
    CCM_SELF->CBCDR &= ~(7<<10);
    CCM_SELF->CBCDR |=  (2<<10);
    while((CCM_SELF->CDHIPR>>1)&0x01); //等待握手信号完成
#endif
}

void PERCLK_CLK_ROOT_Init(void)
{
    /*
     *  RERCLK_CLK_ROOT供给 EPIT-I2C 外设的时钟
     *  最小3MHz，最大66MHz
     */
    //设置CBCDR[IPG_PODF]使得分频为2将AHB_CLK_ROOT的频率除以二（66MHz）
    CCM_SELF->CBCDR &= ~(3<<8);
    CCM_SELF->CBCDR |=  (1<<8);
    //设置CCM_CSCMR1[PERCLK_CLK_SEL]为0
    CCM_SELF->CSCMR1 &= ~(1<<6);
    //设置CSCMR1[PERCLK_PODF]使得分频为1
    CCM_SELF->CSCMR1 &= ~(0x3F<<0);
}

void IPG_CLK_ROOT_Init(void)
{
    /*
     *  IPG_CLK_ROOT供给 ADC-DOG外设的时钟
     *  最小3MHz，最大66MHz
     */

    /*设置PERCLK_CLK_ROOT的同时已将IPG_CLK_ROOT设置为66MHz*/
}

void USDHC1_CLK_ROOT_Init(void)
{

}

void USDHC2_CLK_ROOT_Init(void)
{

}

void BCH_CLK_ROOT_Init(void)
{

}

void GPMI_CLK_ROOT_Init(void)
{

}

void ACLK_EIM_SLOW_CLK_ROOT_Init(void)
{

}

void SPDIF0_CLK_ROOT_Init(void)
{

}

void SAI1_CLK_ROOT_Init(void)
{

}

void SAI2_CLK_ROOT_Init(void)
{

}

void SAI3_CLK_ROOT_Init(void)
{

}

void ESAI_CLK_ROOT_Init(void)
{

}

void LCDIF1_CLK_ROOT_Init(void)
{

}

void EPDC_CLK_ROOT_Init(void)
{

}

void QSPI1_CLK_ROOT_Init(void)
{

}

void ENFC_CLK_ROOT_Init(void)
{

}

void CAN_CLK_ROOT_Init(void)
{

}

void ECSPI_CLK_ROOT_Init(void)
{

}

void UART_CLK_ROOT_Init(void)
{

}

/*
 *  各个PLL初始化
 */
void PLL_Init(void)
{
    PLL1_Init();
    PLL2_Init();
    PLL3_Init();
}

void PLL1_Init(void)
{
    //将pll1_sw_clk输入信号切换为step_clk
    if(((CCM_SELF->CCSR>>2)&0x01) == 0)
    {
        CCM_SELF->CCSR &= ~(1<<8); //step_clk信号输入源设置为24MHz晶振 CCSR[8]=0
        CCM_SELF->CCSR |=  (1<<2);  
    }
    
    //将pll1_main_clk设置为528MHz PLL output frequency = Fref * DIV_SEL/2 --> 528 = 24*?/2/2
    //要操作的寄存器CCM_ANALOG_PLL_ARM[DIV_SELECT]
    CCM_ANALOG_SELF->PLL_ARM = (1<<13) | ((88<<0) & 0x7F);
    while((CCM_ANALOG_SELF->PLL_ARM>>31) != 1);
    
    //设置ARM_PODF分频为1
    CCM_SELF->CACRR = 0x1;
    while((CCM_SELF->CDHIPR>>16)&0x01); //等待握手信号完成
    //将pll1_sw_clk输入信号切换为pll1_main_clk
    CCM_SELF->CCSR &= ~(1<<2);
}

void PLL2_Init(void)
{
    /*  
     *  PLL2 - System PLL (functional frequency 528 MHz)
     * 
     *  PLL2->528MHz   
     *  PFD0->352MHz -> 528*18/FRAC -> FRAC=27
     *  PFD1->594MHz -> 528*18/FRAC -> FRAC=16 
     *  PFD2->396MHz -> 528*18/FRAC -> FRAC=24
     *  PFD3->297MHz -> 528*18/FRAC -> FRAC=32
     * 
     *  pll2默认将外部24MHz扩大22倍形成528MHz
     *  pfd0~pfd3通过操作CCM_ANALOG_PFD_528n寄存器即可
     */

    unsigned int reg_temp;

    //设置CCM_ANALOG_PFD_528n寄存器
    reg_temp  = CCM_ANALOG_SELF->PFD_528;
    reg_temp &= ~((0x3F<<0)|(0x3F<<8)|(0x3F<<16)|(0x3F<<24)); //将FRAC域置0
    reg_temp |=  ((27<<0)|(16<<8)|(24<<16)|(32<<24)); //配置FRAC域
    reg_temp &= ~((1<<7)|(1<<15)|(1<<23)|(1<<31)); //打开PFD
    CCM_ANALOG_SELF->PFD_528 = reg_temp;
}

void PLL3_Init(void)
{
    /*
     *  PLL3 - USB1 PLL (functional frequency 480 MHz)
     * 
     *  PLL3->480MHz   
     *  PFD0->720MHz   -> 480*18/FRAC -> FRAC=12
     *  PFD1->540MHz   -> 480*18/FRAC -> FRAC=16 
     *  PFD2->508.2MHz -> 480*18/FRAC -> FRAC=17
     *  PFD3->454.7MHz -> 480*18/FRAC -> FRAC=19
     * 
     *  pll3默认将外部24MHz扩大20倍形成480MHz
     *  pfd0~pfd3通过操作CCM_ANALOG_PFD_480n寄存器即可
     */
    unsigned int reg_temp;

    //设置CCM_ANALOG_PFD_480n寄存器
    reg_temp  = CCM_ANALOG_SELF->PFD_480;
    reg_temp &= ~((0x3F<<0)|(0x3F<<8)|(0x3F<<16)|(0x3F<<24)); //将FRAC域置0
    reg_temp |=  ((12<<0)|(16<<8)|(17<<16)|(19<<24)); //配置FRAC域
    reg_temp &= ~((1<<7)|(1<<15)|(1<<23)|(1<<31)); //打开PFD
    CCM_ANALOG_SELF->PFD_480 = reg_temp;
}


