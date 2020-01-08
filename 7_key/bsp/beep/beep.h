#ifndef __BEEP_H
#define __BEEP_H

/*寄存器定义*/
#define CCGR1 *((volatile unsigned int *)0x020C406C)
#define BEEP_MUX IOMUXC_SW_MUX_CTL_PAD_SNVS_TAMPER1
#define IOMUXC_SW_MUX_CTL_PAD_SNVS_TAMPER1 *((volatile unsigned int *)0x020E0020)
#define BEEP_PAD IOMUXC_SW_PAD_CTL_PAD_SNVS_TAMPER1
#define IOMUXC_SW_PAD_CTL_PAD_SNVS_TAMPER1 *((volatile unsigned int *)0x020E02AC)
#define GPIO5_DR   *((volatile unsigned int *)0x020AC000)
#define GPIO5_GDIR *((volatile unsigned int *)0x020AC004)

/*参数宏定义*/
#define BEEP_ON  1
#define BEEP_OFF 0

//宏定义型函数
#define Beep_On()  (GPIO5_DR &= ~(1<<1))
#define Beep_Off() (GPIO5_DR |=  (1<<1))

//function declaration
void Beep_Init(void);
void Beep_set_status(char status);


#endif // !__BEEP_H

