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

	GPIO_PIN_Init(PA(0),INPUT_DOWN);
	GPIO_PIN_Init(PA(1),INPUT_DOWN);
	Orth_Encoder_Init(TIM5);

}

int Encoder_position;
int main(void)
{			
	setup();
	LCD_Show_OneChar(300,700,'-',BLACK,BKOR);
	
	
	printf("set up ok!\r\n");
	while(1)
	{
		LCD_show_str(0,0,$STR"Encount:  ",BLACK,BKOR);
		Encoder_position = Orth_Get_EnCount(TIM5);
		if(Encoder_position<0)
		{
			Encoder_position = -Encoder_position;
			LCD_show_str(108,0,$STR"-",BLACK,BKOR);
		}
		else
		{
			LCD_show_str(108,0,$STR" ",BLACK,BKOR);
		}
		LCD_show_number(120,0,Encoder_position,BLACK,BKOR,10);

		key_moniter();
		LED0 = !LED0;
	}
} 








