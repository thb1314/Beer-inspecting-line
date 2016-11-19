#include "myport.h"
#include "mytype.h"
#include "tim.h"
#include "task.h"
#include <STC15F2K60S2.H>


bit is_start_check_close_btn = 0;

void InitTimer0()
{
	
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	
	TL0 = (u8)T0MS;		//���ö�ʱ��ֵ
	TH0 = (u8)(T0MS >> 8);		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	// �򿪴����ж�
	ET0 = 1;
	//������ʱ��
	START_TIMER0();
	
}
static u16 timer = 0;

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
