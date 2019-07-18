#include "Include_config.h"

#include "sys.h"
#include "delay.h"	


void setup()
{
	delay_init(72);
	led_init();
	JTAG_Set(SWD_ENABLE);   //关闭JTAG
	LCD_init(BKOR);
	
	H_IIC_init(PG(13),PC(0));   //别忘了修改H_IIC.c里面的引脚配置
	oled_init();
	oled_show_str(0,0,(u8*)"jesons007 ok!", $1608);
	OLED_REFRESH_FULL;
	
	key_init(); //TIM6
	
	myuart_init(USART3,115200,PB(11),PB(10));	

	myuart_init(USART1,115200,PA(10),PA(9));
	Uart_Rx_IRQENR(USART1,DISABLE);
	Uart_RX_Monitor_Init();
}


int main(void)
{			
	u8 i=0,j=0;
	setup();
	uart_send_str(USART1,$STR"SYS OK!\r\n");
	
	//ESP_Shell(AT_TEST,100,$STR"OK",0,0,$STR"AT_OK");

	while(1) 
	{
		key_moniter();
		i++;
		if(i>=200)
		{
			i=0;
			LED0 = !LED0;
		}
		delay_ms(1);	
	}
	
} 






