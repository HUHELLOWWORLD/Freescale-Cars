#ifndef _ZZOLED_H
#define _ZZOLED_H



#define byte unsigned char  //自己加的
#define word unsigned int   //自己加的
#define Dot_Size 3 //小数点后三位


 extern byte longqiu96x64[768];
 void OLED_Pin_Init(void);    //液晶端口的初始化，选用A12/14/16/17  
 void LCD_Init(void);   //!!!!!!!!!!管脚初始化要在液晶初始化之前!!!!!!!!!
 void LCD_CLS(void);
 void LCD_P6x8Str(byte x,byte y,byte ch[]);
 void LCD_P8x16Str(byte x,byte y,byte ch[]);
 void LCD_P14x16Str(byte x,byte y,byte ch[]);
 void LCD_Print(byte x, byte y, byte ch[]);
 void LCD_PutPixel(byte x,byte y);
 void LCD_Rectangle(byte x1,byte y1,byte x2,byte y2,byte gif);
 void Draw_LQLogo(void);
 void Draw_LibLogo(void);
 void Draw_Our_Picture(void);   //画自己图片的函数
 void Draw_xiaohui(void);
 void Draw_School_name(void);
 void Draw_BMP(byte x0,byte y0,byte x1,byte y1,byte bmp[]); 
 void LCD_Fill(byte dat);
 signed int Int_To_String(signed long Int_Num,signed char String[]);
 signed int Float_To_String(float Float_Num,signed char String[]);
 void OLED_Write_Int(unsigned char x,unsigned char y,signed int Number);
 void OLED_Write_Float(unsigned char x,unsigned char y,float Number);
 
 
 void OLED_Write_Command(unsigned char Cmd);
 void OLED_Set_Pos(unsigned char x,unsigned char y);
 void List_Move(signed char New_Data);
 void List_Paint(void);
 void Paint_List(float New_Data,float Paint_Ave,float Paint_Margin);
#endif

 
 
/****************液晶程序使用方法*****************/
 /*
 首先要先初始化端口：B8~B11，分别对应的端口看  LQ12864.h
 然后是初始化液晶
 LCD_Init();
 
 各种程序的使用方法：
       LCD_P6x8Str(byte x,byte y,byte *p)  写字符串（6x8)
 例如：LCD_P8x16Str(48,4,"OLED");
       LCD_P8x16Str(byte x,byte y,byte *p)  写字符串（8x16)
 例如：LCD_P8x16Str(48,4,"OLED");
       LCD_P14x16Str(byte x,byte y,byte ch[])  输出汉字字符
 
       LCD_Print(byte x, byte y, byte ch[])  显示汉字和字符混合字符串
 例如：LCD_Print(15,2,"智能车首选液晶");
       LCD_Fill(byte bmp_data)      写满整个屏幕（可用于清屏）
      

        OLED_Write_Int(20,4,a);  显示整形变量
        OLED_Write_Float(1,1,b);   显示浮点型变量
 */