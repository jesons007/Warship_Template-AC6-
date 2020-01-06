#ifndef __SYS_H
#define __SYS_H	  
#include <stm32f10x.h>  

//0,不支持OS
//1,支持OS
#define SYSTEM_SUPPORT_OS		0		//定义系统文件夹是否支持OS
																	    
#define PA(n)    (0X00+n)
#define PB(n)    (0X10+n)
#define PC(n)    (0X20+n)
#define PD(n)    (0X30+n)
#define PE(n)    (0X40+n)
#define PF(n)    (0X50+n)
#define PG(n)    (0X60+n) 

#define $STR (u8*)

//fix bug: 12.19 
//GPIO Fast Set/Reset:
#define PA0__Set_1 GPIOA->ODR |= 0x0001
#define PA1__Set_1 GPIOA->ODR |= 0x0002
#define PA2__Set_1 GPIOA->ODR |= 0x0004
#define PA3__Set_1 GPIOA->ODR |= 0x0008
#define PA4__Set_1 GPIOA->ODR |= 0x0010
#define PA5__Set_1 GPIOA->ODR |= 0x0020
#define PA6__Set_1 GPIOA->ODR |= 0x0040
#define PA7__Set_1 GPIOA->ODR |= 0x0080
#define PA8__Set_1 GPIOA->ODR |= 0x0100
#define PA9__Set_1 GPIOA->ODR |= 0x0200
#define PA10_Set_1 GPIOA->ODR |= 0x0400
#define PA11_Set_1 GPIOA->ODR |= 0x0800
#define PA12_Set_1 GPIOA->ODR |= 0x1000
#define PA13_Set_1 GPIOA->ODR |= 0x2000
#define PA14_Set_1 GPIOA->ODR |= 0x4000
#define PA15_Set_1 GPIOA->ODR |= 0x8000

#define PB0__Set_1 GPIOB->ODR |= 0x0001
#define PB1__Set_1 GPIOB->ODR |= 0x0002
#define PB2__Set_1 GPIOB->ODR |= 0x0004
#define PB3__Set_1 GPIOB->ODR |= 0x0008
#define PB4__Set_1 GPIOB->ODR |= 0x0010
#define PB5__Set_1 GPIOB->ODR |= 0x0020
#define PB6__Set_1 GPIOB->ODR |= 0x0040
#define PB7__Set_1 GPIOB->ODR |= 0x0080
#define PB8__Set_1 GPIOB->ODR |= 0x0100
#define PB9__Set_1 GPIOB->ODR |= 0x0200
#define PB10_Set_1 GPIOB->ODR |= 0x0400
#define PB11_Set_1 GPIOB->ODR |= 0x0800
#define PB12_Set_1 GPIOB->ODR |= 0x1000
#define PB13_Set_1 GPIOB->ODR |= 0x2000
#define PB14_Set_1 GPIOB->ODR |= 0x4000
#define PB15_Set_1 GPIOB->ODR |= 0x8000

#define PC0__Set_1 GPIOC->ODR |= 0x0001
#define PC1__Set_1 GPIOC->ODR |= 0x0002
#define PC2__Set_1 GPIOC->ODR |= 0x0004
#define PC3__Set_1 GPIOC->ODR |= 0x0008
#define PC4__Set_1 GPIOC->ODR |= 0x0010
#define PC5__Set_1 GPIOC->ODR |= 0x0020
#define PC6__Set_1 GPIOC->ODR |= 0x0040
#define PC7__Set_1 GPIOC->ODR |= 0x0080
#define PC8__Set_1 GPIOC->ODR |= 0x0100
#define PC9__Set_1 GPIOC->ODR |= 0x0200
#define PC10_Set_1 GPIOC->ODR |= 0x0400
#define PC11_Set_1 GPIOC->ODR |= 0x0800
#define PC12_Set_1 GPIOC->ODR |= 0x1000
#define PC13_Set_1 GPIOC->ODR |= 0x2000
#define PC14_Set_1 GPIOC->ODR |= 0x4000
#define PC15_Set_1 GPIOC->ODR |= 0x8000

#define PD0__Set_1 GPIOD->ODR |= 0x0001
#define PD1__Set_1 GPIOD->ODR |= 0x0002
#define PD2__Set_1 GPIOD->ODR |= 0x0004
#define PD3__Set_1 GPIOD->ODR |= 0x0008
#define PD4__Set_1 GPIOD->ODR |= 0x0010
#define PD5__Set_1 GPIOD->ODR |= 0x0020
#define PD6__Set_1 GPIOD->ODR |= 0x0040
#define PD7__Set_1 GPIOD->ODR |= 0x0080
#define PD8__Set_1 GPIOD->ODR |= 0x0100
#define PD9__Set_1 GPIOD->ODR |= 0x0200
#define PD10_Set_1 GPIOD->ODR |= 0x0400
#define PD11_Set_1 GPIOD->ODR |= 0x0800
#define PD12_Set_1 GPIOD->ODR |= 0x1000
#define PD13_Set_1 GPIOD->ODR |= 0x2000
#define PD14_Set_1 GPIOD->ODR |= 0x4000
#define PD15_Set_1 GPIOD->ODR |= 0x8000

#define PE0__Set_1 GPIOE->ODR |= 0x0001
#define PE1__Set_1 GPIOE->ODR |= 0x0002
#define PE2__Set_1 GPIOE->ODR |= 0x0004
#define PE3__Set_1 GPIOE->ODR |= 0x0008
#define PE4__Set_1 GPIOE->ODR |= 0x0010
#define PE5__Set_1 GPIOE->ODR |= 0x0020
#define PE6__Set_1 GPIOE->ODR |= 0x0040
#define PE7__Set_1 GPIOE->ODR |= 0x0080
#define PE8__Set_1 GPIOE->ODR |= 0x0100
#define PE9__Set_1 GPIOE->ODR |= 0x0200
#define PE10_Set_1 GPIOE->ODR |= 0x0400
#define PE11_Set_1 GPIOE->ODR |= 0x0800
#define PE12_Set_1 GPIOE->ODR |= 0x1000
#define PE13_Set_1 GPIOE->ODR |= 0x2000
#define PE14_Set_1 GPIOE->ODR |= 0x4000
#define PE15_Set_1 GPIOE->ODR |= 0x8000

#define PF0__Set_1 GPIOF->ODR |= 0x0001
#define PF1__Set_1 GPIOF->ODR |= 0x0002
#define PF2__Set_1 GPIOF->ODR |= 0x0004
#define PF3__Set_1 GPIOF->ODR |= 0x0008
#define PF4__Set_1 GPIOF->ODR |= 0x0010
#define PF5__Set_1 GPIOF->ODR |= 0x0020
#define PF6__Set_1 GPIOF->ODR |= 0x0040
#define PF7__Set_1 GPIOF->ODR |= 0x0080
#define PF8__Set_1 GPIOF->ODR |= 0x0100
#define PF9__Set_1 GPIOF->ODR |= 0x0200
#define PF10_Set_1 GPIOF->ODR |= 0x0400
#define PF11_Set_1 GPIOF->ODR |= 0x0800
#define PF12_Set_1 GPIOF->ODR |= 0x1000
#define PF13_Set_1 GPIOF->ODR |= 0x2000
#define PF14_Set_1 GPIOF->ODR |= 0x4000
#define PF15_Set_1 GPIOF->ODR |= 0x8000

#define PG0__Set_1 GPIOG->ODR |= 0x0001
#define PG1__Set_1 GPIOG->ODR |= 0x0002
#define PG2__Set_1 GPIOG->ODR |= 0x0004
#define PG3__Set_1 GPIOG->ODR |= 0x0008
#define PG4__Set_1 GPIOG->ODR |= 0x0010
#define PG5__Set_1 GPIOG->ODR |= 0x0020
#define PG6__Set_1 GPIOG->ODR |= 0x0040
#define PG7__Set_1 GPIOG->ODR |= 0x0080
#define PG8__Set_1 GPIOG->ODR |= 0x0100
#define PG9__Set_1 GPIOG->ODR |= 0x0200
#define PG10_Set_1 GPIOG->ODR |= 0x0400
#define PG11_Set_1 GPIOG->ODR |= 0x0800
#define PG12_Set_1 GPIOG->ODR |= 0x1000
#define PG13_Set_1 GPIOG->ODR |= 0x2000
#define PG14_Set_1 GPIOG->ODR |= 0x4000
#define PG15_Set_1 GPIOG->ODR |= 0x8000

#define PA0__Set_0 GPIOA->ODR &= 0xFFFE
#define PA1__Set_0 GPIOA->ODR &= 0xFFFD
#define PA2__Set_0 GPIOA->ODR &= 0xFFFB
#define PA3__Set_0 GPIOA->ODR &= 0xFFF7
#define PA4__Set_0 GPIOA->ODR &= 0xFFEF
#define PA5__Set_0 GPIOA->ODR &= 0xFFDF
#define PA6__Set_0 GPIOA->ODR &= 0xFFBF
#define PA7__Set_0 GPIOA->ODR &= 0xFF7F
#define PA8__Set_0 GPIOA->ODR &= 0xFEFF
#define PA9__Set_0 GPIOA->ODR &= 0xFDFF
#define PA10_Set_0 GPIOA->ODR &= 0xFBFF
#define PA11_Set_0 GPIOA->ODR &= 0xF7FF
#define PA12_Set_0 GPIOA->ODR &= 0xEFFF
#define PA13_Set_0 GPIOA->ODR &= 0xDFFF
#define PA14_Set_0 GPIOA->ODR &= 0xBFFF
#define PA15_Set_0 GPIOA->ODR &= 0x7FFF

#define PB0__Set_0 GPIOB->ODR &= 0xFFFE
#define PB1__Set_0 GPIOB->ODR &= 0xFFFD
#define PB2__Set_0 GPIOB->ODR &= 0xFFFB
#define PB3__Set_0 GPIOB->ODR &= 0xFFF7
#define PB4__Set_0 GPIOB->ODR &= 0xFFEF
#define PB5__Set_0 GPIOB->ODR &= 0xFFDF
#define PB6__Set_0 GPIOB->ODR &= 0xFFBF
#define PB7__Set_0 GPIOB->ODR &= 0xFF7F
#define PB8__Set_0 GPIOB->ODR &= 0xFEFF
#define PB9__Set_0 GPIOB->ODR &= 0xFDFF
#define PB10_Set_0 GPIOB->ODR &= 0xFBFF
#define PB11_Set_0 GPIOB->ODR &= 0xF7FF
#define PB12_Set_0 GPIOB->ODR &= 0xEFFF
#define PB13_Set_0 GPIOB->ODR &= 0xDFFF
#define PB14_Set_0 GPIOB->ODR &= 0xBFFF
#define PB15_Set_0 GPIOB->ODR &= 0x7FFF

#define PC0__Set_0 GPIOC->ODR &= 0xFFFE
#define PC1__Set_0 GPIOC->ODR &= 0xFFFD
#define PC2__Set_0 GPIOC->ODR &= 0xFFFB
#define PC3__Set_0 GPIOC->ODR &= 0xFFF7
#define PC4__Set_0 GPIOC->ODR &= 0xFFEF
#define PC5__Set_0 GPIOC->ODR &= 0xFFDF
#define PC6__Set_0 GPIOC->ODR &= 0xFFBF
#define PC7__Set_0 GPIOC->ODR &= 0xFF7F
#define PC8__Set_0 GPIOC->ODR &= 0xFEFF
#define PC9__Set_0 GPIOC->ODR &= 0xFDFF
#define PC10_Set_0 GPIOC->ODR &= 0xFBFF
#define PC11_Set_0 GPIOC->ODR &= 0xF7FF
#define PC12_Set_0 GPIOC->ODR &= 0xEFFF
#define PC13_Set_0 GPIOC->ODR &= 0xDFFF
#define PC14_Set_0 GPIOC->ODR &= 0xBFFF
#define PC15_Set_0 GPIOC->ODR &= 0x7FFF

#define PD0__Set_0 GPIOD->ODR &= 0xFFFE
#define PD1__Set_0 GPIOD->ODR &= 0xFFFD
#define PD2__Set_0 GPIOD->ODR &= 0xFFFB
#define PD3__Set_0 GPIOD->ODR &= 0xFFF7
#define PD4__Set_0 GPIOD->ODR &= 0xFFEF
#define PD5__Set_0 GPIOD->ODR &= 0xFFDF
#define PD6__Set_0 GPIOD->ODR &= 0xFFBF
#define PD7__Set_0 GPIOD->ODR &= 0xFF7F
#define PD8__Set_0 GPIOD->ODR &= 0xFEFF
#define PD9__Set_0 GPIOD->ODR &= 0xFDFF
#define PD10_Set_0 GPIOD->ODR &= 0xFBFF
#define PD11_Set_0 GPIOD->ODR &= 0xF7FF
#define PD12_Set_0 GPIOD->ODR &= 0xEFFF
#define PD13_Set_0 GPIOD->ODR &= 0xDFFF
#define PD14_Set_0 GPIOD->ODR &= 0xBFFF
#define PD15_Set_0 GPIOD->ODR &= 0x7FFF

#define PE0__Set_0 GPIOE->ODR &= 0xFFFE
#define PE1__Set_0 GPIOE->ODR &= 0xFFFD
#define PE2__Set_0 GPIOE->ODR &= 0xFFFB
#define PE3__Set_0 GPIOE->ODR &= 0xFFF7
#define PE4__Set_0 GPIOE->ODR &= 0xFFEF
#define PE5__Set_0 GPIOE->ODR &= 0xFFDF
#define PE6__Set_0 GPIOE->ODR &= 0xFFBF
#define PE7__Set_0 GPIOE->ODR &= 0xFF7F
#define PE8__Set_0 GPIOE->ODR &= 0xFEFF
#define PE9__Set_0 GPIOE->ODR &= 0xFDFF
#define PE10_Set_0 GPIOE->ODR &= 0xFBFF
#define PE11_Set_0 GPIOE->ODR &= 0xF7FF
#define PE12_Set_0 GPIOE->ODR &= 0xEFFF
#define PE13_Set_0 GPIOE->ODR &= 0xDFFF
#define PE14_Set_0 GPIOE->ODR &= 0xBFFF
#define PE15_Set_0 GPIOE->ODR &= 0x7FFF

#define PF0__Set_0 GPIOF->ODR &= 0xFFFE
#define PF1__Set_0 GPIOF->ODR &= 0xFFFD
#define PF2__Set_0 GPIOF->ODR &= 0xFFFB
#define PF3__Set_0 GPIOF->ODR &= 0xFFF7
#define PF4__Set_0 GPIOF->ODR &= 0xFFEF
#define PF5__Set_0 GPIOF->ODR &= 0xFFDF
#define PF6__Set_0 GPIOF->ODR &= 0xFFBF
#define PF7__Set_0 GPIOF->ODR &= 0xFF7F
#define PF8__Set_0 GPIOF->ODR &= 0xFEFF
#define PF9__Set_0 GPIOF->ODR &= 0xFDFF
#define PF10_Set_0 GPIOF->ODR &= 0xFBFF
#define PF11_Set_0 GPIOF->ODR &= 0xF7FF
#define PF12_Set_0 GPIOF->ODR &= 0xEFFF
#define PF13_Set_0 GPIOF->ODR &= 0xDFFF
#define PF14_Set_0 GPIOF->ODR &= 0xBFFF
#define PF15_Set_0 GPIOF->ODR &= 0x7FFF

#define PG0__Set_0 GPIOG->ODR &= 0xFFFE
#define PG1__Set_0 GPIOG->ODR &= 0xFFFD
#define PG2__Set_0 GPIOG->ODR &= 0xFFFB
#define PG3__Set_0 GPIOG->ODR &= 0xFFF7
#define PG4__Set_0 GPIOG->ODR &= 0xFFEF
#define PG5__Set_0 GPIOG->ODR &= 0xFFDF
#define PG6__Set_0 GPIOG->ODR &= 0xFFBF
#define PG7__Set_0 GPIOG->ODR &= 0xFF7F
#define PG8__Set_0 GPIOG->ODR &= 0xFEFF
#define PG9__Set_0 GPIOG->ODR &= 0xFDFF
#define PG10_Set_0 GPIOG->ODR &= 0xFBFF
#define PG11_Set_0 GPIOG->ODR &= 0xF7FF
#define PG12_Set_0 GPIOG->ODR &= 0xEFFF
#define PG13_Set_0 GPIOG->ODR &= 0xDFFF
#define PG14_Set_0 GPIOG->ODR &= 0xBFFF
#define PG15_Set_0 GPIOG->ODR &= 0x7FFF

//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入
/////////////////////////////////////////////////////////////////
//Ex_NVIC_Config专用定义
#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3
#define GPIO_E 4
#define GPIO_F 5
#define GPIO_G 6 
#define FTIR   1  //下降沿触发
#define RTIR   2  //上升沿触发
								   

//JTAG模式设置定义
#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
#define JTAG_SWD_ENABLE    0X00	

/////////////////////////////////////////////////////////////////  
void Stm32_Clock_Init(void);  //时钟初始化  
void Sys_Soft_Reset(void);      //系统软复位
void Sys_Standby(void);         //待机模式 	
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);//设置偏移地址
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);//设置NVIC分组
//void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group);//设置中断
void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM);//外部中断配置函数(只对GPIOA~G)
void JTAG_Set(u8 mode);
//////////////////////////////////////////////////////////////////////////////
//以下为汇编函数
void WFI_SET(void);		//执行WFI指令
void INTX_DISABLE(void);//关闭所有中断
void INTX_ENABLE(void);	//开启所有中断
void MSR_MSP(u32 addr);	//设置堆栈地址
///////////////////////////////////////////////////////////////////////////////////////////////////////
//   NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
//   MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
//   BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
//   UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
//   SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
//   DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
//   PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
//   SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */
//   WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                            */
//   PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt            */
//   TAMPER_IRQn                 = 2,      /*!< Tamper Interrupt                                     */
//   RTC_IRQn                    = 3,      /*!< RTC global Interrupt                                 */
//   FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                               */
//   RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                 */
//   EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                 */
//   EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                 */
//   EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                 */
//   EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                 */
//   EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                 */
//   DMA1_Channel1_IRQn          = 11,     /*!< DMA1 Channel 1 global Interrupt                      */
//   DMA1_Channel2_IRQn          = 12,     /*!< DMA1 Channel 2 global Interrupt                      */
//   DMA1_Channel3_IRQn          = 13,     /*!< DMA1 Channel 3 global Interrupt                      */
//   DMA1_Channel4_IRQn          = 14,     /*!< DMA1 Channel 4 global Interrupt                      */
//   DMA1_Channel5_IRQn          = 15,     /*!< DMA1 Channel 5 global Interrupt                      */
//   DMA1_Channel6_IRQn          = 16,     /*!< DMA1 Channel 6 global Interrupt                      */
//   DMA1_Channel7_IRQn          = 17,     /*!< DMA1 Channel 7 global Interrupt                      */
//   ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
//   USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
//   USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
//   CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
//   CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
//   EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
//   TIM1_BRK_IRQn               = 24,     /*!< TIM1 Break Interrupt                                 */
//   TIM1_UP_IRQn                = 25,     /*!< TIM1 Update Interrupt                                */
//   TIM1_TRG_COM_IRQn           = 26,     /*!< TIM1 Trigger and Commutation Interrupt               */
//   TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
//   TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                */
//   TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                */
//   TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                */
//   I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
//   I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
//   I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
//   I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
//   SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
//   SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
//   USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
//   USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
//   USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
//   EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
//   RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
//   USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
//   TIM8_BRK_IRQn               = 43,     /*!< TIM8 Break Interrupt                                 */
//   TIM8_UP_IRQn                = 44,     /*!< TIM8 Update Interrupt                                */
//   TIM8_TRG_COM_IRQn           = 45,     /*!< TIM8 Trigger and Commutation Interrupt               */
//   TIM8_CC_IRQn                = 46,     /*!< TIM8 Capture Compare Interrupt                       */
//   ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                */
//   FSMC_IRQn                   = 48,     /*!< FSMC global Interrupt                                */
//   SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                */
//   TIM5_IRQn                   = 50,     /*!< TIM5 global Interrupt                                */
//   SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                */
//   UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
//   UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
//   TIM6_IRQn                   = 54,     /*!< TIM6 global Interrupt                                */
//   TIM7_IRQn                   = 55,     /*!< TIM7 global Interrupt                                */
//   DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
//   DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
//   DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
//   DMA2_Channel4_5_IRQn        = 59      /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
//默认中断分组：组4:4位抢占优先级,0位响应优先级     
//NVIC_Channel:             中断编号
//NVIC_PreemptionPriority:  优先级 0~15
void MY_NVIC_Init(u8 NVIC_Channel, u8 NVIC_PreemptionPriority);

#endif











