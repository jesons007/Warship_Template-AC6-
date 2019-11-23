#include "Touch.h"
#include "Include_config.h"
#include "UI_Module.h"


//触摸按键数量
u8 Tp_Key_num = 13;

//触摸按键坐标区域映射表
u16 Tp_Key_Map[25][4] = 
{
	{193,723,286,799},      //key_0数字0 坐标区域{x1, y1, x2, y2}
	{97 ,643,190,720},      //key_1数字1 坐标区域{x1, y1, x2, y2}
	{193,643,286,720},      //key_2数字2 坐标区域{x1, y1, x2, y2}
	{289,643,382,720},      //key_3数字3 坐标区域{x1, y1, x2, y2}
	{97 ,563,190,640},      //key_4数字4 坐标区域{x1, y1, x2, y2}
	{193,563,286,640},      //key_5数字5 坐标区域{x1, y1, x2, y2}
	{289,563,382,640},      //key_6数字6 坐标区域{x1, y1, x2, y2}
	{97 ,483,190,560},      //key_7数字7 坐标区域{x1, y1, x2, y2}
	{193,483,286,560},      //key_8数字8 坐标区域{x1, y1, x2, y2}
	{289,483,382,560},      //key_9数字9 坐标区域{x1, y1, x2, y2}
	{289,723,382,799}, 		//.
	{97 ,723,190,799},  	//" "
	{385,723,478,799},   	//"Enter"

};

/*-------------------------------Tp_NumPad UI 部分--------------------------------*/


u16 Button_Fill_Table[25][2] = 
{
    {234,749},          //数字0
    {137,669},          //数字1
    {233,669},          //数字2
    {329,669},          //数字3
    {137,589},          //数字4
    {233,589},          //数字5
    {329,589},          //数字6
    {137,509},          //数字7
    {233,509},          //数字8
    {329,509},          //数字9
    {332,749},          //.
    {97 ,723},          //" "
    {385,723},          //"Enter"
};


void Tp_NumPad_Init(u8 mode)
{
    u8 i;
    u16 LineColor = 0x8410;
    LineColor = 0xc618;


    if(mode==1)
    {
        LCD_Set_Window(0,400,479,799,WHITE);   //包含边界
        LCD_Draw_Line (0,400,479,400,BLACK);   //上边框
        LCD_Draw_Line (0,400,0,799,BLACK);     //左边框
        LCD_Draw_Line (479,400,479,799,BLACK); //右边框

        LCD_Draw_Line (1,482,478,482,LineColor);
        LCD_Draw_Line (1,481,478,481,LineColor);          //H_Line 1

        LCD_Draw_Line (1,562,478,562,LineColor);  
        LCD_Draw_Line (1,561,478,561,LineColor);          //H_Line 2

        LCD_Draw_Line (1,642,478,642,LineColor);  
        LCD_Draw_Line (1,641,478,641,LineColor);          //H_Line 3

        LCD_Draw_Line (1,722,478,722,LineColor);  
        LCD_Draw_Line (1,721,478,721,LineColor);          //H_Line 4              横线


        LCD_Draw_Line (95, 401,95, 799,LineColor);
        LCD_Draw_Line (96, 401,96, 799,LineColor);        //V_Line 1
         
        LCD_Draw_Line (191,401,191,799,LineColor);
        LCD_Draw_Line (192,401,192,799,LineColor);        //V_Line 2
        
        LCD_Draw_Line (287,401,287,799,LineColor);
        LCD_Draw_Line (288,401,288,799,LineColor);        //V_Line 3
        
        LCD_Draw_Line (383,401,383,799,LineColor);
        LCD_Draw_Line (384,401,384,799,LineColor);        //V_Line 4               竖线

        //按钮填充,每个按钮占据94x78 = 宽x高 pix
        for(i=0;i<10;i++)
        {
            LCD_Show_OneChar(Button_Fill_Table[i][0],Button_Fill_Table[i][1],i+'0',BLACK,WHITE);  //i
        }
        LCD_Show_OneChar(Button_Fill_Table[10][0],Button_Fill_Table[10][1],'.',BLACK,WHITE); //小数点
        
        LCD_Draw_9478BMP(97,723,gImage_space,BLACK,WHITE);  //空格符号
        LCD_Draw_9478BMP(385,723,gImage_enter,BLACK,WHITE); //回车符号

    }
    else
    {
        LCD_Set_Window(0,400,479,799,BKOR);
    }
    
	
}




/*-------------------------------Tp_NumPad Event 部分--------------------------------*/

u8 press_enr_1 = 1;
u8 press_enr_2 = 1;

void Tp_Key_pressed_out(u8 key)
{
    if(key>=0&&key<=9)
    {
        LCD_Set_Window(Tp_Key_Map[key][0],Tp_Key_Map[key][1],Tp_Key_Map[key][2],Tp_Key_Map[key][3],WHITE);
        LCD_Show_OneChar(Button_Fill_Table[key][0],Button_Fill_Table[key][1],key+'0',BLACK,WHITE);
        printf("%d",key);
    }
    else
    {
        LCD_Set_Window(Tp_Key_Map[key][0],Tp_Key_Map[key][1],Tp_Key_Map[key][2],Tp_Key_Map[key][3],WHITE);
        switch (key)
        {
            case 10:
                LCD_Show_OneChar(Button_Fill_Table[10][0],Button_Fill_Table[10][1],'.',BLACK,WHITE); //小数点
                printf(".");
                break;
            case 11:
                LCD_Draw_9478BMP(97,723,gImage_space,BLACK,WHITE);  //空格符号
                printf(" ");
                break;
            case 12:
                LCD_Draw_9478BMP(385,723,gImage_enter,BLACK,WHITE); //回车符号
                printf("\n");
                break;
            default:
                break;
        }
    }
    
}


void Tp_Key_just_pressed(u8 key)
{
    if(key>=0&&key<=9)
    {
        LCD_Set_Window(Tp_Key_Map[key][0],Tp_Key_Map[key][1],Tp_Key_Map[key][2],Tp_Key_Map[key][3],GREEN);
        LCD_Show_OneChar(Button_Fill_Table[key][0],Button_Fill_Table[key][1],key+'0',BLACK,GREEN);
    }
    else
    {
        LCD_Set_Window(Tp_Key_Map[key][0],Tp_Key_Map[key][1],Tp_Key_Map[key][2],Tp_Key_Map[key][3],GREEN);
        switch (key)
        {
            case 10:
                LCD_Show_OneChar(Button_Fill_Table[10][0],Button_Fill_Table[10][1],'.',BLACK,GREEN); //小数点

                break;
            case 11:
                LCD_Draw_9478BMP(97,723,gImage_space,BLACK,GREEN);  //空格符号

                break;
            case 12:
                LCD_Draw_9478BMP(385,723,gImage_enter,BLACK,GREEN); //回车符号

                break;
            default:
                break;
        }
        
    }
    
}
