#include "myport.h"
#include "mytype.h"
#include "tim.h"
#include "task.h"
#include <STC15F2K60S2.H>


bit is_start_check_close_btn = 0;

void InitTimer0()
{
	
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	
	TL0 = (u8)T0MS;		//设置定时初值
	TH0 = (u8)(T0MS >> 8);		//设置定时初值
	TF0 = 0;		//清除TF0标志
	// 打开串口中断
	ET0 = 1;
	//开启定时器
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
