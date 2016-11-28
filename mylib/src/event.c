#include "event.h"

#include "myport.h"
#include "tim.h"
#include "uart.h"
#include "task.h"
#include "serial_cmd.h"
#include <intrins.h>
#include <STC15F2K60S2.H>

// �������ʱʱ��
#define PC_UNRESPONSE_TIME_OUT 200

// ����һ������ �ڹرհ�������ʱ���� create a task,trigger when close btn down
volatile Task TskChkIsTrueClose;
void TskChkIsTrueCloseCallBack(void*);



// ����һ������ ���ڼ����λ���Ƿ����� create a task used to check is PC start
volatile Task TskChkIsPCStart;
void TskChkIsPCStartCallBack(void*);
bit isPCStart = 0;


// ����һ������ �ڴ�����1����ʱ���� create a task,trigger when sensor1 trigger
volatile Task TskChkIsSensor1TrigTO30;
void TskChkIsSensor1TrigTO30CallBack(void*);

//����һ������ ������3���������ʱ����
static u16 Sensor3TrigOkDelayTime = 0;
volatile Task TskSensor3TrigOk;
void TskSensor3TrigOkCallBack(void*);





// ��ֹ�ظ��������ı�־λ
bit isStartEvent_CLOSE_SYS = 0;
bit isStartEvent_START_SYS = 0;
bit isStartEvent_SENSOR1_TRIGGER = 0;
bit isStartEvent_SENSOR3_TRIGGER = 0;


// ����λ���೤ʱ��û�лظ�����ͳ��
static u8 pc_unresponse_timer = 0;
// ��sensor1 û�д�������ͳ��
static u8 sensor1_trigger_timerout = 0;
// ��ȡ��Ϣ 
#define p_cmd ((SERIAL_CMD*)uart1_bufRxd)




SysState sys_state = NOT_START;

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
	
	
	//����������(������ͬʱ����)
	if(IS_SENSOR_TRIGGER(I_SENSOR1))
	{
		SET_Event(SENSOR1_TRIGGER_EVENT);
	}
	else if(IS_SENSOR_TRIGGER(I_SENSOR2))
	{
		SET_Event(SENSOR2_TRIGGER_EVENT);
	}
	else if(IS_SENSOR_TRIGGER(I_SENSOR3))
	{
		SET_Event(SENSOR3_TRIGGER_EVENT);
	}
	else if(IS_SENSOR_TRIGGER(I_SENSOR4))
	{
		SET_Event(SENSOR4_TRIGGER_EVENT);
	}
	else if(IS_SENSOR_TRIGGER(I_SENSOR5))
	{
		SET_Event(SENSOR5_TRIGGER_EVENT);
	}
	
	
}

void HandleEvent(void)
{
	if(IS_Event_Valid(START_SYS_EVENT))
	{
		
		if(IS_LOW(isStartEvent_START_SYS))
		{
			TskChkIsPCStart.timer = 100;
			TskChkIsPCStart.type = TIME_TASK;
			TskChkIsPCStart.isstart = 1;
			TskChkIsPCStart.function = TskChkIsPCStartCallBack; 
			TaskInit(&TskChkIsPCStart);
			
			SET_PORT(isStartEvent_START_SYS);
			sys_state = NORMAL_START;
			
		}
		CLR_Event(START_SYS_EVENT);
	}
	
	if(IS_Event_Valid(FORCE_START_SYS_EVENT))
	{
		UartWrite(CMD_FORCE_STARTUP,PROTOCOL_LENGTH);
		// write ��Ƶ������ָ�� ���е����ʼ����
		
		
		sys_state = FORCE_START;
		CLR_Event(FORCE_START_SYS_EVENT);
	}
	
	if(IS_Event_Valid(FORCE_STOP_SYS_EVENT))
	{
		UartWrite(CMD_TSTOP_INSPECTING,PROTOCOL_LENGTH);
		if(NORMAL_START == sys_state)
		{
			//ֹͣ��������
			STOP_BLOCK_WARNING();
			//ֹͣ������������
			STOP_SERIOUS_BLOCK_WARNING();
		}
		sys_state = FORCE_STOP;
		CLR_Event(FORCE_STOP_SYS_EVENT);
	}
	
	if(IS_Event_Valid(STOP_SYS_EVENT))
	{
		UartWrite(CMD_TSTOP_INSPECTING,PROTOCOL_LENGTH);
		
		//write ���Ƶ������ֹͣ����
		
		
		
		if(NORMAL_START == sys_state)
		{
			//�ر�����Դ���
			CLOSE_RAY_OUTPUT();
			//ֹͣ��������
			STOP_BLOCK_WARNING();
			//ֹͣ������������
			STOP_SERIOUS_BLOCK_WARNING();
		}
		
		sys_state = NORMAL_STOP;
		
		
		CLR_Event(STOP_SYS_EVENT);
	}
	
	
	if(IS_Event_Valid(CLOSE_SYS_EVENT))
	{
		//�����������
		OPEN_RAY_OUTPUT();
		
		if(IS_LOW(isStartEvent_CLOSE_SYS))
		{
			TskChkIsTrueClose.timer = 50;
			TskChkIsTrueClose.type = TIME_TASK;
			TskChkIsTrueClose.isstart = 1;
			TskChkIsTrueClose.function = TskChkIsTrueCloseCallBack; 
			TaskInit(&TskChkIsTrueClose);
			
			SET_PORT(isStartEvent_CLOSE_SYS);
		}
		
		
		CLR_Event(CLOSE_SYS_EVENT);
		
	}
	
	if(IS_Event_Valid(SENSOR1_TRIGGER_EVENT))
	{
		if(IS_LOW(isStartEvent_SENSOR1_TRIGGER))
		{
			TskChkIsSensor1TrigTO30.timer = 1000;
			TskChkIsSensor1TrigTO30.type = DELAY_TASK;
			TskChkIsSensor1TrigTO30.isstart = 1;
			TskChkIsSensor1TrigTO30.function = TskChkIsSensor1TrigTO30CallBack; 
			TaskInit(&TskChkIsSensor1TrigTO30);
			
			SET_PORT(isStartEvent_SENSOR1_TRIGGER);
		}
		CLR_Event(SENSOR1_TRIGGER_EVENT);
	}
	if(IS_Event_Valid(SENSOR2_TRIGGER_EVENT))
	{
		// ���Ϳ�ʼ�ɼ�ָ��
		UartWrite(CMD_TSTART_INSPECTING,PROTOCOL_LENGTH);
		CLR_Event(SENSOR1_TRIGGER_EVENT);
	}
	if(IS_Event_Valid(SENSOR3_TRIGGER_EVENT))
	{
		// ָ������ʱʱ�� ִ���������
		if(IS_LOW(isStartEvent_SENSOR3_TRIGGER))
		{
			if(0 == Sensor3TrigOkDelayTime)
			{
				//write ֱ��ִ���߷���
				
				
				// ���ﻹ��Ҫ�жϵ�ǰ�Ƿ����
				if(is_serious_block)
				{
					
				}
			}
			else
			{
				TskSensor3TrigOk.timer = Sensor3TrigOkDelayTime;
				TskSensor3TrigOk.type = DELAY_TASK;
				TskSensor3TrigOk.isstart = 1;
				TskSensor3TrigOk.function = TskSensor3TrigOkCallBack; 
				TaskInit(&TskSensor3TrigOk);
				SET_PORT(isStartEvent_SENSOR3_TRIGGER);	
			}
		
		}
		
		CLR_Event(SENSOR1_TRIGGER_EVENT);
	}
	if(IS_Event_Valid(SENSOR4_TRIGGER_EVENT))
	{
		
		
		
		CLR_Event(SENSOR1_TRIGGER_EVENT);
	}
	if(IS_Event_Valid(SENSOR5_TRIGGER_EVENT))
	{
		
		CLR_Event(SENSOR1_TRIGGER_EVENT);
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
		// firrt check
		if( PROTOCOL_LENGTH == uart1_t_cntRxd )
		{
			
			//У��
			if((uart1_bufRxd[0] == 0x55) && (uart1_bufRxd[1] == 0xAA)  &&((u8)(uart1_bufRxd[PROTOCOL_LENGTH-5] + uart1_bufRxd[PROTOCOL_LENGTH-4] + uart1_bufRxd[PROTOCOL_LENGTH-3] + uart1_bufRxd[PROTOCOL_LENGTH-2]) == uart1_bufRxd[PROTOCOL_LENGTH-1]))
			{
				
				
				//�ж�cmd
				switch(p_cmd->cmd)
				{
					//ͨѶ��� ��һ���ж�election
					case CMD_COM_TEST:
						switch(p_cmd->election)
						{
							//�������λ���ظ���_OK ˵��ͨ�ųɹ�
							case _OK:
								if(isStartEvent_START_SYS)
								{
									pc_unresponse_timer = 0;
									TaskDelete(&TskChkIsPCStart);
									// ��ʼ����
									// SET_Event(PC_HAVE_STARTED_EVENT);
									OPEN_RAY_OUTPUT();
									OPEN_SENSOR();
									OPEN_DETECTOR();
									OPEN_SOLENOIDVALVE();
									OPEN_AC_MATOR();
									
									
									CLR_PORT(isStartEvent_START_SYS);
									// test ����
									UartWrite("PC Init OK!\r\n",13);
								}
								
								break;
							case 0x00:
								UartWrite(CMD_TEST_RE,PROTOCOL_LENGTH);
						}
						break;
						
					// ǿ������
					case CMD_START:
						UartWrite(CMD_FORCE_STARTUP_RE_OK,PROTOCOL_LENGTH);
						// write ���Ƶ����ָ��
						break;
						
					//�������Լ�
					case CMD_SENSORS_TEST:
						switch(p_cmd->election)
						{
							case SENSOR1:
								//��⴫����״̬
								if(IS_SENSOR_OK(I_SENSOR1))
								{
									p_cmd->dat[1] = _OK;
								}
								else
								{
									p_cmd->dat[1] = _NG;
								}
								
								break;
							case SENSOR2:
								//��⴫����״̬
								if(IS_SENSOR_OK(I_SENSOR2))
								{
									p_cmd->dat[1] = _OK;
								}
								else
								{
									p_cmd->dat[1] = _NG;
								}
								
								break;
							case SENSOR3:
								//��⴫����״̬
								if(IS_SENSOR_OK(I_SENSOR3))
								{
									p_cmd->dat[1] = _OK;
								}
								else
								{
									p_cmd->dat[1] = _NG;
								}
								break;
							case SENSOR4:
								//��⴫����״̬
								if(IS_SENSOR_OK(I_SENSOR4))
								{
									p_cmd->dat[1] = _OK;
								}
								else
								{
									p_cmd->dat[1] = _NG;
								}
								
								break;
							case SENSOR5:
								//��⴫����״̬
								if(IS_SENSOR_OK(I_SENSOR5))
								{
									p_cmd->dat[1] = _OK;
								}
								else
								{
									p_cmd->dat[1] = _NG;
								}
								break;
						}
						UartWrite(uart1_bufRxd,PROTOCOL_LENGTH);
						break;
					
					//��Ƶ���Լ�
					case CMD_TRANS_TEST:
						switch(p_cmd->election)
						{
							case TRANS1:
								// change p_cmd->dat
								
								break;
							case TRANS2:
								
								
								break;
							case TRANS3:
								
								
								break;
						}
						UartWrite(uart1_bufRxd,PROTOCOL_LENGTH);
					
						break;
						
					//X���ߴ�
					case CMD_START_INSPECT:
						
					
					
						break;
					//X���߹ر�
					case CMD_STOP_INSPECT:
						
					
					
						break;
					//���ô��ʹ���ʱ
					case CMD_SENSOR_DELAY:
						
					
					
						break;
					
					//���ô��ʹ��ٶ�
					case CMD_TRANS_SPEED:
						
						
					
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
			sys_state = NORMAL_CLOSE;
			
			timer = 0;
			TaskDelete(mytask);
			
			
			// test ִ����صĹػ�����
			UartWrite("pc clolse ok\r\n",12);
			
			//����λ�����͹ػ�����
			UartWrite(CMD_CLOSE_PC,PROTOCOL_LENGTH);
			
			//����Ƶ������ֹͣ�������� write
			
			//�ر�����Դ���
			CLOSE_RAY_OUTPUT();
			//ֹͣ��������
			STOP_BLOCK_WARNING();
			//ֹͣ������������
			STOP_SERIOUS_BLOCK_WARNING();
			//����Դ�µ�
			CLOSE_RAY_OUTPUT();
			//�������µ�
			CLOSE_SENSOR();
			//̽�����µ�
			CLOSE_DETECTOR();
			//��ŷ��µ�
			CLOSE_SOLENOIDVALVE();
			
			
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

	pc_unresponse_timer++;
	if(pc_unresponse_timer > PC_UNRESPONSE_TIME_OUT)
	{
		pc_unresponse_timer = 0;
		
		//����PC
		CLOSE_PC_POWER();
		OPEN_PC_POWER();
		TaskDelete(mytask);
	}
}


// ��⴫����1�Ƿ񳬹�30s�ĺ���
void TskChkIsSensor1TrigTO30CallBack(void* ptr)
{
	Task* mytask = (Task*)(ptr);
	if(!IS_SENSOR_TRIGGER(I_SENSOR1))
	{
		sensor1_trigger_timerout++;
	}
	else
	{
		//30s�� ���� ����ɾ������ ���㳬ʱʱ��
		sensor1_trigger_timerout = 0;
	}
	if(sensor1_trigger_timerout > 30)
	{
		//��ʱ30s �ر�����Դ
		CLOSE_RAY_OUTPUT();
		TaskDelete(mytask);
		//����������ñ�־λ
		CLR_PORT(isStartEvent_SENSOR1_TRIGGER);
	}
}

// ������3 ��ʱ�����ص�����
void TskSensor3TrigOkCallBack(void* ptr)
{
	Task* mytask = (Task*)(ptr);
	// write �����׶���
	
	// ���ﻹ��Ҫ�жϵ�ǰ�Ƿ����
	if(is_serious_block)
	{
		
	}	
	
	TaskDelete(mytask);
	CLR_PORT(isStartEvent_SENSOR3_TRIGGER);
	
	// write ��⴫����4 ���ؽ��
	
	
}