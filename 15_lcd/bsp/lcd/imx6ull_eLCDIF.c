#include "imx6ull_eLCDIF.h"

unsigned int frame_buffer0[LCD_SIZE];
unsigned int frame_buffer1[LCD_SIZE];

void eLCDIF_Init(void)
{
    /*时钟已配置为51.2MHz */

    /*使能eLCDIF */
    CCM->CCGR2 |=  (3u<<28);  //lcd_clk_enable
    CCM->CCGR3 |=  (3u<<10);  //lcdif1_pix_clk_enable

    /*软件复位 */
    LCDIF->CTRL  =  (1u<<31);  //强制复位
    gpt1_delay_ms(10);
    LCDIF->CTRL  =  (0u<<31);  //取消强制复位

    /*初始化eLCDIF控制寄存器组 */
    //LCDIF_CTRLn
    LCDIF->CTRL &= ~(1u<<1);   //ALL_24_BITS_VALID -> Used only when WORD_LENGTH = 3
    LCDIF->CTRL |=  (1u<<5);   //Set this bit to make the eLCDIF act as a bus master
    LCDIF->CTRL |=  (3u<<8);   //24_BIT — Input data is 24 bits per pixel.
    LCDIF->CTRL |=  (3u<<10);  //24_BIT — 24-bit data bus mode.

    LCDIF->CTRL &= ~(3u<<12);  //CSC_DATA_SWIZZLE
    LCDIF->CTRL &= ~(3u<<14);  //INPUT_DATA_SWIZZLE

    LCDIF->CTRL |=  (1u<<17);  //DOTCLK_MODE
    LCDIF->CTRL &= ~(1u<<18);  //不为VSYNC_MODE
    LCDIF->CTRL |=  (1u<<19);  //BYPASS_COUNT
    LCDIF->CTRL &= ~(1u<<20);  //不为DVI_MODE    
    LCDIF->CTRL &= ~(0x1Fu<<21);  //传输数据不发生移位
    LCDIF->CTRL &= ~(1u<<26);  //数据移位方向，随便填一个
    LCDIF->CTRL &= ~(1u<<27);  //WAIT_FOR_VSYNC_EDGEtemp
    //LCDIF_CTRL1n
    LCDIF->CTRL1 &= ~(0xFu<<16);
    LCDIF->CTRL1 |=  (0x7u<<16);

    //LCDIF_CTRL2n 默认0x00000000 没修改

    //LCDIF_TRANSFER_COUNT
    LCDIF->TRANSFER_COUNT = ((height<<16)|(width<<0));

    /*配置显存地址 */
    LCDIF->CUR_BUF  = (unsigned int)frame_buffer_0;
    LCDIF->NEXT_BUF = (unsigned int)frame_buffer_0;

    //LCDIF_VDCTRL0n
    LCDIF->VDCTRL0 = 0;
    LCDIF->VDCTRL0 = ((vspw<<0)|(1<<20)|(1<<21)|(1<<24)|(0<<25)|(0<<26)|(0<<27)|(1<<28)|(0<<29));

    //LCDIF_VDCTRL1
    LCDIF->VDCTRL1 = vbpd + height + vfpd + vspw;

    //LCDIF_VDCTRL2
    LCDIF->VDCTRL2 = ((hspw<<18)|(hbpd+width+hfpd+hspw));

    //LCDIF_VDCTRL3
    LCDIF->VDCTRL3 = (vbpd+vspw)|((hbpd+hspw)<<16);

    //LCDIF_VDCTRL4
    LCDIF->VDCTRL4 = width|(1<<18);

    Enable_eLCDIF();
    gpt1_delay_ms(10);
}


void Enable_eLCDIF(void)
{
    LCDIF->CTRL |=  (1u<<0);
}
