#ifndef __IMX6ULL_UART_H
#define __IMX6ULL_UART_H

//头文件包含


/*
 *  寄存器定义
 */
typedef volatile unsigned int regdef;
typedef struct {
    regdef URXD;
    unsigned char RESERVED_0[60];
    regdef UTXD;
    unsigned char RESERVED_1[60];
    regdef UCR1;
    regdef UCR2;
    regdef UCR3;
    regdef UCR4;
    regdef UFCR;
    regdef USR1;
    regdef USR2;
    regdef UESC;
    regdef UTIM;
    regdef UBIR;
    regdef UBMR;
    regdef UBRC;
    regdef ONEMS;
    regdef UTS;
    regdef UMCR;
} UART_Self_Type;

#define UART1_BASE_SELF                               (0x2020000u)
#define UART1_SELF                                    ((UART_Self_Type *)UART1_BASE_SELF)

#define UART2_BASE_SELF                               (0x21E8000u)
#define UART2_SELF                                    ((UART_Self_Type *)UART2_BASE_SELF)

#define UART3_BASE_SELF                               (0x21EC000u)
#define UART3_SELF                                    ((UART_Self_Type *)UART3_BASE_SELF)

#define UART4_BASE_SELF                               (0x21F0000u)
#define UART4_SELF                                    ((UART_Self_Type *)UART4_BASE_SELF)

#define UART5_BASE_SELF                               (0x21F4000u)
#define UART5_SELF                                    ((UART_Self_Type *)UART5_BASE_SELF)

#define UART6_BASE_SELF                               (0x21FC000u)
#define UART6_SELF                                    ((UART_Self_Type *)UART6_BASE_SELF)

#define UART7_BASE_SELF                               (0x2018000u)
#define UART7_SELF                                    ((UART_Self_Type *)UART7_BASE_SELF)

#define UART8_BASE_SELF                               (0x2288000u)
#define UART8_SELF                                    ((UART_Self_Type *)UART8_BASE_SELF)



//function declaration
void Uart1_Init(void);
void putc_self(unsigned char c);
void puts_self(char *str);
void print_reg(volatile unsigned int reg);

#endif

