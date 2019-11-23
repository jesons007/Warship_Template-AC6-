#ifndef _Mini_TFT_H_
#define _Mini_TFT_H_
#include "SPI.h"
#include "GPIO.h"
#include "sys.h"
#include "delay.h"

#define Mini_TFT_RST   PDout(3)
#define Mini_TFT_BL    PBout(4)
#define Mini_TFT_TE    (GPIOD->IDR & 0x40)
#define Mini_TFT_Data_Bus GPIOC->ODR

#define Mini_TFT_CS_set_1_  GPIOG->ODR |= 0x2000
#define Mini_TFT_CS_set_0_  GPIOG->ODR &= 0xDFFF

#define Mini_TFT_DC_set_1_  GPIOG->ODR |= 0x4000
#define Mini_TFT_DC_set_0_  GPIOG->ODR &= 0xBFFF

#define Mini_TFT_WR_set_1_  GPIOB->ODR |= 0x0008
#define Mini_TFT_WR_set_0_  GPIOB->ODR &= 0xFFF7

#define Mini_TFT_RD_set_1_  GPIOA->ODR |= 0x0100
#define Mini_TFT_RD_set_0_  GPIOA->ODR &= 0xFEFF

void Mini_TFT_Init(void);
void Mini_TFT_Write(u8 c_d, u8 byte);
void Mini_tft_write__cmd(u8 cmd);
void Mini_tft_write_data(u8 data);
void Mini_TFT_Test(void);
void Mini_tft_set_window(u16 x1, u16 y1, u16 x2, u16 y2);

void Mini_tft_clear_16bit_pix(u16 color);
void Mini_tft_draw_point(u16 x,u16 y,u16 color);

void Mini_tft_show_char(u16 x,u16 y,u8 chr,u16 color,u16 Back_Ground);
void Mini_tft_show_str(u16 x,u16 y,u8 *p,u16 color, u16 Back_Ground);
void Mini_tft_show_number(u16 x,u16 y,uint64_t num,u16 color,u16 Back_Ground,u8 chs);

void Mini_tft_Draw_img_240x320(u16 x,u16 y, u8 *img_buf);

/*
Func: 显示图片
x0,y0 :图片起始点坐标
width,height :分辨率（宽X高 = width X height）
imgbuf :图片取模指针
*/
void Mini_tft_Draw_img_(u16 x0,u16 y0, u16 width,u16 height, u8 *imgbuf);
#endif
