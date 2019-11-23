#include "Mini_TFT.h"
#include "LCD_Font.h"
#include "lcd.h"

/*
    RST                 PD3
    TE					PD6            		
    CS                  PG13
    PG14           		D/C
	WR                  PB3
	RD                  PA8
	DB:0~7              PC0~7
	BL                  PB4
    Mini_TFT_
    */
// #define Mini_TFT_RST   PDout(3)
// #define Mini_TFT_BL    PBout(4)
// #define Mini_TFT_TE    (GPIOD->IDR & 0x40)
// #define Mini_TFT_Data_Bus GPIOC->ODR

// #define Mini_TFT_CS_set_1_  GPIOG->ODR |= 0x2000
// #define Mini_TFT_CS_set_0_  GPIOG->ODR &= 0xDFFF

// #define Mini_TFT_DC_set_1_  GPIOG->ODR |= 0x4000
// #define Mini_TFT_DC_set_0_  GPIOG->ODR &= 0xBFFF

// #define Mini_TFT_WR_set_1_  GPIOB->ODR |= 0x0008
// #define Mini_TFT_WR_set_0_  GPIOB->ODR &= 0xFFF7

// #define Mini_TFT_RD_set_1_  GPIOA->ODR |= 0x0100
// #define Mini_TFT_RD_set_0_  GPIOA->ODR &= 0xFEFF


void Mini_TFT_Write(u8 c_d, u8 byte)    //
{
    Mini_TFT_RD_set_1_;
    Mini_TFT_CS_set_0_;
	if(c_d)Mini_TFT_DC_set_1_;
    else Mini_TFT_DC_set_0_;

    Mini_TFT_Data_Bus = byte;
    Mini_TFT_WR_set_0_;
    Mini_TFT_WR_set_1_;
    
    Mini_TFT_CS_set_1_;
}

void Mini_tft_write__cmd(u8 cmd)
{
    // Mini_TFT_Write(0,cmd);
    Mini_TFT_CS_set_0_;

    Mini_TFT_DC_set_0_;

    Mini_TFT_Data_Bus = cmd;
    Mini_TFT_WR_set_0_;
    Mini_TFT_WR_set_1_;
    
	Mini_TFT_CS_set_1_;
}
void Mini_tft_write_data(u8 data)
{
    // Mini_TFT_Write(1,data);
	Mini_TFT_CS_set_0_;
	Mini_TFT_DC_set_1_;

    Mini_TFT_Data_Bus = data;
    Mini_TFT_WR_set_0_;
    Mini_TFT_WR_set_1_;
    
    Mini_TFT_CS_set_1_;
}

void Mini_tft_set_window(u16 x1, u16 y1, u16 x2, u16 y2)
{

	Mini_tft_write__cmd(0x2a); //--Set MX1_ADDR
	Mini_tft_write_data(x1 >> 8 & 0xff);   //--Set MX1_ADDR
	Mini_tft_write_data(x1);
	Mini_tft_write_data(x2 >> 8 & 0xff);    //Set MX2_ADDR
	Mini_tft_write_data(x2);
	Mini_tft_write__cmd(0x2b);  //--Set MY1_ADDR
	Mini_tft_write_data(y1 >> 8 & 0xff);    //--Set MY1_ADDR
	Mini_tft_write_data(y1);
	Mini_tft_write_data(y2 >> 8 & 0xff);    //Set MY2_ADDR
	Mini_tft_write_data(y2);
	Mini_tft_write__cmd(0x2C); //

}

void Mini_tft_clear_16bit_pix(u16 color)
{
    int i;
    u8 b1 = color>>8;
    u8 b2 = (u8)color;

    Mini_tft_set_window(0,0,239,319);
	
    for (i = 0; i < 320*240; i++)
	{
		Mini_tft_write_data(b1);
		Mini_tft_write_data(b2);
	}
	
}

void Mini_TFT_Test()
{
	int i;
	u16 color = YELLOW;
    u8 b1 = color>>8;
    u8 b2 = (u8)color;
    u16 x=0;
    u16 y=0;
    Mini_tft_set_window(100,200,199,299);

    for (i = 0; i < 100*100; i++)
	{
		Mini_tft_write_data(b1);
		Mini_tft_write_data(b2);
	}
	delay_ms(500);
	color = GREEN;
    b1 = color>>8;
    b2 = (u8)color;
	for (i = 0; i < 100*100; i++)
	{
		Mini_tft_write_data(b1);
		Mini_tft_write_data(b2);
	}

}

void Mini_TFT_Init()
{
    /*
        RST                 PD3
        TE                  PD6
        CS                  PG13   low active
        RS                  PG14
        WR                  PB3
        RD                  PA8
        DB:0~7              PC0~7
        BL                  PB4
    */
    GPIO_Init(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, OUTPUT_PP);//data bus
    GPIO_PIN_Init(PD(3),OUTPUT_PP);  
    GPIO_PIN_Init(PD(6),INPUT_UP);  
    GPIO_PIN_Init(PG(13), OUTPUT_PP);
    GPIO_PIN_Init(PG(14), OUTPUT_PP);
    GPIO_PIN_Init(PB(3), OUTPUT_PP); 
    GPIO_PIN_Init(PA(8), OUTPUT_PP); 
    GPIO_PIN_Init(PB(4), OUTPUT_PP); 
	
    GPIOC->ODR |= 0x00ff;
    Mini_TFT_CS_set_1_;
    Mini_TFT_DC_set_1_;
    Mini_TFT_WR_set_1_;
    Mini_TFT_RD_set_1_;

	Mini_TFT_RST = 1;
	delay_ms(1);
	Mini_TFT_RST = 0;
	delay_ms(10); // Delayms 10ms   // This delay time is necessary
	Mini_TFT_RST = 1;
    delay_ms(120); // Delayms 120 ms
	Mini_tft_write__cmd(0x11);//sleep out
	delay_ms(120); //Delay 120ms

    //--------------------------------Display and color format setting-------------------

	Mini_tft_write__cmd(0x36);
	Mini_tft_write_data(0x00);
	Mini_tft_write__cmd(0x3a);
	Mini_tft_write_data(0x05);
//--------------------------------ST7789S Frame rate setting-------------------------

	Mini_tft_write__cmd(0xb2);
	Mini_tft_write_data(0x0c);
	Mini_tft_write_data(0x0c);
	Mini_tft_write_data(0x00);
	Mini_tft_write_data(0x33);
	Mini_tft_write_data(0x33);
	Mini_tft_write__cmd(0xb7);
	Mini_tft_write_data(0x35);
//---------------------------------ST7789S Power setting-----------------------------

	Mini_tft_write__cmd(0xbb);
	Mini_tft_write_data(0x35);
	Mini_tft_write__cmd(0xc0);
	Mini_tft_write_data(0x2c);
	Mini_tft_write__cmd(0xc2);
	Mini_tft_write_data(0x01);
	Mini_tft_write__cmd(0xc3);
	Mini_tft_write_data(0x13);
	Mini_tft_write__cmd(0xc4);
	Mini_tft_write_data(0x20);
	Mini_tft_write__cmd(0xc6);
	Mini_tft_write_data(0x0f);
	Mini_tft_write__cmd(0xca);
	Mini_tft_write_data(0x0f);
	Mini_tft_write__cmd(0xc8);
	Mini_tft_write_data(0x08);
	Mini_tft_write__cmd(0x55);
	Mini_tft_write_data(0x90);
	Mini_tft_write__cmd(0xd0);
	Mini_tft_write_data(0xa4);
	Mini_tft_write_data(0xa1);
//--------------------------------ST7789S gamma setting------------------------------
	Mini_tft_write__cmd(0xe0);
	Mini_tft_write_data(0xd0);
	Mini_tft_write_data(0x00);
	Mini_tft_write_data(0x06);
	Mini_tft_write_data(0x09);
	Mini_tft_write_data(0x0b);
	Mini_tft_write_data(0x2a);
	Mini_tft_write_data(0x3c);
	Mini_tft_write_data(0x55);
	Mini_tft_write_data(0x4b);
	Mini_tft_write_data(0x08);
	Mini_tft_write_data(0x16);
	Mini_tft_write_data(0x14);
	Mini_tft_write_data(0x19);
	Mini_tft_write_data(0x20);
	Mini_tft_write__cmd(0xe1);
	Mini_tft_write_data(0xd0);
	Mini_tft_write_data(0x00);
	Mini_tft_write_data(0x06);
	Mini_tft_write_data(0x09);
	Mini_tft_write_data(0x0b);
	Mini_tft_write_data(0x29);
	Mini_tft_write_data(0x36);
	Mini_tft_write_data(0x54);
	Mini_tft_write_data(0x4b);
	Mini_tft_write_data(0x0d);
	Mini_tft_write_data(0x16);
	Mini_tft_write_data(0x14);
	Mini_tft_write_data(0x21);
	Mini_tft_write_data(0x20);
	Mini_tft_write__cmd(0x29);
	Mini_tft_write__cmd(0x21);

    Mini_TFT_BL = 1;
    Mini_tft_clear_16bit_pix(WHITE);  //ÇåÆÁÈ«°×
    //RGB565
}


void Mini_tft_draw_point(u16 x,u16 y,u16 color)
{
	Mini_tft_write__cmd(0x2a); //--Set MX1_ADDR
	Mini_tft_write_data(x >> 8 & 0xff);   //--Set MX1_ADDR
	Mini_tft_write_data(x);
	Mini_tft_write__cmd(0x2b);  //--Set MY1_ADDR
	Mini_tft_write_data(y >> 8 & 0xff);    //--Set MY1_ADDR
	Mini_tft_write_data(y);
	Mini_tft_write__cmd(0x2C); //Ð´DDRAM

	Mini_tft_write_data(color>>8);
	Mini_tft_write_data((u8)color);
}

void Mini_tft_show_char(u16 x,u16 y,u8 chr,u16 color,u16 Back_Ground)
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
			if(temp&j)Mini_tft_draw_point(x,y,color);
			else Mini_tft_draw_point(x,y,Back_Ground);
			y++;
			if((y-y0)==24)
			{
				x++;
				y = y0;
			}
			
		}
	}
}

void Mini_tft_show_str(u16 x,u16 y,u8 *p,u16 color, u16 Back_Ground)
{
	while(*p!='\0')
	{
		if(x>239)
		{
			x=0;
			y+=24;
		}
		if(y>319)
		{
			x=y=0;
		}
		Mini_tft_show_char(x,y,*p,color,Back_Ground);
		x+=12;
		p++;
	}
}

void Mini_tft_show_number(u16 x,u16 y,uint64_t num,u16 color,u16 Back_Ground,u8 chs)
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
	
	Mini_tft_show_str(x,y,str,color,Back_Ground);
	
}

void Mini_tft_Draw_img_240x320(u16 x,u16 y, u8 *img_buf)
{
	int i,j=0;
	Mini_tft_set_window(x,y,x+239,y+319);

	for(i=0;i<76800;i++)
	{
		Mini_tft_write_data(img_buf[j+1]);
		Mini_tft_write_data(img_buf[j]);
		j+=2;
	}
}


void Mini_tft_Draw_img_(u16 x0,u16 y0, u16 width,u16 height, u8 *imgbuf)
{
	int i,j=0;
	Mini_tft_set_window(x0,y0,x0+width-1,y0+height-1);

	for(i=0;i<width*height;i++)
	{
		Mini_tft_write_data(imgbuf[j+1]);
		Mini_tft_write_data(imgbuf[j]);
		j+=2;
	}

}
