#include "event.h"
#include "myport.h"
#include "tim.h"
#include "uart.h"
#include "task.h"
#include <STC15F2K60S2.H>


//创建一个任务 在关闭按键触发时启动
Task TskChkIsTrueClose;
void TskChkIsTrueCloseCallBack(void*);




volatile u16 event = NO_EVENT;

void UpdateEvent()
{
	//如果是按键按下
	if(IS_BTN_UPDATE(button_state))
	{
		CLR_BTN_UPDATE(button_state);
		switch(button_state)
		{
			case START_BTN_DOWN:
				SET_Event(START_SYS_EVENT);
				break;
			case STOP_BTN_DOWN:
				SET_Event(STOP_SYS_EVENT);
				break;
			case FORCE_START_BTN_DOWN:
				SET_Event(FORCE_START_SYS_EVENT);
				break;
			case FORCE_STOP_BTN_DOWN:
				SET_Event(FORCE_STOP_SYS_EVENT);
				break;
			case CLOSE_BTN_DOWN:
				SET_Event(CLOSE_SYS_EVENT);
				break;
			default:
				break;
		}
	}
	// 如果有串口消息 更新串口事件 这个交给了检测串口的定时器来做了
	
	
	
	
}

void HandleEvent(void)
{
	if(IS_Event_Valid(CLOSE_BTN_DOWN))
	{
		TskChkIsTrueClose.timer = 50;
		TskChkIsTrueClose.type = TIME_TASK;
		TskChkIsTrueClose.isstart = 1;
		TskChkIsTrueClose.function = TskChkIsTrueCloseCallBack; 
		TaskInit(&TskChkIsTrueClose);
		CLR_Event(CLOSE_BTN_DOWN);
	}
	//如果是串口1消息
	#ifdef UART1
	if(IS_Event_Valid(UART1_RCV_EVENT))
	{
		//接收消息
		
		Uart1Write(uart1_bufRxd,uart1_t_cntRxd);
		
		/*if(2 == uart1_t_cntRxd)
		{
			if(6 == uart1_bufRxd[0])
			{
				P6 = uart1_bufRxd[1];
				uart1_bufRxd[1] = P6;
				Uart1Write(uart1_bufRxd,uart1_t_cntRxd);
			}
			else if(7 == uart1_bufRxd[0])
			{
				P7 = uart1_bufRxd[1];
				uart1_bufRxd[1] = P7;
				Uart1Write(uart1_bufRxd,uart1_t_cntRxd);
			}
			
		}
		*/
		
		CLR_Event(UART1_RCV_EVENT);
		//清除计数
	}
	#endif
	#ifdef UART2
	if(IS_Event_Valid(UART2_RCV_EVENT))
	{
		//接收消息
		Uart2Write(uart2_bufRxd,uart2_t_cntRxd);
		CLR_Event(UART2_RCV_EVENT);
		//清除计数
	}
	#endif
	
}



// 检测按钮的回调函数
void TskChkIsTrueCloseCallBack(void* ptr)
{
	
	static u8 timer = 0;
	Task* mytask = (Task*)(ptr);
	if(B_IS_CLOSE_BTN_DOWN())
	{
		timer++;
		if(timer >= 60)
		{
			//执行相关的关机操作
			Uart1Write("ok\n",3);
			CPL_PORT(O_SECOND_ALARM_WARNING);
			
			
			timer = 0;
			TaskDelete(mytask);
		}
	}
	else
	{
		Uart1Write("fail\n",5);
		timer = 0;
		TaskDelete(mytask);
	}
}