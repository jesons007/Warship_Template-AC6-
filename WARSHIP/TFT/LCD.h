#ifndef _LCD_H_
#define _LCD_H_
#include "stm32f10x.h"

#define BKOR    WHITE   //主屏背景颜色

typedef struct
{
	vu16 LCD_REG;
	vu16 LCD_RAM;
} LCD_typedef;

#define LCD_BASE          ((u32)(0X6C000000|0X000007FE))
#define LCD               ((LCD_typedef *)LCD_BASE)
#define LCD_LED            PBout(0)    //背光控制

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色

//扫描方向定义
#define L2R_U2D  0 //从左到右,从上到下(默认)
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上

#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左

void LCD_init(u16 color);
void LCD_write_reg(u16 cmd);
void LCD_write_ram(u16 dat);
vu16 LCD_read_ram(void);
void LCD_WriteReg(u16 reg, u16 vaul);
void LCD_Clear(u16 color);
void LCD_Set_Window(u16 X0, u16 Y0, u16 X1, u16 Y1, u16 color);
void LCD_Start_Write(void);
void LCD_Draw_Point(u16 x, u16 y, u16 color);
void LCD_Draw_Line(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
void LCD_Show_OneChar(u16 x,u16 y,u8 chr,u16 color,u16 Back_Ground);
void LCD_show_char(u16 x,u16 y,u8 chr,u16 color,u16 Back_Ground);
void LCD_show_str(u16 x,u16 y,u8 *p,u16 color, u16 Back_Ground);
void LCD_show_number(u16 x,u16 y,uint64_t num,u16 color,u16 Back_Ground,u8 chs);
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r,u16 color);
u16  LCD_read_id(void);
u16  LCD_Read_Point(u16 x, u16 y);
u8* HEX(u16 valu);

void LCD_SetCursor(u16 x, u16 y);
void LCD_Scan_Dir(u8 dir);		
void LCD_SetWin(u16 X0, u16 Y0, u16 X1, u16 Y1);

#endif

