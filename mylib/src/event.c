#include "event.h"

#include "myport.h"
#include "tim.h"
#include "uart.h"
#include "task.h"
#include "serial_cmd.h"
#include <intrins.h>
#include <STC15F2K60S2.H>

// 计算机超时时间
#define PC_UNRESPONSE_TIME_OUT 200

// 创建一个任务 在关闭按键触发时启动 create a task,trigger when close btn down
volatile Task TskChkIsTrueClose;
void TskChkIsTrueCloseCallBack(void*);



// 创建一个任务 用于检测上位机是否启动 create a task used to check is PC start
volatile Task TskChkIsPCStart;
void TskChkIsPCStartCallBack(void*);
bit isPCStart = 0;


// 创建一个任务 在传感器1触发时启用 create a task,trigger when sensor1 trigger
volatile Task TskChkIsSensor1TrigTO30;
void TskChkIsSensor1TrigTO30CallBack(void*);

//创建一个任务 传感器3触发后的延时任务
static u16 Sensor3TrigOkDelayTime = 0;
volatile Task TskSensor3TrigOk;
void TskSensor3TrigOkCallBack(void*);





// 防止重复添加任务的标志位
bit isStartEvent_CLOSE_SYS = 0;
bit isStartEvent_START_SYS = 0;
bit isStartEvent_SENSOR1_TRIGGER = 0;
bit isStartEvent_SENSOR3_TRIGGER = 0;


// 对上位机多长时基没有回复进行统计
static u8 pc_unresponse_timer = 0;
// 对sensor1 没有触发进行统计
static u8 sensor1_trigger_timerout = 0;
// 提取信息 
#define p_cmd ((SERIAL_CMD*)uart1_bufRxd)




SysState sys_state = NOT_START;

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
	
	
	//传感器触发(不可能同时触发)
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
		// write 变频器发送指令 所有电机开始运行
		
		
		sys_state = FORCE_START;
		CLR_Event(FORCE_START_SYS_EVENT);
	}
	
	if(IS_Event_Valid(FORCE_STOP_SYS_EVENT))
	{
		UartWrite(CMD_TSTOP_INSPECTING,PROTOCOL_LENGTH);
		if(NORMAL_START == sys_state)
		{
			//停止阻塞报警
			STOP_BLOCK_WARNING();
			//停止严重阻塞报警
			STOP_SERIOUS_BLOCK_WARNING();
		}
		sys_state = FORCE_STOP;
		CLR_Event(FORCE_STOP_SYS_EVENT);
	}
	
	if(IS_Event_Valid(STOP_SYS_EVENT))
	{
		UartWrite(CMD_TSTOP_INSPECTING,PROTOCOL_LENGTH);
		
		//write 向变频器发送停止运行
		
		
		
		if(NORMAL_START == sys_state)
		{
			//关闭射线源输出
			CLOSE_RAY_OUTPUT();
			//停止阻塞报警
			STOP_BLOCK_WARNING();
			//停止严重阻塞报警
			STOP_SERIOUS_BLOCK_WARNING();
		}
		
		sys_state = NORMAL_STOP;
		
		
		CLR_Event(STOP_SYS_EVENT);
	}
	
	
	if(IS_Event_Valid(CLOSE_SYS_EVENT))
	{
		//开启射线输出
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
		// 发送开始采集指令
		UartWrite(CMD_TSTART_INSPECTING,PROTOCOL_LENGTH);
		CLR_Event(SENSOR1_TRIGGER_EVENT);
	}
	if(IS_Event_Valid(SENSOR3_TRIGGER_EVENT))
	{
		// 指定的延时时间 执行提出操作
		if(IS_LOW(isStartEvent_SENSOR3_TRIGGER))
		{
			if(0 == Sensor3TrigOkDelayTime)
			{
				//write 直接执行踢飞退
				
				
				// 这里还需要判断当前是否堵塞
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
	//如果是串口1消息
	#ifdef UART1
	if(IS_Event_Valid(UART1_RCV_EVENT))
	{
		//接收消息
		// firrt check
		if( PROTOCOL_LENGTH == uart1_t_cntRxd )
		{
			
			//校验
			if((uart1_bufRxd[0] == 0x55) && (uart1_bufRxd[1] == 0xAA)  &&((u8)(uart1_bufRxd[PROTOCOL_LENGTH-5] + uart1_bufRxd[PROTOCOL_LENGTH-4] + uart1_bufRxd[PROTOCOL_LENGTH-3] + uart1_bufRxd[PROTOCOL_LENGTH-2]) == uart1_bufRxd[PROTOCOL_LENGTH-1]))
			{
				
				
				//判断cmd
				switch(p_cmd->cmd)
				{
					//通讯检测 进一步判断election
					case CMD_COM_TEST:
						switch(p_cmd->election)
						{
							//如果是上位机回复了_OK 说明通信成功
							case _OK:
								if(isStartEvent_START_SYS)
								{
									pc_unresponse_timer = 0;
									TaskDelete(&TskChkIsPCStart);
									// 开始启动
									// SET_Event(PC_HAVE_STARTED_EVENT);
									OPEN_RAY_OUTPUT();
									OPEN_SENSOR();
									OPEN_DETECTOR();
									OPEN_SOLENOIDVALVE();
									OPEN_AC_MATOR();
									
									
									CLR_PORT(isStartEvent_START_SYS);
									// test 调试
									UartWrite("PC Init OK!\r\n",13);
								}
								
								break;
							case 0x00:
								UartWrite(CMD_TEST_RE,PROTOCOL_LENGTH);
						}
						break;
						
					// 强制启动
					case CMD_START:
						UartWrite(CMD_FORCE_STARTUP_RE_OK,PROTOCOL_LENGTH);
						// write 向变频发送指令
						break;
						
					//传感器自检
					case CMD_SENSORS_TEST:
						switch(p_cmd->election)
						{
							case SENSOR1:
								//检测传感器状态
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
								//检测传感器状态
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
								//检测传感器状态
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
								//检测传感器状态
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
								//检测传感器状态
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
					
					//变频器自检
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
						
					//X射线打开
					case CMD_START_INSPECT:
						
					
					
						break;
					//X射线关闭
					case CMD_STOP_INSPECT:
						
					
					
						break;
					//设置传送带延时
					case CMD_SENSOR_DELAY:
						
					
					
						break;
					
					//设置传送带速度
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
			sys_state = NORMAL_CLOSE;
			
			timer = 0;
			TaskDelete(mytask);
			
			
			// test 执行相关的关机操作
			UartWrite("pc clolse ok\r\n",12);
			
			//给上位机发送关机命令
			UartWrite(CMD_CLOSE_PC,PROTOCOL_LENGTH);
			
			//给变频器发送停止运行命令 write
			
			//关闭射线源输出
			CLOSE_RAY_OUTPUT();
			//停止阻塞报警
			STOP_BLOCK_WARNING();
			//停止严重阻塞报警
			STOP_SERIOUS_BLOCK_WARNING();
			//射线源下电
			CLOSE_RAY_OUTPUT();
			//传感器下电
			CLOSE_SENSOR();
			//探测器下电
			CLOSE_DETECTOR();
			//电磁阀下电
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

// 检测上位机是否启动的函数
void TskChkIsPCStartCallBack(void* ptr)
{
	Task* mytask = (Task*)(ptr);
	UartWrite( CMD_TEST , PROTOCOL_LENGTH );

	pc_unresponse_timer++;
	if(pc_unresponse_timer > PC_UNRESPONSE_TIME_OUT)
	{
		pc_unresponse_timer = 0;
		
		//重启PC
		CLOSE_PC_POWER();
		OPEN_PC_POWER();
		TaskDelete(mytask);
	}
}


// 检测传感器1是否超过30s的函数
void TskChkIsSensor1TrigTO30CallBack(void* ptr)
{
	Task* mytask = (Task*)(ptr);
	if(!IS_SENSOR_TRIGGER(I_SENSOR1))
	{
		sensor1_trigger_timerout++;
	}
	else
	{
		//30s内 触发 不用删除任务 清零超时时间
		sensor1_trigger_timerout = 0;
	}
	if(sensor1_trigger_timerout > 30)
	{
		//超时30s 关闭射线源
		CLOSE_RAY_OUTPUT();
		TaskDelete(mytask);
		//清除任务设置标志位
		CLR_PORT(isStartEvent_SENSOR1_TRIGGER);
	}
}

// 传感器3 延时触发回调函数
void TskSensor3TrigOkCallBack(void* ptr)
{
	Task* mytask = (Task*)(ptr);
	// write 让气缸动作
	
	// 这里还需要判断当前是否堵塞
	if(is_serious_block)
	{
		
	}	
	
	TaskDelete(mytask);
	CLR_PORT(isStartEvent_SENSOR3_TRIGGER);
	
	// write 检测传感器4 返回结果
	
	
}