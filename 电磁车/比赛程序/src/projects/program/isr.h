/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��isr.h
 * ����         �����º궨���жϺţ���ӳ���ж�����������жϺ�����ַ��
 *                ʹ��ָ��������������жϷ������������жϷ�����
 *                ���棺ֻ����"vectors.c"���������ұ�����"vectors.h"�����ĺ��棡����
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��Ұ��Ƕ��ʽ����������
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
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
