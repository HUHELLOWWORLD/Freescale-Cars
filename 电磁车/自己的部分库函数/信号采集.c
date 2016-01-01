#include "include.h"

/******AD�ڳ�ʼ��*******/
void AD_Init(void)
{
  adc_init (ADC1,SE4a);//E0��  ��
  adc_start (ADC1,SE4a,ADC_16bit);
  adc_init (ADC1,SE5a);//E1��   ��
  adc_start (ADC1,SE5a,ADC_16bit);
  adc_init (ADC1,SE6a);//E2��   ��
  adc_start (ADC1,SE6a,ADC_16bit);
  adc_init (ADC1,SE7a);//E3��    ��ǰ
  adc_start (ADC1,SE7a,ADC_16bit);
}


/***********����ڳ�ʼ��*********/
void turn_PWM_init(void)
{
  FTM_PWM_init(FTM1,CH0,60,0);  //ʹ��A8��
}


/***********�źŲɼ�************/

int temp_left;
int temp_right;
int temp_middle;
int temp_middle_new;

void get_signal(void)
{
  temp_left=(int)(ad_ave(ADC1,SE5a,ADC_16bit,40)/100)-15; 
  temp_right=(int)(ad_ave(ADC1,SE6a,ADC_16bit,40)/100)-15;
  temp_middle=(int)(ad_ave(ADC1,SE4a,ADC_16bit,40)/100)-15;
  temp_middle_new=(int)(ad_ave(ADC1,SE7a,ADC_16bit,40)/100)-55;
  if(temp_left<0)
    temp_left=0;
  if(temp_right<0)
    temp_right=0;
  if(temp_middle<0)
    temp_middle=0;
  if(temp_middle_new<0)
    temp_middle_new=0;
}


/*********�źŴ���**********/

int left[3]={0,0,0};
int right[3]={0,0,0};
int middle[3]={0,0,0};
int middle_new[3]={0};
int get_max_time=0;
void deal_signal(void)
{
  get_signal();
  if((temp_left-left[0])<100 && (temp_left-left[0])>-100)
    left[0]=temp_left;         //[0]Ϊ�ɼ����������ź�
  if((temp_right-right[0])<100 && (temp_right-right[0])>-100)
    right[0]=temp_right;
  if((temp_middle-middle[0])<100 && (temp_middle-middle[0])>-100)
    middle[0]=temp_middle;
  middle_new[0]=temp_middle_new;
  if(get_max_time<600)        //[2]Ϊ�ɼ����������źŵ����ֵ��ͨ��������ɼ������źűȽϵõ�
  {
    if(left[2]<left[0])
      left[2]=left[0];
    if(right[2]<right[0])
      right[2]=right[0];
    if(middle[2]<middle[0])
      middle[2]=middle[0];
    if(middle_new[2]<middle_new[0])
      middle_new[2]=middle_new[0];
    get_max_time++;    
  }
  left[1]=(int)(left[0]*550/left[2]);//[1]Ϊ���յõ��ı�ֵ�źţ�Ϊ����550�ģ�[0]/[2]��
  right[1]=(int)(right[0]*550/right[2]);
  middle[1]=(int)(middle[0]*550/middle[2]);
  middle_new[1]=(int)(middle_new[0]*550/middle_new[2]);

}

float error=0;
float e_error=0;
float old_error=0;
float error2=0;   //�м��µ�����
float error1[3]={0};  //��һ���
float error3=0;   // �м������
float left_or_right=0.0;

int turn_p=50;
int temp_turn_p=0;
int turn_d=1200;
int turnner=450;
int turnner_max=550;//1235;
int turnner_min=350;//958;
float e_error_max=0;

float limit_e_error=2.0;


float k1[3]={1.0,0.0,4.0};   //middle_new[0]<10ʱ��ϵ��
float k2[3]={2.3,3.2,4.5};
void turn_control(void)
{
  deal_signal();
  
  if(middle[0]>40)
  {
    
    if(left[0]>right[0])
      left_or_right=1.0;
    if(right[0]>left[0])
      left_or_right=-1.0;
  }
  if(middle[0]>20)
  {
    error2=(float)(middle[2]-middle[0]+5)/middle[2];
    if(error2<0)
      error2=0;
  error1[0]=(float)(left[0]-right[0])/middle[0];
  }
  
  error3=error2*left_or_right*k1[0]+error1[0]*k1[1];
  
  if(error3>0 && error3<0.7)
    error=k2[0]*error3; 
  else if(error3<=0 && error3>-0.7)
    error=k2[0]*error3;
  else if(error3>=0.7 && error3<0.8)
    error=k2[1]*(error3-0.7)+k2[0]*0.7; 
  else if(error3>=0.8 )
    error=k2[2]*(error3-0.8)+k2[1]*(0.8-0.7)+k2[0]*0.7;  
  else if(error3>-0.8 && error3<=-0.7)
    error=k2[1]*(error3+0.7)-k2[0]*0.7;
  else if(error3<=-0.8)
    error=k2[2]*(error3+0.8)+k2[1]*(-0.8+0.7)-k2[0]*0.7;

   e_error=error-old_error;
  if(e_error>e_error_max)
    e_error_max=e_error;
 
  
  if(e_error>limit_e_error || e_error<-limit_e_error)   //������
  {
    error=old_error;
    e_error=0;
  }
  if(middle[0] == 0 && left[0] == 0 && right[0] == 0)
    error=old_error;
  
  old_error=error;
  temp_turn_p=turn_p;
  turnner=(int)(450+temp_turn_p*error+turn_d*e_error);

  if(turnner>=turnner_max)
    turnner=turnner_max;
  else if(turnner<=turnner_min)
    turnner=turnner_min;
  FTM_PWM_Duty(FTM1,CH0,turnner);
}