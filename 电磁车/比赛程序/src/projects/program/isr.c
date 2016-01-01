#include "common.h"
#include "include.h"

volatile u32 LPT_INT_count=0;
void LPT_Handler(void)
{
  LPTMR0_CSR|=LPTMR_CSR_TCF_MASK;
  LPT_INT_count++;
}
  

int read_speed=0;

void PIT0_IRQHandler(void)
{
  PIT_Flag_Clear(PIT0);  //���жϱ�־λ
  //if(read_speed == 5)
  //{
    pulse = LPTMR0_CNR;    //�����������������ֵ
    lptmr_counter_clean(); //����������������ֵ 
   // read_speed=0;
  //}
  read_speed++;
  speed_control(); 
  turn_control();

}
