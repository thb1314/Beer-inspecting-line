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
 

void main()
{
	SystenInit();
	while(1)
	{
		
	}
}



// 系统初始化函数
void SystenInit(void)
{

	
	
	InitPort();
	
}