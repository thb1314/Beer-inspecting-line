#include "event.h"
#include "myport.h"
#include "tim.h"
#include <STC15F2K60S2.H>


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
				event |= START_SYS_EVENT;
				break;
			case STOP_BTN_DOWN:
				event |= STOP_SYS_EVENT;
				break;
			case FORCE_START_BTN_DOWN:
				event |= FORCE_START_SYS_EVENT;
				break;
			case FORCE_STOP_BTN_DOWN:
				event |= FORCE_STOP_SYS_EVENT;
				break;
			case CLOSE_BTN_DOWN:
				event |= CLOSE_SYS_EVENT;
				break;
			default:
				break;
		}
	}
	// 如果有串口消息 更新串口事件
	
	
	
	
}

void HandleEvent(void)
{
	if(IS_Event_Valid(CLOSE_BTN_DOWN))
	{
		CLR_Event(CLOSE_BTN_DOWN);
		// 开启定时器
		START_TIMER0();
		//开启标志位
		SET_PORT(is_start_check_close_btn);
	}
	
	
	
	
	
	
}
