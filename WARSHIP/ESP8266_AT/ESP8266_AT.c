/*Esp8266 AT指令库目前尚不稳定，待测试完成会加上代码注释....


 */


#include "ESP8266_AT.h"
#include "timer.h"
#include "delay.h"
#include "LCD.h"
#include "LED.h"

u8 RX_BUFF[RX_BUFF_LENGTH];
u16  RX_Pointer = 0;
u16  RX_Length  = 0;

u8 ConfFlag = 0;
u8 ESP_response_Flag =0;
/*
	FullFlag[7:0]
	bit		function
	0		*Uart_monitor Enable bit
	1		*
	2		*
	3		*
	4		*
	5		*
	6		*
	7		*
*/
u8 Cmd_Index = 0;
u8 *ESP_Cmd_Table[] = 
{
	$STR"AT+CWMODE=1\r\n",										//[0]设置模式为STA模式
	$STR"AT+CWJAP=\"MI8\",\"111222333\"\r\n",					//[1]连接WIFI
	$STR"AT+CIPMUX=0\r\n",										//[2]设置为单连接模式
	$STR"AT+CIPSTART=\"TCP\",\"quan.suning.com\",80\r\n",		//[3]建立TCP连接
	$STR"AT+CIPMODE=1\r\n",										//[4]进入透传模式
	$STR"AT+CIPSEND\r\n",										//[5]开始传输数据，收到">"后可开始发送数据
	$STR"+++",													//[6]退出透传模式,无返回提示信息
	$STR"AT+CIPSTATUS\r\n",										//[7]查询TCP连接状态
	$STR"AT+CIPCLOSE\r\n",      								//[8]断开TCP连接
	$STR"AT+CWQAP\r\n",      									//[9]断开WIFI连接
};

void Uart_RX_Monitor_Init()
{
	Timer_InitDef timer7_user1 = 
	{
		.TIMx = TIM7,
		.ms   = 1,
		.NVIC_Priority = 3,
		.event_handler = Uart_monitor,
	};
	
	timer_init(&timer7_user1);
	ConfFlag = 0x00;     //关闭所有功能
}

void USART3_IRQHandler()
{
	if(USART3->SR&(1<<5))
	{
		RX_BUFF[RX_Pointer++] = USART3->DR;
		RX_Length ++;
	}
}

void Uart_monitor()
{
	static u8 off_time=0;
	static u8 back_Index = 0;
	
	if(ConfFlag&0x01)   //Uart_monitor Enable bit
	{
		if(RX_Pointer>0)
		{
			if(back_Index != RX_Pointer)
			{
				back_Index = RX_Pointer;
				off_time = 0;
			}
			else
			{
				off_time++;
				if(off_time>=15)  //超过15ms没有数据到来就认为一帧数据已经结束
				{
					off_time = 0;
					ESP_response_Flag = 1;
					USART3_Monitor_OFF;
					//Uart_action();
				}
			}
		}
		else
		{
			back_Index = 0;
		}
	}
}

void Uart_action()
{
	// USART3_Monitor_OFF;
	
	// RX_BUFF[RX_Pointer] = '\0';
	// uart_send_str(USART1,RX_BUFF);
	// RX_Pointer = 0;
	// RX_Length  = 0;
	
	// USART3_Monitor_ON;
}

u8 ESP_Send_CMD(u8 *cmd, u16 WaitTime, u8 *check_cmd)    //发送命令并检查返回，若成功则返回 ESP_Response_OK    失败返回 ESP_Wait_OverTime
{
	u16 i,j;
	u8 * check = check_cmd;
	u8 return_flag;
	u8 check_len=0;
	while(*check!='\0')
	{
		check_len++;
		check++;
	}
	check = check_cmd;
	USART3_Monitor_ON;		//开始监听数据帧回复
	uart_send_str(USART3,cmd);
	
	if(check_cmd!=0)
	{
		delay_ms(5);                   //延时等待，确保接收检测成功
		while(WaitTime--)
		{
			
			if(ESP_response_Flag && (RX_Length>=check_len))
			{
			
				ESP_response_Flag = 0;
				
					for(i=0;i<RX_Length;i++)
					{
						if(RX_BUFF[i] == check_cmd[0])
						{
							j=1;
							i++;
							while(j<check_len)
							{
								if(check[j++]!=RX_BUFF[i++])
									break;
							}
							if(j==check_len)
							{
								USART3_Monitor_OFF;
								RX_Pointer = RX_Length = 0;
								return ESP_Response_OK;
							}
						}
					}
				RX_Pointer = RX_Length = 0;
				USART3_Monitor_ON;
			}
			delay_ms(1);
		}
		USART3_Monitor_OFF;
		RX_Pointer = RX_Length = 0;
		return ESP_Wait_OverTime;
	}
	USART3_Monitor_OFF;
	RX_Pointer = RX_Length = 0;

	return 0;
}

void ESP_Shell(u8 *cmd, u16 WaitTime, u8 *check_cmd, u16 x, u16 y, u8 *Shell_Test)
{
	u8 j;
	j = ESP_Send_CMD(cmd, WaitTime, check_cmd);
	if(j==ESP_Response_OK)
	{
		LCD_show_str(x,y,Shell_Test,BLACK,BKOR);
	}
	else if(j==ESP_Wait_OverTime)
	{
		LCD_show_str(x,y,$STR"error!",RED,BKOR);
	}
}

