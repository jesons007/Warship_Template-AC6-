#ifndef ESP8266_AT_H
#define ESP8266_AT_H
#include "sys.h"
#include "MyUart.h"

#define RX_BUFF_LENGTH  1024
#define USART3_Monitor_ON    ConfFlag |= 0x01
#define USART3_Monitor_OFF   ConfFlag &= 0xfe

//AT_CMD_TABLE
#define AT_TEST         $STR"AT\r\n"


//ESP response flag!
#define ESP_Wait_OverTime   0xee
#define ESP_Response_Error  0xef
#define ESP_Response_OK     0xf0

void Uart_monitor(void);
void Uart_action(void);
void Uart_RX_Monitor_Init(void);

u8 ESP_Send_CMD(u8 *cmd, u16 WaitTime, u8 *check_cmd);
void ESP_Shell(u8 *cmd, u16 WaitTime, u8 *check_cmd, u16 x, u16 y, u8 *Shell_Test);

#endif
