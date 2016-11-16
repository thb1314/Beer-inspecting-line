#include "event.h"
#include "myport.h"
#include "tim.h"
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
		TskChkIsTrueClose.timer = 50;
		TskChkIsTrueClose.type = 
		TskChkIsTrueClose.isstart = 1;
		TskChkIsTrueClose.function = TskChkIsTrueCloseCallBack; 
		TaskInit(&TskChkIsTrueClose);
		CLR_Event(CLOSE_BTN_DOWN);
	}
	
	
}



// 检测按钮的回调函数
void TskChkIsTrueCloseCallBack(void* ptr)
{
	Task* mytask = (Task*)(ptr);
	static u8 timer = 0;
	if(B_IS_CLOSE_BTN_DOWN())
	{
		timer++;
		if(timer >= 60)
		{
			//执行关机操作
		}
	}
	else
	{
		timer = 0;
		TaskDelete(&TskChkIsTrueClose);
	}
}