#include "event.h"
#include "myport.h"

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
	
}
