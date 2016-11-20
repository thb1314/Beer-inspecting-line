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
	
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	
	TL0 = GET_LOW_8BIT(T0MS);		//设置定时初值
	TH0 = GET_HIGH_8BIT(T0MS);		//设置定时初值
	TF0 = 0;		//清除TF0标志
	// 打开串口中断
	ET0 = 1;
	//开启定时器
	START_TIMER0();
}

#ifdef UART1
void InitTimer3(void)
{
	T4T3M |= 0x02;		//定时器时钟1T模式
	
	
	T3L = (u8)T3MS;		//设置定时初值
	T3H = (u8)(T3MS >> 8);		//设置定时初值

	IE2 |= 0x20;		//允许定时器3中断
}

//定时器三 检测串口1 tim3 check uart1
void tim3_isr(void) interrupt 19
{

	uart1_t_cntRxd++;
	if((uart1_t_cntRxd - uart1_cntRxd) > UART_DATA_TIMEOUT)
	{
		//接收完成
		SET_Event(UART1_RCV_EVENT);

		//清除计数
		uart1_t_cntRxd = uart1_cntRxd;
		uart1_cntRxd = 0;
		//关闭定时器
		
		uart1_is_start_check_timer = 0;
		CLOSE_TIMER3();
	}
}
	
#endif



#ifdef UART2
void InitTimer4(void)
{
	T4T3M |= 0x20;		//定时器时钟1T模式

	T4L = GET_LOW_8BIT(T4MS);		//设置定时初值
	T4H = GET_HIGH_8BIT(T4MS);	
	
	T4T3M |= 0x80;		//定时器4开始计时
	
	IE2 |= 0x40;		//允许定时器3中断
}


void tim4_isr(void) interrupt 20
{

	uart2_t_cntRxd++;
	if((uart2_t_cntRxd - uart2_cntRxd) > UART_DATA_TIMEOUT)
	{
		//接收完成
		SET_Event(UART2_RCV_EVENT);

		//清除计数
		uart2_t_cntRxd = uart2_cntRxd;
		uart2_cntRxd = 0;
		//关闭定时器
		
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
