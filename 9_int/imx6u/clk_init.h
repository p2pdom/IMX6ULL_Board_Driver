/*
 *  imx6ull时钟初始化
 */
#ifndef __CLK_INIT_H
#define __CLK_INIT_H

//头文件包含

//必要变量定义


/*寄存器定义*/
typedef volatile unsigned int regdef;
typedef struct
{
    regdef CCR;
    regdef CCDR;
    regdef CSR;
    regdef CCSR;
    regdef CACRR;
    regdef CBCDR;
    regdef CBCMR;
    regdef CSCMR1;
    regdef CSCMR2;
    regdef CSCDR1;
    regdef CS1CDR;
    regdef CS2CDR;
    regdef CDCDR;
    regdef CHSCCDR;
    regdef CSCDR2;
    regdef CSCDR3;
    unsigned char RESERVED_0[8];
    regdef CDHIPR;
    unsigned char RESERVED_1[8];
    regdef CLPCR;
    regdef CISR;
    regdef CIMR;
    regdef CCOSR;
    regdef CGPR;
    regdef CCGR0;                            
    regdef CCGR1;                       
    regdef CCGR2;                      
    regdef CCGR3;         
    regdef CCGR4;                   
    regdef CCGR5;                       
    regdef CCGR6;
    unsigned char RESERVED_2[4];
    regdef CMEOR;
}CCM_Type_SELF;
#define CCM_BASE_ADDRESS  (0x20C4000u)
#define CCM_SELF          ((CCM_Type_SELF *)CCM_BASE_ADDRESS)

typedef struct
{
    regdef PLL_ARM;                         
    regdef PLL_ARM_SET;                     
    regdef PLL_ARM_CLR;               
    regdef PLL_ARM_TOG;                     
    regdef PLL_USB1;                         
    regdef PLL_USB1_SET;                    
    regdef PLL_USB1_CLR;                 
    regdef PLL_USB1_TOG;                   
    regdef PLL_USB2;                      
    regdef PLL_USB2_SET;                    
    regdef PLL_USB2_CLR;                    
    regdef PLL_USB2_TOG;                   
    regdef PLL_SYS;                        
    regdef PLL_SYS_SET;                     
    regdef PLL_SYS_CLR;                     
    regdef PLL_SYS_TOG;                     
    regdef PLL_SYS_SS;                        
    unsigned char RESERVED_0[12];
    regdef PLL_SYS_NUM;                      
    unsigned char RESERVED_1[12];
    regdef PLL_SYS_DENOM;                     
    unsigned char RESERVED_2[12];
    regdef PLL_AUDIO;                         
    regdef PLL_AUDIO_SET;                     
    regdef PLL_AUDIO_CLR;                     
    regdef PLL_AUDIO_TOG;                     
    regdef PLL_AUDIO_NUM;                     
    unsigned char RESERVED_3[12];
    regdef PLL_AUDIO_DENOM;                   
    unsigned char RESERVED_4[12];
    regdef PLL_VIDEO;                       
    regdef PLL_VIDEO_SET;                   
    regdef PLL_VIDEO_CLR;              
    regdef PLL_VIDEO_TOG;                    
    regdef PLL_VIDEO_NUM;                    
    unsigned char RESERVED_5[12];
    regdef PLL_VIDEO_DENOM;                 
    unsigned char RESERVED_6[28];
    regdef PLL_ENET;                          
    regdef PLL_ENET_SET;                   
    regdef PLL_ENET_CLR;                      
    regdef PLL_ENET_TOG;                      
    regdef PFD_480;                           
    regdef PFD_480_SET;                       
    regdef PFD_480_CLR;                     
    regdef PFD_480_TOG;                       
    regdef PFD_528;                         
    regdef PFD_528_SET;                      
    regdef PFD_528_CLR;                       
    regdef PFD_528_TOG;                    
    unsigned char RESERVED_7[64];
    regdef MISC0;                           
    regdef MISC0_SET;                      
    regdef MISC0_CLR;                      
    regdef MISC0_TOG;                       
    regdef MISC1;                         
    regdef MISC1_SET;                      
    regdef MISC1_CLR;                     
    regdef MISC1_TOG;                        
    regdef MISC2;                            
    regdef MISC2_SET;                     
    regdef MISC2_CLR;                
    regdef MISC2_TOG; 
}CCM_ANALOG_Type_SELF;
#define CCM_ANALOG_BASE_ADDRESS  (0x20C8000u)
#define CCM_ANALOG_SELF          ((CCM_ANALOG_Type_SELF *)CCM_ANALOG_BASE_ADDRESS)

//function declaration
void Imx6ull_Clk_Init(void);

void Clock_Tree_Init(void);

void ARM_CLK_ROOT_Init(void);
void MMDC_CLK_ROOT_Init(void);
void FABRIC_CLK_ROOT_Init(void);
void AXI_CLK_ROOT_Init(void);
void AHB_CLK_ROOT_Init(void);
void PERCLK_CLK_ROOT_Init(void);
void IPG_CLK_ROOT_Init(void);
void USDHC1_CLK_ROOT_Init(void);
void USDHC2_CLK_ROOT_Init(void);
void BCH_CLK_ROOT_Init(void);
void GPMI_CLK_ROOT_Init(void);
void ACLK_EIM_SLOW_CLK_ROOT_Init(void);
void SPDIF0_CLK_ROOT_Init(void);
void SAI1_CLK_ROOT_Init(void);
void SAI2_CLK_ROOT_Init(void);
void SAI3_CLK_ROOT_Init(void);
void ESAI_CLK_ROOT_Init(void);
void LCDIF1_CLK_ROOT_Init(void);
void EPDC_CLK_ROOT_Init(void);
void QSPI1_CLK_ROOT_Init(void);
void ENFC_CLK_ROOT_Init(void);
void CAN_CLK_ROOT_Init(void);
void ECSPI_CLK_ROOT_Init(void);
void UART_CLK_ROOT_Init(void);


void PLL_Init(void);
void PLL1_Init(void);
void PLL2_Init(void);
void PLL3_Init(void);

#endif // !__CLK_INIT_H

