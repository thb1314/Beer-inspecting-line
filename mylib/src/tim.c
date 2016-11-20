#include "myport.h"
#include "mytype.h"
#include "myfunc.h"
#include "event.h"
#include "tim.h"
#include "task.h"
#include <STC15F2K60S2.H>


bit is_start_check_close_btn = 0;

void InitTimer0(void)
{
	
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	
	TL0 = GET_LOW_8BIT(T0MS);		//���ö�ʱ��ֵ
	TH0 = GET_HIGH_8BIT(T0MS);		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	// �򿪴����ж�
	ET0 = 1;
	//������ʱ��
	START_TIMER0();
}

#ifdef UART1
void InitTimer3(void)
{
	T4T3M |= 0x02;		//��ʱ��ʱ��1Tģʽ
	
	
	T3L = (u8)T3MS;		//���ö�ʱ��ֵ
	T3H = (u8)(T3MS >> 8);		//���ö�ʱ��ֵ

	IE2 |= 0x20;		//����ʱ��3�ж�
}

//��ʱ���� ��⴮��1 tim3 check uart1
void tim3_isr(void) interrupt 19
{

	uart1_t_cntRxd++;
	if((uart1_t_cntRxd - uart1_cntRxd) > UART_DATA_TIMEOUT)
	{
		//�������
		SET_Event(UART1_RCV_EVENT);

		//�������
		uart1_t_cntRxd = uart1_cntRxd;
		uart1_cntRxd = 0;
		//�رն�ʱ��
		
		uart1_is_start_check_timer = 0;
		CLOSE_TIMER3();
	}
}
	
#endif



#ifdef UART2
void InitTimer4(void)
{
	T4T3M |= 0x20;		//��ʱ��ʱ��1Tģʽ

	T4L = GET_LOW_8BIT(T4MS);		//���ö�ʱ��ֵ
	T4H = GET_HIGH_8BIT(T4MS);	
	
	T4T3M |= 0x80;		//��ʱ��4��ʼ��ʱ
	
	IE2 |= 0x40;		//����ʱ��3�ж�
}


void tim4_isr(void) interrupt 20
{

	uart2_t_cntRxd++;
	if((uart2_t_cntRxd - uart2_cntRxd) > UART_DATA_TIMEOUT)
	{
		//�������
		SET_Event(UART2_RCV_EVENT);

		//�������
		uart2_t_cntRxd = uart2_cntRxd;
		uart2_cntRxd = 0;
		//�رն�ʱ��
		
		uart2_is_start_check_timer = 0;
		CLOSE_TIMER4();
	}
}
	
#endif



void tim0_isr(void) interrupt 1
{
	u8 i = 0;
	u8 tmp = taskbuffer.length;
	
	
	
	for(i = 0; i < tmp; i++)
	{
		if(taskbuffer.task[i]->isstart)
		{
			taskbuffer.task[i]->_timer++;
			if(taskbuffer.task[i]->_timer == taskbuffer.task[i]->timer)
			{
				// if the type equal  DELAY_TASK
				if(DELAY_TASK == taskbuffer.task[i]->type)
				{
					taskbuffer.task[i]->isstart = 0;
				}
				
				taskbuffer.task[i]->_timer = 0;
				// callback function
				(*(taskbuffer.task[i]->function))(&taskbuffer.task[i]);
			}

		}
	}
	
	
}
