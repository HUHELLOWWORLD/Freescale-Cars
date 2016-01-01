#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

/*
 * Include 用户自定义的头文件
 */
#include  "isr.h"
#include  "PIT.h"
#include  "gpio.h"       //IO口操作
#include  "LED.H"       //流水灯
#include  "exti.h"       //EXTI外部GPIO中断
#include  "uart.h"      //串口
#include  "lptmr.h"     //低功耗定时器(延时)
#include  "adc.h"
#include  "FTM.h"

#include  "液晶显示.h"
#include  "无线模块.h"
#include  "键盘.h"
#include  "赋值.h"
#include  "速度控制.h"
#include  "换页.h"
#include  "信号采集.h"

#endif  //__INCLUDE_H__
