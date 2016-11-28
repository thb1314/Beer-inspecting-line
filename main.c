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


//����һ������ ��⴫����4�Ƿ�����������
static u8 idata Sensor4TrigTime = 0;
static u8 idata Sensor5TrigTime = 0;


volatile Task idata TskIsSensor4_5_TrigOk;
void TskIsSensor4_5_TrigOkCallBack(void*);
bit is_serious_block = 0;

#define SENSOR4TRIGTIME_MAX 50
#define SENSOR5TRIGTIME_MAX 50

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
	
	

	TskIsSensor4_5_TrigOk.timer = 100;
	TskIsSensor4_5_TrigOk.type = TIME_TASK;
	TskIsSensor4_5_TrigOk.isstart = 1;
	TskIsSensor4_5_TrigOk.function = TskIsSensor4_5_TrigOkCallBack; 
	TaskInit(&TskIsSensor4_5_TrigOk);
	
}

void TskIsSensor4_5_TrigOkCallBack(void* ptr)
{
	Task* mytask = (Task*)(ptr);
	if(IS_SENSOR_TRIGGER(I_SENSOR4))
	{
		if(Sensor4TrigTime <= SENSOR4TRIGTIME_MAX)
		{
			Sensor4TrigTime++;
		}
	}
	else
	{
		if(IS_HIGH(is_serious_block))
		{
			//write ���ر������
			STOP_SERIOUS_BLOCK_WARNING();
			// ��ʼ�޳�����
		}
			
		Sensor4TrigTime = 0;
		CLR_PORT(is_serious_block);
	}
	if( Sensor4TrigTime == SENSOR4TRIGTIME_MAX )
	{
		//write ִ��������������
		OPEN_SERIOUS_BLOCK_WARNING();
		//ֹͣ�޳�����
		
		//���͸���λ��
		
		
		SET_PORT(is_serious_block);
	}
	
	
	
	if(IS_SENSOR_TRIGGER(I_SENSOR5))
	{
		if(Sensor5TrigTime <= SENSOR5TRIGTIME_MAX)
		{
			Sensor5TrigTime++;
		}
	}
	else
	{
		// write ������λ��

		STOP_BLOCK_WARNING();	
		Sensor5TrigTime = 0;

	}
	if( Sensor5TrigTime == SENSOR5TRIGTIME_MAX )
	{

		OPEN_BLOCK_WARNING();
		// write ������λ��
		
	}
}
