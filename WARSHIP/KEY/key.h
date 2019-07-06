#ifndef _KEY_H_
#define _KEY_H_
#include "Include_config.h"
#include "stm32f10x.h"
#include "sys.h"

#define Matrixkeyboard_ENR   1           //�Ƿ�֧�־������, 1: ֧��  0: ��֧�� 

//#define KEY0  PEin(4)
//#define KEY1  PEin(3)
//#define KEY2  PEin(2)
//#define WK_UP PAin(0)

#define WKUP_PERS 0
#define KEY0_PRES 1
#define KEY1_PRES 2
#define KEY2_PERS 3

#define KEY_IN_1    PFin(7)
#define KEY_IN_2    PFin(5)
#define KEY_IN_3    PFin(3)
#define KEY_IN_4    PFin(1)

#define KEY_OUT_1   PAout(1)
#define KEY_OUT_2   PCout(2)
#define KEY_OUT_3   PCout(0)
#define KEY_OUT_4   PFout(9)

#define KEY_IN1    PF(7)
#define KEY_IN2    PF(5)
#define KEY_IN3    PF(3)
#define KEY_IN4    PF(1)

#define KEY_OUT1   PA(1)
#define KEY_OUT2   PC(2)
#define KEY_OUT3   PC(0)
#define KEY_OUT4   PF(9)

void key_init(void);
void key_scan(void);
void key_action(u8 key);
void keyup_press(void);
void key0_press(void);
void key1_press(void);
void key2_press(void);
void keyM_press(u8 key);
void key_moniter(void);

void Key_Out_Init(u8 pin);
void Key_In_Init(u8 pin);

#endif
