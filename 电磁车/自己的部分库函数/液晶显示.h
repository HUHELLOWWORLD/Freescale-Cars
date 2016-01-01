#ifndef _ZZOLED_H
#define _ZZOLED_H



#define byte unsigned char  //�Լ��ӵ�
#define word unsigned int   //�Լ��ӵ�
#define Dot_Size 3 //С�������λ


 extern byte longqiu96x64[768];
 void OLED_Pin_Init(void);    //Һ���˿ڵĳ�ʼ����ѡ��A12/14/16/17  
 void LCD_Init(void);   //!!!!!!!!!!�ܽų�ʼ��Ҫ��Һ����ʼ��֮ǰ!!!!!!!!!
 void LCD_CLS(void);
 void LCD_P6x8Str(byte x,byte y,byte ch[]);
 void LCD_P8x16Str(byte x,byte y,byte ch[]);
 void LCD_P14x16Str(byte x,byte y,byte ch[]);
 void LCD_Print(byte x, byte y, byte ch[]);
 void LCD_PutPixel(byte x,byte y);
 void LCD_Rectangle(byte x1,byte y1,byte x2,byte y2,byte gif);
 void Draw_LQLogo(void);
 void Draw_LibLogo(void);
 void Draw_Our_Picture(void);   //���Լ�ͼƬ�ĺ���
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

 
 
/****************Һ������ʹ�÷���*****************/
 /*
 ����Ҫ�ȳ�ʼ���˿ڣ�B8~B11���ֱ��Ӧ�Ķ˿ڿ�  LQ12864.h
 Ȼ���ǳ�ʼ��Һ��
 LCD_Init();
 
 ���ֳ����ʹ�÷�����
       LCD_P6x8Str(byte x,byte y,byte *p)  д�ַ�����6x8)
 ���磺LCD_P8x16Str(48,4,"OLED");
       LCD_P8x16Str(byte x,byte y,byte *p)  д�ַ�����8x16)
 ���磺LCD_P8x16Str(48,4,"OLED");
       LCD_P14x16Str(byte x,byte y,byte ch[])  ��������ַ�
 
       LCD_Print(byte x, byte y, byte ch[])  ��ʾ���ֺ��ַ�����ַ���
 ���磺LCD_Print(15,2,"���ܳ���ѡҺ��");
       LCD_Fill(byte bmp_data)      д��������Ļ��������������
      

        OLED_Write_Int(20,4,a);  ��ʾ���α���
        OLED_Write_Float(1,1,b);   ��ʾ�����ͱ���
 */