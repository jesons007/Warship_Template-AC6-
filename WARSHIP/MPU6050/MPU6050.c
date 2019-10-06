/*----MPU6050库使用说明------------------*/
/*
**移植自正点原子MPU6050实验代码,使用自己写的F_IIC驱动,经测试速度优于正点原子的代码
**使用官方提供的DMP库解算欧拉角
MPU6050输出数据包括：
**欧拉角均以初始化复位时的位置为0°
//航向角（yaw）  : -180.0°<---> +180.0°
//横滚角（roll） : -180.0°<---> +180.0°
//俯仰角（pitch）: -90.0° <---> +90.0°
//...
//
//
直接给出示例demo:
	MPU_Init();									//初始化MPU6050引脚接口、IIC、DMP库等操作，此函数会执行较长时间，需在程序中做判断等待（初始化成功返回0，错误返回其它数）
	float pitch,roll,yaw; 						//定义欧拉角参数  航向角（yaw）、横滚角（roll）和俯仰角（pitch）
	mpu_dmp_get_data(&pitch,&roll,&yaw);		//得到欧拉角,精度为1位小数(成功返回0，错误返回其它数)
	//以上三步即可得到欧拉角


MPU6050可以输出三个轴向的加速度以及三个轴向的角速度:
	//次数据为寄存器原始数据，无法直接使用，不过这些数据同样能够在程序里处理后得到欧拉角
	short aacx,aacy,aacz;		//加速度传感器原始数据
	short gyrox,gyroy,gyroz;	//陀螺仪原始数据	
	MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据(成功返回0，错误返回其它数)
	MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据(成功返回0，错误返回其它数)

MPU6050还可以得到温度值:
	short temp=MPU_Get_Temperature();		//MPU_Get_Temperature()函数返回温度值(扩大了100倍)
*/

#include "MPU6050.h"
#include "F_IIC.h"
#include "GPIO.h"
#include "delay.h"
#include "LCD.h"

F_IIC_TypeDef MPU6050_IIC_User = 
{
	.IIC_SCL = PB(10),           //IIC接口引脚
	.IIC_SDA = PB(11),
};

//初始化MPU6050
//返回值:0,成功
//    其他,错误代码
u8 MPU_Init()
{
	u8 res;
    GPIO_Init(GPIOA,GPIO_PIN_15,OUTPUT_PP);
    GPIO_Rset(GPIOA,GPIO_PIN_15);         //控制MPU6050的AD0脚为低电平,从机地址为:0X68

    F_IIC_init(&MPU6050_IIC_User);
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X80);	//复位MPU6050
    delay_ms(100);
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X00);	//唤醒MPU6050
	MPU_Set_Gyro_Fsr(3);					//陀螺仪传感器,±2000dps
	MPU_Set_Accel_Fsr(0);					//加速度传感器,±2g
	MPU_Set_Rate(50);						//设置采样率50Hz
	MPU_Write_Byte(MPU_INT_EN_REG,0X00);	//关闭所有中断
	MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	//I2C主模式关闭
	MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);	//关闭FIFO
	MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT引脚低电平有效
	res=MPU_Read_Byte(MPU_DEVICE_ID_REG);
	if(res==MPU_ADDR)//器件ID正确
	{
		MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X01);	//设置CLKSEL,PLL X轴为参考
		MPU_Write_Byte(MPU_PWR_MGMT2_REG,0X00);	//加速度与陀螺仪都工作
		MPU_Set_Rate(50);						//设置采样率为50Hz

		res = mpu_dmp_init();
		if(res==0)
		{
			//初始化成功
		}else return 1;
 	}else return 1;
	return 0;
}


//IIC写一个字节 
//reg:寄存器地址
//data:数据
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Byte(u8 reg,u8 data) 				 
{ 
    F_IIC_start(&MPU6050_IIC_User);
	F_IIC_write(&MPU6050_IIC_User, (MPU_ADDR<<1)|0);//发送器件地址+写命令
	if(!F_IIC_Wait_ACK(&MPU6050_IIC_User))	//等待应答
	{
		F_IIC_stop(&MPU6050_IIC_User);		 
		return 1;		
	}
    F_IIC_write(&MPU6050_IIC_User, reg);//写寄存器地址
    F_IIC_Wait_ACK(&MPU6050_IIC_User); //等待应答
	F_IIC_write(&MPU6050_IIC_User, data);//发送数据
	if(!F_IIC_Wait_ACK(&MPU6050_IIC_User))	//等待ACK
	{
		F_IIC_stop(&MPU6050_IIC_User); 
		return 1;		 
	}		 
    F_IIC_stop(&MPU6050_IIC_User);
	return 0;
}

//IIC读一个字节 
//reg:寄存器地址 
//返回值:读到的数据
u8 MPU_Read_Byte(u8 reg)
{
	u8 res;
    F_IIC_start(&MPU6050_IIC_User); 
	F_IIC_write(&MPU6050_IIC_User, (MPU_ADDR<<1)|0);//发送器件地址+写命令	
	F_IIC_Wait_ACK(&MPU6050_IIC_User);		//等待应答 
    F_IIC_write(&MPU6050_IIC_User,reg);	//写寄存器地址
    F_IIC_Wait_ACK(&MPU6050_IIC_User);		//等待应答
    F_IIC_start(&MPU6050_IIC_User);
	F_IIC_write(&MPU6050_IIC_User,(MPU_ADDR<<1)|1);//发送器件地址+读命令	
    F_IIC_Wait_ACK(&MPU6050_IIC_User);		//等待应答 
	res=F_IIC_read(&MPU6050_IIC_User, 0);   //读取数据,发送nACK 
    F_IIC_stop(&MPU6050_IIC_User);		//产生一个停止条件 
	return res;		
}


//IIC连续写
//addr:器件地址 
//reg:寄存器地址
//len:写入长度
//buf:数据区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i; 
    F_IIC_start(&MPU6050_IIC_User);
	F_IIC_write(&MPU6050_IIC_User,(addr<<1)|0);//发送器件地址+写命令	
	if(!F_IIC_Wait_ACK(&MPU6050_IIC_User))	//等待应答
	{
		F_IIC_stop(&MPU6050_IIC_User);	 
		return 1;		
	}
    F_IIC_write(&MPU6050_IIC_User,reg);	//写寄存器地址
    F_IIC_Wait_ACK(&MPU6050_IIC_User);		//等待应答
	for(i=0;i<len;i++)
	{
		F_IIC_write(&MPU6050_IIC_User,buf[i]);	//发送数据
		if(!F_IIC_Wait_ACK(&MPU6050_IIC_User))		//等待ACK
		{
			F_IIC_stop(&MPU6050_IIC_User);	 
			return 1;		 
		}		
	}    
    F_IIC_stop(&MPU6050_IIC_User); 
	return 0;	
}


//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
 	F_IIC_start(&MPU6050_IIC_User); 
	F_IIC_write(&MPU6050_IIC_User, (addr<<1)|0);//发送器件地址+写命令	
	if(!F_IIC_Wait_ACK(&MPU6050_IIC_User))	//等待应答
	{
		F_IIC_stop(&MPU6050_IIC_User);	 
		return 1;		
	}
    F_IIC_write(&MPU6050_IIC_User,reg);	//写寄存器地址
    F_IIC_Wait_ACK(&MPU6050_IIC_User);		//等待应答
    F_IIC_start(&MPU6050_IIC_User);
	F_IIC_write(&MPU6050_IIC_User, (addr<<1)|1);//发送器件地址+读命令	
    F_IIC_Wait_ACK(&MPU6050_IIC_User);		//等待应答 
	while(len)
	{
		if(len==1)*buf=F_IIC_read(&MPU6050_IIC_User,0);//读数据,发送nACK 
		else *buf=F_IIC_read(&MPU6050_IIC_User,1);		//读数据,发送ACK  
		len--;
		buf++; 
	}    
    F_IIC_stop(&MPU6050_IIC_User);	//产生一个停止条件 
	return 0;	
}


//设置MPU6050陀螺仪传感器满量程范围
//fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);//设置陀螺仪满量程范围  
}

//设置MPU6050加速度传感器满量程范围
//fsr:0,±2g;1,±4g;2,±8g;3,±16g
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_Accel_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);//设置加速度传感器满量程范围  
}

//设置MPU6050的数字低通滤波器
//lpf:数字低通滤波频率(Hz)
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_LPF(u16 lpf)
{
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU_CFG_REG,data);//设置数字低通滤波器  
}

//设置MPU6050的采样率(假定Fs=1KHz)
//rate:4~1000(Hz)
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_Rate(u16 rate)
{
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);	//设置数字低通滤波器
 	return MPU_Set_LPF(rate/2);					//自动设置LPF为采样率的一半
}

//得到温度值
//返回值:温度值(扩大了100倍)
short MPU_Get_Temperature()
{
    u8 buf[2]; 
    short raw;
	float temp;
	MPU_Read_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=36.53+((double)raw)/340;  
    return temp*100;
}

//得到陀螺仪值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((u16)buf[0]<<8)|buf[1];  
		*gy=((u16)buf[2]<<8)|buf[3];  
		*gz=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}

//得到加速度值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}

void MPU_6050_LcdShow(u16 x,u16 y,float data)      //在(x,y)处显示欧拉角数据,仅支持显示正负三位整数及一位小数
{
	short temp;
	u16 tenp;
	temp = data*10;
	LCD_show_str(x+48,y,$STR".",BLACK,BKOR);
	
	if(temp<0)
	{
		temp = -temp;
		LCD_show_str(x,y,$STR"-",BLACK,BKOR);
	}
	else LCD_show_str(x,y,$STR" ",BLACK,BKOR);
	tenp = temp/10;
	if(tenp<10) 
	{
		LCD_show_str(x+12,y,$STR"  ",BLACK,BKOR);
		LCD_show_number(x+36,y,tenp,BLACK,BKOR,1);
	}
	else if(tenp<100)
	{
		LCD_show_str(x+12,y,$STR" ",BLACK,BKOR);
		LCD_show_number(x+24,y,tenp,BLACK,BKOR,2);
	}
	else LCD_show_number(x+12,y,tenp,BLACK,BKOR,3);
	
	
	LCD_show_number(x+60,y,temp%10,BLACK,BKOR,1);
}

//速度测试
	//TimeKeeper_ON();	
	// while(MPU_Init())//1722.3ms
	// {
	// 	LCD_show_str(0,0,$STR"MPU6050 error!",BLACK,BKOR);
	// 	delay_ms(200);
	// 	LCD_show_str(0,0,$STR"              ",BLACK,BKOR);
	// 	delay_ms(200);
	// }
	// TimeKeeper_OFF();
	// LCD_show_number(0,200,Get_TimeKeeper_Count(),BLACK,BKOR,10);

	// TimeKeeper_ON();
	// MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据281us
	// TimeKeeper_OFF();
	// LCD_show_number(0,400,Get_TimeKeeper_Count(),BLACK,BKOR,10);
	
	// TimeKeeper_ON();
	// MPU_Write_Byte(MPU_GYRO_CFG_REG,3);//设置陀螺仪满量程范围100us
	// TimeKeeper_OFF();
	// LCD_show_number(0,424,Get_TimeKeeper_Count(),BLACK,BKOR,10);
	
	// TimeKeeper_ON();
	// mpu_dmp_get_data(&pitch,&roll,&yaw);		//得到欧拉角165us
	// TimeKeeper_OFF();
	// LCD_show_number(0,448,Get_TimeKeeper_Count(),BLACK,BKOR,10);

/*
float pitch,roll,yaw; 		//欧拉角  航向角（yaw）、横滚角（roll）和俯仰角（pitch）
void setup()
{
	JTAG_Set(SWD_ENABLE);   //关闭JTAG,只用SWD
	delay_init(72);
	led_init();
	LCD_init(BKOR);
	myuart_init(USART1,115200,PA(10),PA(9));
	
	H_IIC_init(PG(13),PC(0));   //别忘了修改H_IIC.c里面的引脚配置
	oled_init();
	oled_show_str(0,0,(u8*)"jesons007 ok!", $1608);
	oled_show_img((u8*)img1);
	OLED_REFRESH_FULL;
	
	key_init(); //TIM6
	TimeKeeper_Init(TimeKeeper_1us_Count); //TIM7;
	//myuart_init(USART3,115200,PB(11),PB(10));
}


int main(void)
{			
	
	short aacx,aacy,aacz;		//加速度传感器原始数据
	short gyrox,gyroy,gyroz;	//陀螺仪原始数据
	short temp;
	u8 *buff[10];
	u8 i=0,j=1;
	setup();
	uart_send_str(USART1,$STR"SYS OK!\r\n");
	
	printf("111%d\r\n",i);
	LED0 = 0;
	
	TimeKeeper_ON();	
	while(MPU_Init())//1722.3ms
	{
		LCD_show_str(0,0,$STR"MPU6050 error!",BLACK,BKOR);
		delay_ms(200);
		LCD_show_str(0,0,$STR"              ",BLACK,BKOR);
		delay_ms(200);
	}
	
	
	TimeKeeper_OFF();
	LCD_show_number(0,200,Get_TimeKeeper_Count(),BLACK,BKOR,10);
	
	LED0 = 1;
	
	LCD_show_str(0,0, $STR"yaw:   ",BLACK,BKOR);
	LCD_show_str(0,24,$STR"roll:  ",BLACK,BKOR);
	LCD_show_str(0,48,$STR"pitch: ",BLACK,BKOR);
	
	 TimeKeeper_ON();
	 mpu_dmp_get_data(&pitch,&roll,&yaw);		//得到欧拉角165us
	 TimeKeeper_OFF();
     LCD_show_number(0,448,Get_TimeKeeper_Count(),BLACK,BKOR,10);
	
	while(1)
	{
		mpu_dmp_get_data(&pitch,&roll,&yaw);		//得到欧拉角
		// MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
		// MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
		MPU_6050_LcdShow(84,0,  yaw);
		MPU_6050_LcdShow(84,24, roll);
		MPU_6050_LcdShow(84,48, pitch);

		//  temp = aacy;
		// // if(temp<0)
		// // {
		// // 	temp = -temp;
		// // 	LCD_show_str(0,100,$STR"-",BLACK,BKOR);
		// // }
		// // else	LCD_show_str(0,100,$STR" ",BLACK,BKOR);
		// // LCD_show_number(12,100,temp,BLACK,BKOR,5);

		key_moniter();
		
		LED0 = !LED0;
	}
} 


*/

