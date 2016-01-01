#include "include.h"


/*********初始化*********/
void speed_PWM_init(void)
{
  FTM_PWM_init(FTM0,CH0,16000,0);
  FTM_PWM_init(FTM0,CH1,16000,0);
  gpio_init(PORTA,0,GPO,1);
  gpio_init(PORTA,2,GPI,1);
  gpio_init(PORTB,21,GPO,1);
  gpio_init(PORTB,19,GPI,1);
}


/***********速度控制*********/

int pulse=0;   //编码器采集的速度
int speed=29;   //目标速度
int speed_turn=24;
int a_speed;
int temp_speed=0;

float speed_p=1300;//350;//300;//1300;
float speed_i=300;//35;//0.5;//300;
float speed_d=10;

int s_error[3]={0};
int start_car=0;
int change_PWM=0;

int s_PWM=0;
int s_PWM_forward=0;
int s_PWM_back=0;

int delay_2S_mark=0;
int stop_car_time=0;
int stop_car=0;
int time_back=0;
int e_speed_error=0;
int turnner_old[150]={0};
int read_turnner;
int line_or_turn=0;
int line_mark=0;

void speed_control(void)
{  
  if(PTA2_IN == 0)
  {
    start_car=1;
    stop_car_time++;
    if(stop_car_time>2000)
    {
      stop_car_time=2002;
      if(PTB19_IN == 0)
      {
        a_speed=0;
        stop_car=1;
      }
    }
   /* for(read_turnner=0;read_turnner<149;read_turnner++)
    {
      turnner_old[read_turnner]=turnner_old[read_turnner+1];
    }
    turnner_old[149]=turnner;
    for(read_turnner=0;read_turnner<150;read_turnner++)
    {
      if(turnner_old[read_turnner]>400 && turnner_old[read_turnner]<500)
        line_mark=1;
      else
      {
        line_mark=0;
        break;
      }
    }
    if(line_mark == 1)
      a_speed=speed;
    else if(line_mark == 0)
      a_speed=speed_turn;*/
    if(turnner>430 && turnner<470)
      a_speed=speed;
    else
      a_speed=speed_turn;
    temp_speed=a_speed;  //控制a_speed的值
  }
  else
  {
    start_car=0;
    a_speed=speed;
    stop_car_time=0;
    temp_speed=0;
    delay_2S_mark=1;
    s_PWM=0;
    stop_car=0;
    time_back=0;
  }
  if(delay_2S_mark == 1 && temp_speed != 0)
  {
    delay_own(5000);   ///////////////////////////////////////////
    delay_2S_mark=0;
  }
  
if(stop_car == 0)
{
  s_error[2]=s_error[1];
  s_error[1]=s_error[0];
  s_error[0]=temp_speed-pulse;
  if(delay_2S_mark==0)
  {
    change_PWM=(int)(speed_p*(s_error[0]-s_error[1])+speed_i*s_error[0]+speed_d*(s_error[0]-2*s_error[1]+s_error[2]));  
    s_PWM+=change_PWM;
  }
  if(stop_car == 1)
    s_PWM=0;
  
 
  
  if(s_PWM>10000)
  {
    s_PWM_forward=10000;
    s_PWM=10000;
    s_PWM_back=0;
  }
  else if(s_PWM>=0 && s_PWM<10000)
  {
    s_PWM_forward=s_PWM;
    s_PWM_back=0;
  }
  else if(s_PWM<0 && s_PWM>-10000)
  {
    s_PWM_forward=0;
    s_PWM_back=-3*s_PWM;
    if(s_PWM_back>10000)
      s_PWM_back=10000;
  }
  else if(s_PWM<-10000)
  {
    s_PWM_forward=0;
    s_PWM=-10000;
    s_PWM_back=10000;
  }
  /*
  if(a_speed == 0 && pulse<5)
  {
    stop_car=1;
    s_PWM_forward=0;
    s_PWM_back=0;
  }*/
 
  FTM_PWM_Duty(FTM0,CH1,s_PWM_forward);
  FTM_PWM_Duty(FTM0,CH0,s_PWM_back);
}
else
{
  time_back++;
  if(time_back<(8*speed))
  {
     FTM_PWM_Duty(FTM0,CH1,0);
     FTM_PWM_Duty(FTM0,CH0,10000);
  }
  else 
  {
    time_back=10*speed+10;
    FTM_PWM_Duty(FTM0,CH1,0);
    FTM_PWM_Duty(FTM0,CH0,0);
  }
}

}