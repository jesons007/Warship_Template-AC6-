#include "Include_config.h"

#include "sys.h"
#include "delay.h"	
#include "stdio.h"     //包含使用Printf

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
	float pitch,roll,yaw; 		//欧拉角  航向角（yaw）、横滚角（roll）和俯仰角（pitch）
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

		// key_moniter();
		
		//delay_ms(500);	
		//mpu_dmp_get_data(&pitch,&roll,&yaw);
		LED0 = !LED0;
	}
} 








