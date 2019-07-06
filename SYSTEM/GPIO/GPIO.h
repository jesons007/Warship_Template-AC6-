#ifndef _GPIO_H_
#define _GPIO_H_
#include "stm32f10x.h"

/*GPIO常用的5种模式*/
#define OUTPUT_PP 		0X3     //推挽输出
#define OUTPUT_FF 		0XB     //复用推挽
#define INPUT_UP  		0X9     //上拉输入
#define INPUT_DOWN		0X8     //下拉输入
#define INPUT_ANALOG    0X0	    //模拟输入

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

//GPIO引脚编号定义
#define GPIO_PIN_0				1<<0
#define GPIO_PIN_1				1<<1
#define GPIO_PIN_2				1<<2
#define GPIO_PIN_3				1<<3
#define GPIO_PIN_4				1<<4
#define GPIO_PIN_5				1<<5
#define GPIO_PIN_6				1<<6
#define GPIO_PIN_7				1<<7
#define GPIO_PIN_8				1<<8
#define GPIO_PIN_9				1<<9
#define GPIO_PIN_10				1<<10
#define GPIO_PIN_11				1<<11
#define GPIO_PIN_12				1<<12
#define GPIO_PIN_13				1<<13
#define GPIO_PIN_14				1<<14
#define GPIO_PIN_15				1<<15 
#define GPIO_PIN_ALL            (0XFFFF)
#define GPIO_PIN_LSB            (0X00FF)
#define GPIO_PIN_MSB            (0XFF00)

void GPIO_Init(GPIO_TypeDef *GPIOx, u16 GPIO_PIN, u8 GPIO_MODE);
void GPIO_Set(GPIO_TypeDef *GPIOx, u16 GPIO_PIN);
void GPIO_Rset(GPIO_TypeDef *GPIOx, u16 GPIO_PIN);

void GPIO_WRITE(GPIO_TypeDef *GPIOx,u16 data);//一次设置16个io口的输出
u16 GPIO_READ(GPIO_TypeDef *GPIOx);          //一次读出16个io口的输入

void GPIO_PIN_Init(u8 PIN, u8 Mode);

#endif


