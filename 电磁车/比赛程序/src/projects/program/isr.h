/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 * 文件名       ：isr.h
 * 描述         ：重新宏定义中断号，重映射中断向量表里的中断函数地址，
 *                使其指向我们所定义的中断服务函数。声明中断服务函数
 *                警告：只能在"vectors.c"包含，而且必须在"vectors.h"包含的后面！！！
 *
 * 实验平台     ：野火kinetis开发板
 * 库版本       ：
 * 嵌入系统     ：
 *
 * 作者         ：野火嵌入式开发工作室
 * 淘宝店       ：http://firestm32.taobao.com
 * 技术支持论坛 ：http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/



#ifndef __ISR_H
#define __ISR_H 1

#include  "include.h"

#undef VECTOR_101
#define VECTOR_101 LPT_Handler

#undef VECTOR_084
#define VECTOR_084 PIT0_IRQHandler

extern void LPT_Handler(void);
extern void PIT0_IRQHandler(void);
/*
extern int read_left[1000];
extern int read_right[1000];
extern int read_middle[1000];
extern int read_middle_new[1000];*/


#endif  //__ISR_H

/* End of "isr.h" */
