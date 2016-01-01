
#include "include.h"


int key=-1;
int sum=0;    //其他子程序可以使用该值
void sum_key(void)
{
  if(key>=0 && key<=9)
    sum=sum*10+key;
}

/***********变量赋值********/
int temp_p=0;
int temp_i=0;
int temp_d=0;
    
void fuzhi(void)
{
  if(key == 30)
  {
    temp_p=1;
    temp_i=0;
    temp_d=0;
  }
  else if(key == 31)
  {
    temp_i=1;
    temp_p=0;
    temp_d=0;
  }
  else if(key == 32)
  {
    temp_d=1;
    temp_p=0;
    temp_i=0;
  }
  
  if(key == 35)
  {
    
    if(temp_p == 1)
    {
      if(page == 0)
        speed_p=sum/10.0;
      else if(page == 1)
        speed=sum;
      else if(page == 4)
        turn_p=sum;
    }
    else if(temp_i == 1)
    {
      if(page == 0)
         speed_i=sum/10.0;
    }
    else if(temp_d == 1)
    {
      if(page == 0)
         speed_d=sum/10.0;
      else if(page == 4)
        turn_d=sum;
    }
    temp_p=0;
    temp_i=0;
    temp_d=0;
    sum=0;
    LCD_Init();
  }
  /*
  if(page == 5)
  {
    if(key == 30)
      num+=10;
    else if(key == 31)
      num-=10;
    else if(key == 32)
      num++;
    else if(key == 35)
      num--;
  }*/
  }
    
