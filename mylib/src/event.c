#include "event.h"
#include "myport.h"
#include "tim.h"
#include "task.h"
#include <STC15F2K60S2.H>


//����һ������ �ڹرհ�������ʱ����
Task TskChkIsTrueClose;
void TskChkIsTrueCloseCallBack(void*);




volatile u16 event = NO_EVENT;

void UpdateEvent()
{
	//����ǰ�������
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
	// ����д�����Ϣ ���´����¼�
	
	
	
	
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



// ��ⰴť�Ļص�����
void TskChkIsTrueCloseCallBack(void* ptr)
{
	Task* mytask = (Task*)(ptr);
	static u8 timer = 0;
	if(B_IS_CLOSE_BTN_DOWN())
	{
		timer++;
		if(timer >= 60)
		{
			//ִ�йػ�����
		}
	}
	else
	{
		timer = 0;
		TaskDelete(&TskChkIsTrueClose);
	}
}