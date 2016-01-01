


#ifndef WUXIAN_H_
#define WUXIAN_H_

#include "gpio.h"



/*---------------------*IO口初始化、、128模板*---------------------*/
/*
#define	nRF_CE    PTM_PTM5 //1
#define	nRF_CSN   PTM_PTM4 //1
#define	nRF_SCK   PTM_PTM3 //1
#define nRF_MOSI  PTM_PTM2 //1
#define nRF_MISO  PTM_PTM1 //0
#define nRF_IRQ   PTM_PTM0 //0


#define nRF2401_IO_Init()   {DDRM=0x3c;}
// CE C10;SCK C8;MISO C6;CSN C4;MOSI C7;IRQ C9;*/

#define	nRF_CE    PTB1_OUT //1
#define	nRF_CSN   PTB7_OUT //1
#define	nRF_SCK   PTB3_OUT //1
#define nRF_MOSI  PTB9_OUT //1
#define nRF_MISO  PTB5_IN //
#define nRF_IRQ   PTB11_IN //0


void nRF2401_IO_Init(void);
void Send_Init(void);
void Send_Data(void);


#endif
