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
	oled_show_str(0,0,(u8*)"oled ok!", $1608);
	//oled_show_img((u8*)img1);
	OLED_REFRESH_FULL;
	
	key_init(); //TIM6
	TimeKeeper_Init(TimeKeeper_1us_Count); //TIM7;
	//myuart_init(USART3,115200,PB(11),PB(10));

	GPIO_PIN_Init(PA(0),INPUT_DOWN);
	GPIO_PIN_Init(PA(1),INPUT_DOWN);
	Orth_Encoder_Init(TIM5);
	//gt9147_init();
	//Tp_NumPad_Init(1);
	//Nano_TFT_Init();//SPI2
	//Mini_TFT_Init();//8080
	W25Q128_Init();
}

void show_sdcard_info(void)
{
	switch(SDCardInfo.CardType)
	{
		case SDIO_STD_CAPACITY_SD_CARD_V1_1:printf("Card Type:SDSC V1.1\r\n");break;
		case SDIO_STD_CAPACITY_SD_CARD_V2_0:printf("Card Type:SDSC V2.0\r\n");break;
		case SDIO_HIGH_CAPACITY_SD_CARD:printf("Card Type:SDHC V2.0\r\n");break;
		case SDIO_MULTIMEDIA_CARD:printf("Card Type:MMC Card\r\n");break;
	}	
  	printf("Card ManufacturerID:%d\r\n",SDCardInfo.SD_cid.ManufacturerID);	//制造商ID
 	printf("Card RCA:%d\r\n",SDCardInfo.RCA);								//卡相对地址
	printf("Card Capacity:%d MB\r\n",(u32)(SDCardInfo.CardCapacity>>20));	//显示容量
 	printf("Card BlockSize:%d\r\n\r\n",SDCardInfo.CardBlockSize);			//显示块大小
}  
int main(void)
{			
	u16 i=0;
	setup();
	printf("set up ok!\r\n");
	LCD_show_str(0,0,$STR"set up ok!",BLACK,BKOR);
	//uart_send_str(USART1,$STR"set up ok\r\n");
		
	// TimeKeeper_ON();
	// LCD_Draw_Img(0,300,320,480,(u8 *)0x08003c9e);
	// TimeKeeper_OFF();
	// LCD_show_number(0,400,(u32)gImage_1,BLACK,WHITE,10);
	
	while(!W25Q128_Check())
	{
		LCD_show_str(0,24,$STR"W25Q128 Error!",RED,BKOR);
		delay_ms(100);
		LCD_show_str(0,24,$STR"              ",RED,BKOR);
		delay_ms(100);
	}LCD_show_str(0,24,$STR"W25Q128 OK!",RED,BKOR);
	
	while(SD_Init())//检测不到SD卡
	{
		LCD_show_str(0,48,$STR"SD Card Error!",RED,BKOR);
		delay_ms(500);					
		LCD_show_str(0,48,$STR"Please Check! ",RED,BKOR);
		delay_ms(500);
		LED0=!LED0;//DS0闪烁
	}
	show_sdcard_info();
	while(1)
	{
		delay_ms(1);
		key_moniter();
		i++;
		if(i>=200)
		{
			i=0;
			LED1 = !LED1;
			//printf("system running!\r\n");
		}
	}
} 








