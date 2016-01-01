#include "common.h"
#include "include.h"

#define INT_COUNT 50000

void main()
{

  DisableInterrupts;
  key_pin_init();
  OLED_Pin_Init();
  LCD_Init();
  speed_PWM_init();
  AD_Init();
  turn_PWM_init();
  //nRF2401_IO_Init();
 // Send_Init();
  lptmr_counter_init(LPT0_ALT2,INT_COUNT,2,LPT_Rising);
  pit_init_ms(PIT0,2);
  EnableInterrupts;
  for(;;)
  {   
    key=check_key();     //��仰д�ڿ�ͷ     
    page_change();
    sum_key();           
    fuzhi();      //��仰д�����
   // Send_Data();  
  }
  
}
