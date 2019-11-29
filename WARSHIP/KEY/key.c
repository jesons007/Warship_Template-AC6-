#include "key.h"

extern float pitch,roll,yaw; 		//欧拉角  航向角（yaw）、横滚角（roll）和俯仰角（pitch）

//				WK_UP  KEY0  KEY1  KEY2
u8 key_sta[4] = {1,     1,    1,    1};
u8 key_bak[4] = {1,     1,    1,    1};			//1:not press    0:pressed

#if  Matrixkeyboard_ENR

u8 KeySta[4][4] = {  				//全部矩阵按键的当前状态
    {1, 1, 1, 1},  
	{1, 1, 1, 1},  
	{1, 1, 1, 1},  
	{1, 1, 1, 1}
};
u8 Keybackup[4][4] = {  				//按键值备份，保存前一次的值
    {1, 1, 1, 1},  
	{1, 1, 1, 1},  
	{1, 1, 1, 1},  
	{1, 1, 1, 1}
};

const u8 KeyCodeMap[4][4] = {
    { '1', '2', '3', 'A' }, 			//1、	2、	  3、   A
    { '4', '5', '6', 'B' }, 			//4、	5、	  6、	B
    { '7', '8', '9', 'C' }, 			//7、	8、	  9、	C
    { '*', '0', '#', 'D' }  			//*、   0、   #、  	D
};

u8 keyout = 0;   							//矩阵按键扫描输出索引(0.1.2.3)
u8 keybuf[4][4] = {  						//矩阵按键扫描缓冲区
	{0xFF, 0xFF, 0xFF, 0xFF},  
	{0xFF, 0xFF, 0xFF, 0xFF},
    {0xFF, 0xFF, 0xFF, 0xFF},  
	{0xFF, 0xFF, 0xFF, 0xFF}
    };

#endif

void key_init(void)
{
	RCC->APB2ENR |= 1<<2;
	RCC->APB2ENR |= 1<<6;
	RCC->APB1ENR |= 1<<4;
#if  Matrixkeyboard_ENR
	Key_Out_Init(KEY_OUT1);
	Key_Out_Init(KEY_OUT2);
	Key_Out_Init(KEY_OUT3);
	Key_Out_Init(KEY_OUT4);
	Key_In_Init(KEY_IN1);
	Key_In_Init(KEY_IN2);
	Key_In_Init(KEY_IN3);
	Key_In_Init(KEY_IN4);
#endif
	GPIOA->CRL &= 0XFFFFFFF0;
	GPIOA->CRL |= 0X00000008;   
	GPIOA->ODR &= 0XFFFE;			//PA0下拉输入
	
	GPIOE->CRL &= 0XFFF000FF;
	GPIOE->CRL |= 0X00088800;
	GPIOE->ODR |= 0X001C;			//PE 2,3,4 上拉输入
	
	TIM6->PSC = 7199;				//100us计数一次
	TIM6->ARR = 9;
	TIM6->DIER |= 1;
	
	NVIC->IP[54]   = 0X00|(15<<4);   //中断优先级设置为15(最低)
	NVIC->ISER[1] |= 0X00400000;
	
	TIM6->CR1 |= 1;
}

#if  Matrixkeyboard_ENR
void Key_Out_Init(u8 pin)
{
	RCC->APB2ENR |= 1<<((pin>>4)+2);//使能GPIO的时钟
	*(uint32_t *)(GPIOA_BASE+1024*(pin>>4)+(((pin&0X0F)>7)?4:0)) &= ~(0X0000000F<<(4*(((pin&0X0F)<8)?(pin&0X0F):(pin&0X0F)-8)));
	*(uint32_t *)(GPIOA_BASE+1024*(pin>>4)+(((pin&0X0F)>7)?4:0)) |=  0X3<<(4*(((pin&0X0F)<8)?(pin&0X0F):(pin&0X0F)-8));
}

void Key_In_Init(u8 pin)
{
	RCC->APB2ENR |= 1<<((pin>>4)+2);//使能GPIO的时钟
	*(uint32_t *)(GPIOA_BASE+1024*(pin>>4)+(((pin&0X0F)>7)?4:0)) &= ~(0X0000000F<<(4*(((pin&0X0F)<8)?(pin&0X0F):(pin&0X0F)-8)));
	*(uint32_t *)(GPIOA_BASE+1024*(pin>>4)+(((pin&0X0F)>7)?4:0)) |=  0X8<<(4*(((pin&0X0F)<8)?(pin&0X0F):(pin&0X0F)-8));
	*(uint32_t *)(GPIOA_BASE+1024*(pin>>4)+0x0c) |= 1<<(pin&0X0F);

}
#endif

void key_scan()
{
	//				         WK_UP     KEY0     KEY1     KEY2
	static u16 key_buf[4] = {0X0000,  0XFFFF,  0XFFFF,  0XFFFF};
	u8 i;

	key_buf[0] = (key_buf[0]<<1)|( GPIOA->IDR    &0X0001);	//WK_UP
	key_buf[1] = (key_buf[1]<<1)|((GPIOE->IDR>>4)&0X0001); 	//KEY0
	key_buf[2] = (key_buf[2]<<1)|((GPIOE->IDR>>3)&0X0001);	//KEY1
	key_buf[3] = (key_buf[3]<<1)|((GPIOE->IDR>>2)&0X0001);	//KEY2

	if(key_buf[0]==0XFFFF)
		key_sta[0] =0;
	else if(key_buf[0]==0X0000)
		key_sta[0] =1;
		
	for(i=1;i<4;i++)
	{
		if(key_buf[i]==0X0000)
			key_sta[i] =0;
		else if(key_buf[i]==0XFFFF)
			key_sta[i] =1;
	}

#if  Matrixkeyboard_ENR
	keybuf[keyout][0] = (keybuf[keyout][0] << 1) | KEY_IN_1;
	keybuf[keyout][1] = (keybuf[keyout][1] << 1) | KEY_IN_2;
	keybuf[keyout][2] = (keybuf[keyout][2] << 1) | KEY_IN_3;
	keybuf[keyout][3] = (keybuf[keyout][3] << 1) | KEY_IN_4;
	
	for(i=0;i<4;i++)
	{
		if((keybuf[keyout][i] & 0x0f) == 0x00)
			KeySta[keyout][i] = 0;
		else if((keybuf[keyout][i] & 0x0f) == 0x0f)
			KeySta[keyout][i] = 1;
	}
	
	keyout++;
	keyout &= 0X03;
	switch (keyout)          //根据索引，释放当前输出引脚，拉低下次的输出引脚
    {
        case 0: KEY_OUT_4 = 1; KEY_OUT_1 = 0; break;
        case 1: KEY_OUT_1 = 1; KEY_OUT_2 = 0; break;
        case 2: KEY_OUT_2 = 1; KEY_OUT_3 = 0; break;
        case 3: KEY_OUT_3 = 1; KEY_OUT_4 = 0; break;
        default: break;
    }
#endif
}

void key_action(u8 key)
{
	switch(key)
	{
		case WKUP_PERS:
			
			keyup_press();
			break;
		case KEY0_PRES:
		
			key0_press();
			break;
		case KEY1_PRES:
			
			key1_press();
			break;
		case KEY2_PERS:
			
			key2_press();
			break;
		default :
#if  Matrixkeyboard_ENR
			keyM_press(key);
#endif
			break;
	};
}

void key_moniter()
{
	u8 i;

#if  Matrixkeyboard_ENR	
	u8 j;
	for (i=0; i<4; i++)  						//循环检测4*4的矩阵按键
    {
        for (j=0; j<4; j++)
        {
            if (Keybackup[i][j] != KeySta[i][j])    //检测按键动作
            {
                if (Keybackup[i][j] == 0)           //按键按下时执行动作
                {
                    key_action(KeyCodeMap[i][j]); //调用按键动作函数
                }
                Keybackup[i][j] = KeySta[i][j];     //刷新前一次的备份值
            }
        }
    }
#endif

	for(i=0;i<4;i++)
	{
		if(key_sta[i] != key_bak[i])
		{
			if(key_bak[i]==0)
			{
				key_action(i);
			}
			key_bak[i] = key_sta[i];
		}
	}		
}


void TIM6_IRQHandler()
{
	key_scan();
	TIM6->SR = 0;
}


void keyup_press()
{
	

}

void key0_press()
{
	
}

void key1_press()
{
	
}
void key2_press()
{
	
}

#if  Matrixkeyboard_ENR


void keyM_press(u8 key)   //矩阵键盘被按下
{
	
	
}


#endif


