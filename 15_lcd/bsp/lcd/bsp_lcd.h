#ifndef __BSP_LCD_H
#define __BSP_LCD_H

#include "imx6ull.h"
#include "imx6ull_gpio.h"
#include "imx6ull_eLCDIF.h"


/* 颜色 */
#define LCD_BLUE		  0x000000FF
#define LCD_GREEN		  0x0000FF00
#define LCD_RED 		  0x00FF0000
#define LCD_CYAN		  0x0000FFFF
#define LCD_MAGENTA 	  0x00FF00FF
#define LCD_YELLOW		  0x00FFFF00
#define LCD_LIGHTBLUE	  0x008080FF
#define LCD_LIGHTGREEN	  0x0080FF80
#define LCD_LIGHTRED	  0x00FF8080
#define LCD_LIGHTCYAN	  0x0080FFFF
#define LCD_LIGHTMAGENTA  0x00FF80FF
#define LCD_LIGHTYELLOW   0x00FFFF80
#define LCD_DARKBLUE	  0x00000080
#define LCD_DARKGREEN	  0x00008000
#define LCD_DARKRED 	  0x00800000
#define LCD_DARKCYAN	  0x00008080
#define LCD_DARKMAGENTA   0x00800080
#define LCD_DARKYELLOW	  0x00808000
#define LCD_WHITE		  0x00FFFFFF
#define LCD_LIGHTGRAY	  0x00D3D3D3
#define LCD_GRAY		  0x00808080
#define LCD_DARKGRAY	  0x00404040
#define LCD_BLACK		  0x00000000
#define LCD_BROWN		  0x00A52A2A
#define LCD_ORANGE		  0x00FFA500
#define LCD_TRANSPARENT   0x00000000

/*屏幕参数定义 */
#define LCD_SIZE 1024*600
#define height      600    /*屏幕高度 */
#define width       1024  /*屏幕宽度 */
#define pixel_byte  4     /*像素位数 */

#define vspw 3
#define vbpd 20
#define vfpd 12
#define hspw 20
#define hbpd 140
#define hfpd 160

#define frame_buffer_0 frame_buffer0  /*显存地址1 */
#define frame_buffer_1 frame_buffer1 /*显存地址2 */

#define forecolor  LCD_BLACK /*前景色 */
#define backcolor  LCD_WHITE /*背景色 */



void Lcd_Init(void);
void Lcd_GPIO_Init(void);


//绘画API
inline void lcd_clear(void);
inline void lcd_draw_point(unsigned int x, unsigned int y, unsigned int color);
inline unsigned int lcd_read_point(unsigned int x, unsigned int y);

#endif // !__BSP_LCD_H

