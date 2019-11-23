#include "Nano_TFT.h"
#include "LCD_Font.h"

#define Nano_TFT_clk_1   (GPIOB->ODR|=0x2000)
#define Nano_TFT_clk_0   (GPIOB->ODR&=0xDFFF)

#define Nano_TFT_dat_1   (GPIOB->ODR|=0x8000)
#define Nano_TFT_dat_0   (GPIOB->ODR&=0x7FFF)

#define Nano_TFT_cs_1   (GPIOG->ODR|=0x0080)
#define Nano_TFT_cs_0   (GPIOG->ODR&=0xFF7F)

#define Nano_TFT_bl_1   (GPIOG->ODR|=0x0100)
#define Nano_TFT_bl_0   (GPIOG->ODR&=0xFEFF)

#define software_spi GPIOB->CRH = 0x30300000
#define hardware_spi GPIOB->CRH = 0xB0B00000


int lcd_i;
u8 spi_lcd_byte_bit_len   = 9;
u8 spi_lcd_byte_bit_index = 0x80;
u8 spi2_write(SPI_TypeDef *SPIx, u8 byte)
{
	while(!(SPIx->SR&0x02));    //等待上一次发送完成
	SPIx->DR = byte;
	//while(!(SPIx->SR&0x01));    //等待接收完成
	for(lcd_i=0;lcd_i<3;lcd_i++)__NOP();
	return SPIx->DR;
}
void spi_lcd_9bit_write(u8 c_d, u8 byte)    //软加硬件spi
{
    Nano_TFT_cs_0;
	software_spi;
    if(c_d)Nano_TFT_dat_1;
    else Nano_TFT_dat_0;
    Nano_TFT_clk_0;
    Nano_TFT_clk_1;
	hardware_spi;
    
	spi2_write(SPI2,byte);
	// SPI_Write_Read(SPI2,byte);

    Nano_TFT_cs_1;
}
// void spi_lcd_9bit_write(u8 c_d, u8 byte)   //纯软件spi
// {
//     Nano_TFT_cs_0;
//     if(c_d)Nano_TFT_dat_1;
//     else Nano_TFT_dat_0;
//     Nano_TFT_clk_0;
//     Nano_TFT_clk_1;
//     for(spi_lcd_byte_bit_index=0x80;spi_lcd_byte_bit_index!=0;spi_lcd_byte_bit_index>>=1)
//     {
//         if(spi_lcd_byte_bit_index&byte)Nano_TFT_dat_1;
//         else Nano_TFT_dat_0;
//         Nano_TFT_clk_0;
//         Nano_TFT_clk_1;
//     }
//     Nano_TFT_cs_1;
// }
void Nano_tft_write__cmd(u8 cmd)
{
    spi_lcd_9bit_write(0,cmd);
}
void Nano_tft_write_data(u8 data)
{
    spi_lcd_9bit_write(1,data);
}

void Nano_tft_set_window(u16 x1, u16 y1, u16 x2, u16 y2)
{
	Nano_tft_write__cmd(0x2a); //--Set MX1_ADDR
	Nano_tft_write_data(x1 >> 8 & 0xff);   //--Set MX1_ADDR
	Nano_tft_write_data(x1);
	Nano_tft_write_data(x2 >> 8 & 0xff);    //Set MX2_ADDR
	Nano_tft_write_data(x2);
	Nano_tft_write__cmd(0x2b);  //--Set MY1_ADDR
	Nano_tft_write_data(y1 >> 8 & 0xff);    //--Set MY1_ADDR
	Nano_tft_write_data(y1);
	Nano_tft_write_data(y2 >> 8 & 0xff);    //Set MY2_ADDR
	Nano_tft_write_data(y2);
	Nano_tft_write__cmd(0x2C); //写DDRAM
}

void Nano_tft_clear_12bit_pix(u8 b1,u8 b2,u8 b3)
{
	int i;
	Nano_tft_write__cmd(0x3A); 	//Interface Mode Control
	Nano_tft_write_data(0x03); 	// 12 bits / pixel
	Nano_tft_set_window(0, 0, 239, 239);
	
	for (i = 0; i < 28800; i++)
	{
		Nano_tft_write_data(b1);
		Nano_tft_write_data(b2);
		Nano_tft_write_data(b3);
	}
	Nano_tft_write__cmd(0x3A); 	//Interface Mode Control
	Nano_tft_write_data(0x05); 	// 16 bits / pixel
}
void Nano_tft_clear_16bit_pix(u16 color)
{
    int i;
    u8 b1 = color>>8;
    u8 b2 = (u8)color;
    Nano_tft_set_window(0, 0, 239, 239);
    for (i = 0; i < 57600; i++)
	{
		Nano_tft_write_data(b1);
		Nano_tft_write_data(b2);
	}
}

void Nano_TFT_Init()
{
	SPI_init(SPI2, SPI_MODE_2, SPI_8Bits_Mode, 1);
    GPIO_PIN_Init(PB(13),OUTPUT_PP);     //spi2 clk (hardware pin)
    GPIO_PIN_Init(PB(15),OUTPUT_PP);     //spi2 mosi(hardware pin)
    GPIO_PIN_Init(PG(7), OUTPUT_PP);     //cs
    GPIO_PIN_Init(PG(8), OUTPUT_PP);     //BL
    Nano_TFT_clk_1;   //时钟空闲为1，上升沿采样
    Nano_TFT_dat_1;
    Nano_TFT_cs_1;
    Nano_TFT_bl_1;
	
    
    delay_ms(120);
	Nano_tft_write__cmd(0x11);
	delay_ms(120); //Delay 120ms

    //--------------------------------Display and color format setting-------------------

	Nano_tft_write__cmd(0x36);
	Nano_tft_write_data(0x00);
	Nano_tft_write__cmd(0x3a);
	Nano_tft_write_data(0x05);
//--------------------------------ST7789S Frame rate setting-------------------------

	Nano_tft_write__cmd(0xb2);
	Nano_tft_write_data(0x0c);
	Nano_tft_write_data(0x0c);
	Nano_tft_write_data(0x00);
	Nano_tft_write_data(0x33);
	Nano_tft_write_data(0x33);
	Nano_tft_write__cmd(0xb7);
	Nano_tft_write_data(0x35);
//---------------------------------ST7789S Power setting-----------------------------

	Nano_tft_write__cmd(0xbb);
	Nano_tft_write_data(0x35);
	Nano_tft_write__cmd(0xc0);
	Nano_tft_write_data(0x2c);
	Nano_tft_write__cmd(0xc2);
	Nano_tft_write_data(0x01);
	Nano_tft_write__cmd(0xc3);
	Nano_tft_write_data(0x13);
	Nano_tft_write__cmd(0xc4);
	Nano_tft_write_data(0x20);
	Nano_tft_write__cmd(0xc6);
	Nano_tft_write_data(0x0f);
	Nano_tft_write__cmd(0xca);
	Nano_tft_write_data(0x0f);
	Nano_tft_write__cmd(0xc8);
	Nano_tft_write_data(0x08);
	Nano_tft_write__cmd(0x55);
	Nano_tft_write_data(0x90);
	Nano_tft_write__cmd(0xd0);
	Nano_tft_write_data(0xa4);
	Nano_tft_write_data(0xa1);
//--------------------------------ST7789S gamma setting------------------------------
	Nano_tft_write__cmd(0xe0);
	Nano_tft_write_data(0xd0);
	Nano_tft_write_data(0x00);
	Nano_tft_write_data(0x06);
	Nano_tft_write_data(0x09);
	Nano_tft_write_data(0x0b);
	Nano_tft_write_data(0x2a);
	Nano_tft_write_data(0x3c);
	Nano_tft_write_data(0x55);
	Nano_tft_write_data(0x4b);
	Nano_tft_write_data(0x08);
	Nano_tft_write_data(0x16);
	Nano_tft_write_data(0x14);
	Nano_tft_write_data(0x19);
	Nano_tft_write_data(0x20);
	Nano_tft_write__cmd(0xe1);
	Nano_tft_write_data(0xd0);
	Nano_tft_write_data(0x00);
	Nano_tft_write_data(0x06);
	Nano_tft_write_data(0x09);
	Nano_tft_write_data(0x0b);
	Nano_tft_write_data(0x29);
	Nano_tft_write_data(0x36);
	Nano_tft_write_data(0x54);
	Nano_tft_write_data(0x4b);
	Nano_tft_write_data(0x0d);
	Nano_tft_write_data(0x16);
	Nano_tft_write_data(0x14);
	Nano_tft_write_data(0x21);
	Nano_tft_write_data(0x20);
	Nano_tft_write__cmd(0x29);
	Nano_tft_write__cmd(0x21);

    Nano_tft_clear_16bit_pix(0xffff);  //清屏全白
    //RGB565
}


void Nano_tft_draw_point(u8 x,u8 y,u16 color)
{
	Nano_tft_write__cmd(0x2a); //--Set MX1_ADDR
	Nano_tft_write_data(x >> 8 & 0xff);   //--Set MX1_ADDR
	Nano_tft_write_data(x);
	Nano_tft_write__cmd(0x2b);  //--Set MY1_ADDR
	Nano_tft_write_data(y >> 8 & 0xff);    //--Set MY1_ADDR
	Nano_tft_write_data(y);
	Nano_tft_write__cmd(0x2C); //写DDRAM

	Nano_tft_write_data(color>>8);
	Nano_tft_write_data((u8)color);
}

void Nano_tft_show_char(u16 x,u16 y,u8 chr,u16 color,u16 Back_Ground)
{
	u8 i,j;
	u8 temp;
	u16 y0=y;
	chr -= ' ';
	for(i=0;i<36;i++)
	{
		temp = LCD_asc2_2412[chr][i];
		for(j=0x80;j!=0;j>>=1)
		{
			if(temp&j)Nano_tft_draw_point(x,y,color);
			else Nano_tft_draw_point(x,y,Back_Ground);
			y++;
			if((y-y0)==24)
			{
				x++;
				y = y0;
			}
			
		}
	}
}

void Nano_tft_show_str(u16 x,u16 y,u8 *p,u16 color, u16 Back_Ground)
{
	while(*p!='\0')
	{
		if(x>239)
		{
			x=0;
			y+=24;
		}
		if(y>239)
		{
			x=y=0;
		}
		Nano_tft_show_char(x,y,*p,color,Back_Ground);
		x+=12;
		p++;
	}
}

void Nano_tft_show_number(u16 x,u16 y,uint64_t num,u16 color,u16 Back_Ground,u8 chs)
{
	uint64_t n = num;
	u8 str[20];
	signed char len=0,i;
	do
	{
		len++;
		num/=10;
	}while(num!=0);
	
	for(i=len-1;i>=0;i--)
	{
		str[i]=n%10+'0';
		n/=10;
	}
	
	if(len<=chs)
	{
		while(len<chs)
		{
			str[len++] = ' ';
		}
		str[len]='\0';
	}
	else
	{
		str[chs]='\0';
	}
	
	Nano_tft_show_str(x,y,str,color,Back_Ground);
	
}
