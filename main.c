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

void main()
{
	SystemInit();
	while(1)
	{
		CheckBtn();
		UpdateEvent();
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
	
	//初始化串口
	
	//初始化定时器
	InitTimer0();
	//开启定时器
	START_TIMER0();
	
	//开启总中断
	EA = 1;
	
}