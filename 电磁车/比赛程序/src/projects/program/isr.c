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
  PIT_Flag_Clear(PIT0);  //清中断标志位
  //if(read_speed == 5)
  //{
    pulse = LPTMR0_CNR;    //保存脉冲计数器计算值
    lptmr_counter_clean(); //清空脉冲计数器计算值 
   // read_speed=0;
  //}
  read_speed++;
  speed_control(); 
  turn_control();

}
