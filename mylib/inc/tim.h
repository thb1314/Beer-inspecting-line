/******************************************************************* 
 *  Copyright(c) 2016 THB-CCUT  
 *  All rights reserved. 
 *   
 *  �ļ�����: tim.h
 *  ��Ҫ����: ��ʱ��������
 *   
 *  ��������: 2016-11-08
 *  ����: THB
 *  ˵��: ��ʼ����ʱ������ʱ����غ���
 *   
 *  �޸�����: 
 *  ����: 
 *  ˵��: 
 ******************************************************************/ 

 
#ifndef __TIM_H_
#define __TIM_H_
#include "myfosc.h"
#include "myfunc.h"

//��ʱ������ (ms)
#define T0_US (1)
#define T0MS (65536-FOSC/12/1000*T0_US)

#define START_TIMER0() SET_PORT(TR0)
#define COLSE_TIMER0() CLR_PORT(TR0)
//��ʼ����ʱ�� �������ȼ�
void InitTimer0(void);
void tim0_isr(void);



// һЩ��������ı�־λ
extern bit is_start_check_close_btn;
#endif
