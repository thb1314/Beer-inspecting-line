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
 
//注意: STC15W4K32S4系列的芯片,上电后所有与PWM相关的IO口均为
//      高阻态,需将这些口设置为准双向口或强推挽模式方可正常使用
//相关IO: P0.6/P0.7/P1.6/P1.7/P2.1/P2.2
//        P2.3/P2.7/P3.7/P4.2/P4.4/P4.5 
 
 

void main()
{
	SystenInit();
	while(1)
	{
		
	}
}



// 系统初始化函数
void SystenInit()
{
//注意: STC15W4K32S4系列的芯片,上电后所有与PWM相关的IO口均为
//      高阻态,需将这些口设置为准双向口或强推挽模式方可正常使用
//相关IO: P0.6/P0.7/P1.6/P1.7/P2.1/P2.2
//        P2.3/P2.7/P3.7/P4.2/P4.4/P4.5
	
	// 配置相关IO口为准双向口
	// P06 P07 准双向口
	P0M1 &= 0x3F;
	P0M0 &= 0x3F;
	// P16 P17 准双向口
	P1M1 &= 0x3F;
	P1M0 &= 0x3F;
	// P21 P22 P23 P27 准双向口
	P2M1 &= 0x71;
	P2M0 &= 0x71;
	// P37 准双向口
	P3M1 &= 0x7F;
	P3M0 &= 0x7F;
	// P42 P44 P45
	P4M1 &= 0xCB;
	P4M0 &= 0xCB;
	
}