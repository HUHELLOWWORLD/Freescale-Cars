


#define cross1 PTB8_OUT
#define cross2 PTB10_OUT
#define cross3 PTB16_OUT
#define cross4 PTB18_OUT
#define row1 PTB0_IN
#define row2 PTB2_IN
#define row3 PTB4_IN
#define row4 PTB6_IN


extern void delay_own(int limit_time_i);
extern void key_pin_init(void);
int check_key(void);
