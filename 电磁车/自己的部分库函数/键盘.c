#include "include.h"


void delay_own(int limit_time_i)
{
  int time_i=0;
  int time_j=0;
  for(time_i=0;time_i<limit_time_i;time_i++)
  {
    for(time_j=0;time_j<5000;time_j++)
    {
      ;
    }
  }
}

void key_pin_init(void)
{
  gpio_init(PORTB,0,GPI,1);
  gpio_init(PORTB,2,GPI,1);
  gpio_init(PORTB,4,GPI,1);
  gpio_init(PORTB,6,GPI,1);
  gpio_init(PORTB,8,GPO,1);
  gpio_init(PORTB,10,GPO,1);
  gpio_init(PORTB,16,GPO,1);
  gpio_init(PORTB,18,GPO,1);
}


int delay_time_key=30;  //按键延时
void give_high_level(void)
{
  gpio_set(PORTB,0,1);
  gpio_set(PORTB,2,1);
  gpio_set(PORTB,4,1); 
  gpio_set(PORTB,6,1);
  gpio_set(PORTB,8,1);
  gpio_set(PORTB,10,1);
  gpio_set(PORTB,16,1);
  gpio_set(PORTB,18,1);
  delay_own(delay_time_key);
}


/**********按键检测（用于内部）*********/

int check_key_in(void)
{


  give_high_level();  //扫描第一行
  cross1=0;
  delay_own(10);
  if(row1==0)
    return(1);
  else if(row2==0)
    return(2);
  else if(row3==0)
    return(3);
  else if(row4==0)
    return(30);
  
  give_high_level();    //扫描第二行
  cross2=0;
  delay_own(10);
  if(row1==0)
    return(4);
  else if(row2==0)
    return(5);
  else if(row3==0)
    return(6);
  else if(row4==0)
    return(31);
  
  give_high_level();    //扫描第三行
  cross3=0;
  delay_own(10);
  if(row1==0)
    return(7);
  else if(row2==0)
    return(8);
  else if(row3==0)
    return(9);
  else if(row4==0)
    return(32);
  
  give_high_level();    //扫描第四行
  cross4=0;
  delay_own(10);
  if(row1==0)
    return(33);
  else if(row2==0)
    return(0);
  else if(row3==0)
    return(34);
  else if(row4==0)
    return(35); 
  return(-1);
}

/************检测上升沿*************/
int check_rise=1;//当等于1时表示检测到了上升沿
int old_key=-1;
int press_key;
int key_mark=0;
int check_key(void)
{ 
  press_key=check_key_in();
  if((press_key != old_key) && (key_mark == -1))
    check_rise=1;
  else
    check_rise=0; 
  old_key=press_key;
  
  if(check_rise == 1)
  {
    key_mark=press_key;
  }
  else
  {
    key_mark=-1;
  }
  return(key_mark);

}