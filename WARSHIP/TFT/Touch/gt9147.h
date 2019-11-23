#pragma once
#include "sys.h"
#include "ctiic.h"

//电阻/电容屏芯片连接引脚	   
#define PEN  		PFin(10)  	//PF10 INT  --> GT_INT
#define DOUT 		PBin(2)   	//PB2  MISO 
#define TDIN 		PFout(9)  	//PF9  MOSI --> IIC_SDA
#define TCLK 		PBout(1)  	//PB1  SCLK --> IIC_SCL
#define GT_RST   	PFout(11)  	//PF11  CS  --> GT_RST

//I2C读写命令	
#define GT_CMD_WR 		0X28     	//写命令
#define GT_CMD_RD 		0X29		//读命令

//GT9147 部分寄存器定义 
#define GT_CTRL_REG 	0X8040   	//GT9147控制寄存器
#define GT_CFGS_REG 	0X8047   	//GT9147配置起始地址寄存器
#define GT_CHECK_REG 	0X80FF   	//GT9147校验和寄存器
#define GT_PID_REG 		0X8140   	//GT9147产品ID寄存器

#define GT_GSTID_REG 	0X814E   	//GT9147当前检测到的触摸情况
#define GT_TP1_REG 		0X8150  	//第一个触摸点数据地址
#define GT_TP2_REG 		0X8158		//第二个触摸点数据地址
#define GT_TP3_REG 		0X8160		//第三个触摸点数据地址
#define GT_TP4_REG 		0X8168		//第四个触摸点数据地址
#define GT_TP5_REG 		0X8170		//第五个触摸点数据地址 

typedef struct 
{
	u8 (*scan)(void);				//扫描触摸屏.0,屏幕扫描;1,物理坐标;
	u16 X[5]; 		//当前坐标
	u16 Y[5];		//电容屏有最多5组坐标X[0],Y[0]表示第一组坐标
								
	u8  sta;					//笔的状态 
								//b7:按下1/松开0; 
	                            //b6:0,没有按键按下;1,有按键按下. 
								//b5:保留
								//b4~b0:电容触摸屏按下的点数(0,表示未按下,1表示按下)
}_m_tp_dev;

u8 gt9147_init(void);
u8 GT9147_Send_Cfg(u8 mode);

void GT9147_Read_REG(u16 REG_addr, u8 *buff, u8 len);
u8 GT9147_Writ_REG(u16 REG_addr, u8 *buff, u8 len);
u8 GT9147_Scan(void);
