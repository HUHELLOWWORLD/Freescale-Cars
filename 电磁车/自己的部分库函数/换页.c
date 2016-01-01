#include "include.h"

int page_change_mark=0;
int page=2;
int page_max=7;   //最大页数

void page_change(void)
{
  if(key == 33)
  {
    page--;
    page_change_mark=1;
    if(page<0)
      page=page_max;
  }
  else if(key == 34)
  {
    page++;
    page_change_mark=1;
    if(page>page_max)
      page=0;
  }
  
  if(page_change_mark == 1)
  {
    LCD_Init();
    page_change_mark=0;
  }
  
  if(page == 0)
  {
    OLED_Write_Int(80,6,sum);   
    LCD_Print(2,2,"P:");
    OLED_Write_Float(20,2,speed_p);
    LCD_Print(2,4,"I:");
    OLED_Write_Float(20,4,speed_i);
    LCD_Print(2,6,"D:");
    OLED_Write_Float(20,6,speed_d);
  }
  else if(page == 1)
  {
    OLED_Write_Int(2,0,speed);
    OLED_Write_Int(34,0,speed_turn);
    OLED_Write_Int(64,0,pulse);
    OLED_Write_Int(110,0,start_car);
    Paint_List(pulse,speed,20);
    if(key==1)
      speed--;
    else if(key == 2)
      speed++;
    else if(key ==4)
      speed_turn--;
    else if(key == 5)
      speed_turn++;
 
  }
  else if(page == 2)
  {
    LCD_Print(50,0,"舵机");
    OLED_Write_Float(80,0,e_error_max);
    OLED_Write_Float(2,0,limit_e_error);
    LCD_Print(2,2,"左:");
    LCD_Print(28,2,"   ");
    OLED_Write_Int(28,2,left[0]);
    LCD_Print(66,2,"右:");
    LCD_Print(92,2,"   ");
    OLED_Write_Int(92,2,right[0]);
    LCD_Print(2,4,"中:");
    LCD_Print(28,4,"   ");
    OLED_Write_Int(28,4,middle[0]);
    LCD_Print(92,4,"   ");
    OLED_Write_Int(92,4,middle_new[0]);
    OLED_Write_Int(2,6,turnner);
    OLED_Write_Float(66,6,error);
    if(key ==1)
      limit_e_error=limit_e_error-0.1;
    else if(key == 2)
      limit_e_error=limit_e_error+0.1;
  }
  
  else if(page == 3)
  {
    LCD_Print(2,2,"error1:");
    OLED_Write_Float(64,2,error1[0]);
    LCD_Print(2,4,"error2:");
    OLED_Write_Float(64,4,error2);
    LCD_Print(2,6,"error3:");
    OLED_Write_Float(64,6,error3);
  }
  else if(page == 4)
  {
    LCD_Print(50,0,"舵机");
    LCD_Print(2,2,"P:");
    OLED_Write_Int(28,2,turn_p);
    LCD_Print(2,4,"D:");
    OLED_Write_Int(28,4,turn_d);
    OLED_Write_Int(80,6,sum);
  }
  else if(page == 5)
  {
    if(key==4)
      turnner_max--;
    else if(key==5)
      turnner_max++;
    else if(key==7)
      turnner_min--;
    else if(key==8)
      turnner_min++;
    LCD_Print(2,0,"turnner_max:");
    OLED_Write_Int(2,2,turnner_max);
    LCD_Print(2,4,"turnner_min:");
    OLED_Write_Int(2,6,turnner_min);
  }
 else if(page == 6)
 {
   LCD_Print(2,2,"k21:");
   OLED_Write_Float(64,2,k2[0]);
   LCD_Print(2,4,"k22:");
   OLED_Write_Float(64,4,k2[1]);
   LCD_Print(2,6,"k23:");    
   OLED_Write_Float(64,6,k2[2]);
   if(key == 1)
     k2[0]=k2[0]-0.1;
   else if(key == 2)
     k2[0]=k2[0]+0.1;
   else if(key == 4)
     k2[1]=k2[1]-0.1;
   else if(key == 5)
     k2[1]=k2[1]+0.1;
   else if(key == 7)
     k2[2]=k2[2]-0.1; 
   else if(key == 8)
     k2[2]=k2[2]+0.1;
 }
 else if(page == 7)
 {
   LCD_Print(2,2,"k11:");
   OLED_Write_Float(64,2,k1[0]);
   LCD_Print(2,4,"k12:");
   OLED_Write_Float(64,4,k1[1]);
   if(key == 1)
     k1[0]=k1[0]-0.1;
   else if(key == 2)
     k1[0]=k1[0]+0.1;
   else if(key == 4)
     k1[1]=k1[1]-0.1;
   else if(key == 5)
     k1[1]=k1[1]+0.1;
 }
}