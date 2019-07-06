#include "oled.h"
#include "OLED_font.h"

/*------------OLED库使用说明--------------*/
/*
OLED库包含3个文件：oled.c, oled.h, OLED_font.h, 其中OLED_font.h为字库头文件，包含1206,1608,2412三种字体的ASCLL字库（不含中文字库）
仅适用于4脚IIC接口的OLED
使用高速IIC接口驱动，动态刷新无压力*=* 刷新整屏（128*64）平均用时15.6ms
函数使用说明：
	oled_init()						//初始化OLED并清屏， *调用之前需要先调用H_IIC_init函数初始化IIC接口
	oled_clear(u8 n)				//oled清屏函数，n=0时清屏
	u8 OLED_BUFF[128][8];   		//oled显示缓冲区
	------以下函数的操作均只操作显示缓冲区(调用之后并不会显示到屏幕上)-----
		draw_point(u8 x, u8 y)										//在(x,y)坐标处画点
		clear_point(u8 x,u8 y)										//清除(x,y)处的坐标点
		oled_show_char(u8 x,u8 y,u8 chr,u8 font)					//以(x,y)为起点(字符的左上角)显示字符chr，font：字体代号（可选参数有$1206， $1608， $2412）
		oled_show_str(u8 x, u8 y, u8 *p,u8 font)					//以(x,y)为起点(字符串的左上角)显示字符串，*p为字符串指针，字符串过长会自动换行。
		oled_show_num(u8 x, u8 y, uint64_t num,u8 font,u8 chs)		//以(x,y)为起点显示数字num，chs:数字占位个数，例如chs=4,显示数字888 --> 则会显示字符串"888 "
					font参数：字体，包含$1206, $1608, $2412
	------------oled坐标分布见./OLED_Address.jpg

	oled_refresh(u8 page, u8 x0, u8 x1)函数说明：
		刷新oled显示，将显示缓冲区的数据写入oled中，
		参数说明：
			page：		//要刷新的页地址，页地址分布见./OLED_Address.jpg， 共8页，可选参数如下，支持或操作
				Page7
				Page6
				Page5
				Page4
				Page3
				Page2
				Page1
				Page0
			x0, x1:		//刷新的起点横坐标和终点横坐标，刷新每一页时只刷新x0~x1之内的像素点，限制关系：0<= x0 <= x1 <=127

eg:OLED_IIC引脚对应关系为SCL->PA5   SDA->PA6
	首先调用
		H_IIC_init(PA(5),PA(6));
	然后调用
		oled_init();
	初始化完成！
	调用
		oled_show_str(0,0,"Jesons007",$1608);
		oled_show_num(0,16,6666,$1608,4);
		oled_refresh(Page0|Page1|Page2|Page3|Page4|Page5|Page6|Page7,0,127)    	//刷新整屏
	将显示所要的信息。
*/

u8 OLED_BUFF[128][8];

void oled_refresh(u8 page, u8 x0, u8 x1)  //0 <= x0 <= x1 <= 127
{
	u8 i,j;
	u8 k = 0;
	u8 lsb = x0&0x0f;
	u8 msb = 0x10+(x0>>4);
	u8 sta = x1+1;
	
	for(i=1;i!=0;i<<=1)
	{
		if(i&page)
		{
			oled_wrcmd(0xb0+k);
			oled_wrcmd(lsb);
			oled_wrcmd(msb);
			for(j=x0;j<sta;j++)
			{
				oled_wrdat(OLED_BUFF[j][k]);
			}
		}
		k++;
	}
	
}

void oled_wrcmd(u8 cmd)
{
    H_IIC_start();
    H_IIC_write(0x78);
    H_IIC_Wait_ACK();
    H_IIC_write(0x00);
    H_IIC_Wait_ACK();
    H_IIC_write(cmd);
    H_IIC_Wait_ACK();
    H_IIC_stop();
}

void oled_wrdat(u8 dat)
{
    H_IIC_start();
    H_IIC_write(0x78);
    H_IIC_Wait_ACK();
    H_IIC_write(0x40);
    H_IIC_Wait_ACK();
    H_IIC_write(dat);
    H_IIC_Wait_ACK();
    H_IIC_stop();
}

void oled_clear(u8 n)
{
    u8 i,j;
	for(i=0;i<8;i++)
	{
		oled_wrcmd(0xb0+i);
		oled_wrcmd(0x00);
		oled_wrcmd(0x10);
		for(j=0;j<128;j++)
		{
			oled_wrdat(n);
		}
	}	
}

void oled_init()
{
    delay_ms(50);
	
	oled_wrcmd(0XAE);            //启动代码
	oled_wrcmd(0XD5);
	oled_wrcmd(0X80);
	oled_wrcmd(0XA8);
	oled_wrcmd(0X3F);
	oled_wrcmd(0XD3);
	oled_wrcmd(0X00);
	oled_wrcmd(0X40);
	oled_wrcmd(0X8D);
	oled_wrcmd(0X14);
	oled_wrcmd(0X20);
	oled_wrcmd(0X02);
	oled_wrcmd(0XA1);
	oled_wrcmd(0XC0);
	oled_wrcmd(0XDA);
	oled_wrcmd(0X12);
	oled_wrcmd(0X81);
	oled_wrcmd(0XEF);
	oled_wrcmd(0XD9);
	oled_wrcmd(0XF1);
	oled_wrcmd(0XDB);
	oled_wrcmd(0X30);
	oled_wrcmd(0XA4);
	oled_wrcmd(0XA6);
	oled_wrcmd(0XAF);
	
    oled_clear(0x00);
}

void draw_point(u8 x, u8 y)
{
    u8 page,b=0x80;
	if(x>127||y>63)return;
	page =7 - y/8;
	y = y%8;
	b = b>>y;
	OLED_BUFF[x][page] |= b;
//	oled_wrcmd(0xb0+page);
//	oled_wrcmd(x&0x0f);
//	oled_wrcmd(0x10|(x>>4));
//	oled_wrdat(OLED_BUFF[x][page]);
}
void clear_point(u8 x,u8 y)
{
	u8 page,b=0x80;
	if(x>127||y>63)return;
	page =7 - y/8;
	y = y%8;
	b = b>>y;
	OLED_BUFF[x][page] &= ~b;
//	oled_wrcmd(0xb0+page);
//	oled_wrcmd(x&0x0f);
//	oled_wrcmd(0x10|(x>>4));
//	oled_wrdat(OLED_BUFF[x][page]);
}

void oled_show_char(u8 x,u8 y,u8 chr,u8 font)
{
	u8 y0, i, j, size;
	u8 temp;
	
	
	y0 = y;
	size = font;
	if(font==$2412)
		size = 24;
	
	chr = chr - ' ';
	
	for(i=0;i<font;i++)
	{
		if(font==$1206)
			temp = asc2_1206[chr][i];
		else if(font==$1608)
			temp = asc2_1608[chr][i];
		else if(font==$2412)
			temp = asc2_2412[chr][i];

		for(j=0x80;j!=0;j>>=1)
		{
			if(temp&j)draw_point(x,y);
			else clear_point(x,y);
			y++;
			if((y-y0)==size)
			{
				y = y0;
				x++;
				break;
			}
		}	
	}
}

void oled_show_str(u8 x, u8 y, u8 *p,u8 font)
{
	while((*p<='~')&&(*p>=' '))
	{
		if(x>(128-(font/2)))
		{
			x=0;
			y+=font;
		}
		if(y>(64-font))
		{
			x=y=0;
		}
		oled_show_char(x,y,*p,font);
		p++;
		x+=font/2;
	}
}


//chs:数字占位个数，例如chs=4,显示数字888 --> "888 "
void oled_show_num(u8 x, u8 y, uint64_t num,u8 font,u8 chs)
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
	
	
	oled_show_str(x,y,str,font);
	
}

/*
for(i=0;i<4;i++)
{
	for(j=0;j<16;j++)
	{
		oled_show_char(j*8,i*16,t,$1608);
	}
}
oled_refresh(Page0|Page1|Page2|Page3|Page4|Page5|Page6|Page7,0,127);
*/


