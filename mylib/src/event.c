#include "event.h"
#include "myport.h"
#include "tim.h"
#include "uart.h"
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
	// ����д�����Ϣ ���´����¼� ��������˼�⴮�ڵĶ�ʱ��������
	
	
	
	
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
	//����Ǵ���1��Ϣ
	#ifdef UART1
	if(IS_Event_Valid(UART1_RCV_EVENT))
	{
		//������Ϣ
		
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
		//�������
	}
	#endif
	#ifdef UART2
	if(IS_Event_Valid(UART2_RCV_EVENT))
	{
		//������Ϣ
		Uart2Write(uart2_bufRxd,uart2_t_cntRxd);
		CLR_Event(UART2_RCV_EVENT);
		//�������
	}
	#endif
	
}



// ��ⰴť�Ļص�����
void TskChkIsTrueCloseCallBack(void* ptr)
{
	
	static u8 timer = 0;
	Task* mytask = (Task*)(ptr);
	if(B_IS_CLOSE_BTN_DOWN())
	{
		timer++;
		if(timer >= 60)
		{
			//ִ����صĹػ�����
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