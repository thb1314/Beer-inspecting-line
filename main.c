/******************************************************************* 
 *  Copyright(c) 2016 THB-CCUT  
 *  All rights reserved. 
 *   
 *  �ļ�����: main.c
 *  ��Ҫ����: �������ļ�
 *   
 *  ��������: 2016-11-06
 *  ����: THB
 *  ˵��: 
 *   
 *  �޸�����: 
 *  ����: 
 *  ˵��: 
 ******************************************************************/
#include <STC15F2K60S2.H>
#include "main.h"
#include "myfunc.h"
#include "myport.h"
#include "mytype.h"
#include "serial_cmd.h"
#include "exit.h"
#include "event.h"
#include "tim.h"
#include "uart.h"
#include "task.h"
#include "delay.h"





void main()
{
	SystemInit();
	
	P0M1 &= ~0x01;
	P0M1 |= 0x01;
	
	P6 = 0xFF;
	P7 = 0xFF;
	
	
	while(1)
	{
		//��ⰴ��
		CheckBtn();
		//�����¼�״̬
		UpdateEvent();
		//�����¼�
		HandleEvent();



	}
}



// ϵͳ��ʼ������
void SystemInit(void)
{

	//��ʼ��IO��
	InitPort();
	//��ʼ���ⲿ�ж�
	InitExit();
	//��ʼ����ʱ��
	InitTimer0();
	//��ʼ������
	#ifdef UART1
	Uart1Init();
	#endif
	#ifdef UART2
	Uart2Init();
	#endif
	//�������ж�
	SET_PORT(EA);
	
}

