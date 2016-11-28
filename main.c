/******************************************************************* 
 *  Copyright(c) 2016 THB-CCUT  
 *  All rights reserved. 
 *   
 *  文件名称: main.c
 *  简要描述: 主程序文件
 *   
 *  创建日期: 2016-11-06
 *  作者: THB
 *  说明: 
 *   
 *  修改日期: 
 *  作者: 
 *  说明: 
 ******************************************************************/
#include <STC15F2K60S2.H>
#include "main.h"
#include "myfunc.h"
#include "myport.h"
#include "mytype.h"
#include "serial_cmd.h"
#include "exit.h"
#include "event.h"
#include "tim.h"
#include "uart.h"
#include "task.h"
#include "delay.h"


//创建一个任务 检测传感器4是否连续被触发
static u8 idata Sensor4TrigTime = 0;
static u8 idata Sensor5TrigTime = 0;


volatile Task idata TskIsSensor4_5_TrigOk;
void TskIsSensor4_5_TrigOkCallBack(void*);
bit is_serious_block = 0;

#define SENSOR4TRIGTIME_MAX 50
#define SENSOR5TRIGTIME_MAX 50

void main()
{
	SystemInit();
	
	P0M1 &= ~0x01;
	P0M1 |= 0x01;
	
	P6 = 0xFF;
	P7 = 0xFF;
	
	
	while(1)
	{
		//检测按键
		CheckBtn();
		//更新事件状态
		UpdateEvent();
		//处理事件
		HandleEvent();



	}
}



// 系统初始化函数
void SystemInit(void)
{

	//初始化IO口
	InitPort();
	//初始化外部中断
	InitExit();
	//初始化定时器
	InitTimer0();
	//初始化串口
	#ifdef UART1
	Uart1Init();
	#endif
	#ifdef UART2
	Uart2Init();
	#endif
	//开启总中断
	SET_PORT(EA);
	
	

	TskIsSensor4_5_TrigOk.timer = 100;
	TskIsSensor4_5_TrigOk.type = TIME_TASK;
	TskIsSensor4_5_TrigOk.isstart = 1;
	TskIsSensor4_5_TrigOk.function = TskIsSensor4_5_TrigOkCallBack; 
	TaskInit(&TskIsSensor4_5_TrigOk);
	
}

void TskIsSensor4_5_TrigOkCallBack(void* ptr)
{
	Task* mytask = (Task*)(ptr);
	if(IS_SENSOR_TRIGGER(I_SENSOR4))
	{
		if(Sensor4TrigTime <= SENSOR4TRIGTIME_MAX)
		{
			Sensor4TrigTime++;
		}
	}
	else
	{
		if(IS_HIGH(is_serious_block))
		{
			//write 严重报警解除
			STOP_SERIOUS_BLOCK_WARNING();
			// 开始剔除操作
		}
			
		Sensor4TrigTime = 0;
		CLR_PORT(is_serious_block);
	}
	if( Sensor4TrigTime == SENSOR4TRIGTIME_MAX )
	{
		//write 执行严重阻塞报警
		OPEN_SERIOUS_BLOCK_WARNING();
		//停止剔除操作
		
		//发送给上位机
		
		
		SET_PORT(is_serious_block);
	}
	
	
	
	if(IS_SENSOR_TRIGGER(I_SENSOR5))
	{
		if(Sensor5TrigTime <= SENSOR5TRIGTIME_MAX)
		{
			Sensor5TrigTime++;
		}
	}
	else
	{
		// write 传给上位机

		STOP_BLOCK_WARNING();	
		Sensor5TrigTime = 0;

	}
	if( Sensor5TrigTime == SENSOR5TRIGTIME_MAX )
	{

		OPEN_BLOCK_WARNING();
		// write 传给上位机
		
	}
}
