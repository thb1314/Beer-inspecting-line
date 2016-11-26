#include "event.h"

#include "myport.h"
#include "tim.h"
#include "uart.h"
#include "task.h"
#include "serial_cmd.h"
#include <intrins.h>
#include <STC15F2K60S2.H>


// 创建一个任务 在关闭按键触发时启动 create a task,trigger when close btn down
volatile Task TskChkIsTrueClose;
void TskChkIsTrueCloseCallBack(void*);



// 创建一个任务 用于检测上位机是否启动 create a task used to check is PC start
volatile Task TskChkIsPCStart;
void TskChkIsPCStartCallBack(void*);
bit isPCStart = 0;


// 防止重复添加任务的标志位
bit isStartEvent_CLOSE_SYS = 0;
bit isStartEvent_START_SYS = 0;


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
	if(IS_Event_Valid(START_SYS_EVENT))
	{
		if(!isStartEvent_START_SYS)
		{
			TskChkIsPCStart.timer = 100;
			TskChkIsPCStart.type = TIME_TASK;
			TskChkIsPCStart.isstart = 1;
			TskChkIsPCStart.function = TskChkIsPCStartCallBack; 
			TaskInit(&TskChkIsPCStart);
			
			isStartEvent_START_SYS = 1;
			
			
			CLR_Event(START_SYS_EVENT);
		}
	}
	
	
	if(IS_Event_Valid(CLOSE_SYS_EVENT))
	{
		if(!isStartEvent_CLOSE_SYS)
		{
			TskChkIsTrueClose.timer = 50;
			TskChkIsTrueClose.type = TIME_TASK;
			TskChkIsTrueClose.isstart = 1;
			TskChkIsTrueClose.function = TskChkIsTrueCloseCallBack; 
			TaskInit(&TskChkIsTrueClose);
			
			isStartEvent_CLOSE_SYS = 1;
		}

		
		CLR_Event(CLOSE_SYS_EVENT);
		
	}
//	if(IS_Event_Valid(PC_HAVE_STARTED_EVENT))
//	{
//		
//		
//		
//		CLR_Event(PC_HAVE_STARTED_EVENT);
//		
//		
//	}
	//如果是串口1消息
	#ifdef UART1
	if(IS_Event_Valid(UART1_RCV_EVENT))
	{
		//接收消息
		//Uart1Write(uart1_bufRxd,uart1_t_cntRxd);
		
		// firrt check
		if( PROTOCOL_LENGTH == uart1_t_cntRxd )
		{
			
			//校验
			if((uart1_bufRxd[0] == 0x55) && (uart1_bufRxd[1] == 0xAA)  &&((u8)(uart1_bufRxd[PROTOCOL_LENGTH-5] + uart1_bufRxd[PROTOCOL_LENGTH-4] + uart1_bufRxd[PROTOCOL_LENGTH-3] + uart1_bufRxd[PROTOCOL_LENGTH-2]) == uart1_bufRxd[PROTOCOL_LENGTH-1]))
			{
				// 提取信息 
				SERIAL_CMD* p_cmd = 0x00;
				p_cmd = (SERIAL_CMD*)uart1_bufRxd;

				//判断cmd
				switch(p_cmd->cmd)
				{
					case CMD_COM_TEST:
						if(isStartEvent_START_SYS)
						{
							TaskDelete(&TskChkIsPCStart);
							// 开始启动
							// SET_Event(PC_HAVE_STARTED_EVENT);
							OPEN_RAY_OUTPUT();
							OPEN_SENSOR();
							OPEN_DETECTOR();
							OPEN_SOLENOIDVALVE();
							OPEN_AC_MATOR();
							
							// test 调试
							UartWrite("PC Init OK!\r\n",13);
						}

						break;
					default:
						// not do anything
						break;
				}
				

				
				
			}
		}

		
		CLR_Event(UART1_RCV_EVENT);
	}
	#endif
	#ifdef UART2
	if(IS_Event_Valid(UART2_RCV_EVENT))
	{
		// 接收消息
		Uart2Write(uart2_bufRxd,uart2_t_cntRxd);
		CLR_Event(UART2_RCV_EVENT);
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
			UartWrite("ok\r\n",4);
			CPL_PORT(O_SECOND_ALARM_WARNING);
			
			
			timer = 0;
			TaskDelete(mytask);
			isStartEvent_CLOSE_SYS = 0;
		}
	}
	else
	{

		timer = 0;
		TaskDelete(mytask);
		isStartEvent_CLOSE_SYS = 0;
	}
	
}

// 检测上位机是否启动的函数
void TskChkIsPCStartCallBack(void* ptr)
{
	Task* mytask = (Task*)(ptr);
	UartWrite( CMD_TEST , PROTOCOL_LENGTH );

	
}