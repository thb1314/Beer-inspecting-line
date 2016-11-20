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
#include "uart.h"

//��ʱ������ (ms)
#define T0_MS (1)


#define T0MS (65536-FOSC/1000*T0_MS)





#define START_TIMER0() SET_PORT(TR0)
#define COLSE_TIMER0() CLR_PORT(TR0)
//��ʼ����ʱ�� �������ȼ�
void InitTimer0(void);
void tim0_isr(void);

#ifdef UART1


#define T3_MS (1)
#define T3MS (65536 - (FOSC/4/UART_BAUDRATE))
//#define T3MS  (65536-FOSC/1000*T3_MS)
//��ʼ����ʱ��3
void InitTimer3(void);

#define START_TIMER3() (T4T3M |= 0x08)
#define CLOSE_TIMER3() (T4T3M &= ~0x08)
#define IS_START_TIMER3() (T4T3M &= 0x08)

#endif


#ifdef UART2


#define T4_MS (1)
#define T4MS (65536 - (FOSC/4/UART_BAUDRATE))
//#define T4MS  (65536-FOSC/1000*T3_MS)

//��ʼ����ʱ��4
void InitTimer4(void);

#define START_TIMER4() (T4T3M |= 0x80)
#define CLOSE_TIMER4() (T4T3M &= ~0x80)
#define IS_START_TIMER4() (T4T3M &= 0x80)

#endif

// һЩ��������ı�־λ
extern bit is_start_check_close_btn;


#endif
