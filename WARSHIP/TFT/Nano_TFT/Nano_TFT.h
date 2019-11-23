#ifndef _Nano_TFT_H_
#define _Nano_TFT_H_
#include "SPI.h"
#include "GPIO.h"
#include "sys.h"
#include "delay.h"

void Nano_TFT_Init(void);
void spi_lcd_9bit_write(u8 c_d, u8 byte);
void Nano_tft_write__cmd(u8 cmd);
void Nano_tft_write_data(u8 data);

void Nano_tft_set_window(u16 x1, u16 y1, u16 x2, u16 y2);

void Nano_tft_clear_12bit_pix(u8 b1,u8 b2,u8 b3);
void Nano_tft_clear_16bit_pix(u16 color);
void Nano_tft_draw_point(u8 x,u8 y,u16 color);

void Nano_tft_show_char(u16 x,u16 y,u8 chr,u16 color,u16 Back_Ground);
void Nano_tft_show_str(u16 x,u16 y,u8 *p,u16 color, u16 Back_Ground);
void Nano_tft_show_number(u16 x,u16 y,uint64_t num,u16 color,u16 Back_Ground,u8 chs);
#endif
