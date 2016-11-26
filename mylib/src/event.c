#include "event.h"

#include "myport.h"
#include "tim.h"
#include "uart.h"
#include "task.h"
#include "serial_cmd.h"
#include <intrins.h>
#include <STC15F2K60S2.H>


// ����һ������ �ڹرհ�������ʱ���� create a task,trigger when close btn down
volatile Task TskChkIsTrueClose;
void TskChkIsTrueCloseCallBack(void*);



// ����һ������ ���ڼ����λ���Ƿ����� create a task used to check is PC start
volatile Task TskChkIsPCStart;
void TskChkIsPCStartCallBack(void*);
bit isPCStart = 0;


// ��ֹ�ظ��������ı�־λ
bit isStartEvent_CLOSE_SYS = 0;
bit isStartEvent_START_SYS = 0;


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
	//����Ǵ���1��Ϣ
	#ifdef UART1
	if(IS_Event_Valid(UART1_RCV_EVENT))
	{
		//������Ϣ
		//Uart1Write(uart1_bufRxd,uart1_t_cntRxd);
		
		// firrt check
		if( PROTOCOL_LENGTH == uart1_t_cntRxd )
		{
			
			//У��
			if((uart1_bufRxd[0] == 0x55) && (uart1_bufRxd[1] == 0xAA)  &&((u8)(uart1_bufRxd[PROTOCOL_LENGTH-5] + uart1_bufRxd[PROTOCOL_LENGTH-4] + uart1_bufRxd[PROTOCOL_LENGTH-3] + uart1_bufRxd[PROTOCOL_LENGTH-2]) == uart1_bufRxd[PROTOCOL_LENGTH-1]))
			{
				// ��ȡ��Ϣ 
				SERIAL_CMD* p_cmd = 0x00;
				p_cmd = (SERIAL_CMD*)uart1_bufRxd;

				//�ж�cmd
				switch(p_cmd->cmd)
				{
					case CMD_COM_TEST:
						if(isStartEvent_START_SYS)
						{
							TaskDelete(&TskChkIsPCStart);
							// ��ʼ����
							// SET_Event(PC_HAVE_STARTED_EVENT);
							OPEN_RAY_OUTPUT();
							OPEN_SENSOR();
							OPEN_DETECTOR();
							OPEN_SOLENOIDVALVE();
							OPEN_AC_MATOR();
							
							// test ����
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
		// ������Ϣ
		Uart2Write(uart2_bufRxd,uart2_t_cntRxd);
		CLR_Event(UART2_RCV_EVENT);
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

// �����λ���Ƿ������ĺ���
void TskChkIsPCStartCallBack(void* ptr)
{
	Task* mytask = (Task*)(ptr);
	UartWrite( CMD_TEST , PROTOCOL_LENGTH );

	
}