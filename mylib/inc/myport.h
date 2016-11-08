/******************************************************************* 
 *  Copyright(c) 2016 THB-CCUT  
 *  All rights reserved. 
 *   
 *  文件名称: myport.h
 *  简要描述: 定义了一些MCU的IO口的功能（主要用于做什么）
 *   
 *  创建日期: 2016-11-06
 *  作者: THB
 *  说明: I是输入前缀 O为输出前缀
 *   
 *  修改日期: 
 *  作者: 
 *  说明: 
 ******************************************************************/ 

 
#ifndef __MYPORT_H_
#define __MYPORT_H_


#include "mytype.h"

#include "myfunc.h"
// 入口光电
#define I_GATE_PHOTOELECTRIC_SENSOR		P00
// 计数光电(外部中断1)
#define I_COUNT_PHOTOELECTRIC_SENSOR	P33
// 剔除废品光电
#define I_FILTER_PHOTOELECTRIC_SENSOR	P01
// 阻塞光电
#define I_BLOCK_PHOTOELECTRIC_SENSOR	P02

// 门开报警信号(外部中断0)
#define I_GATE_OPEN_WARNING				P32
// 关机信号(外部中断2)
#define I_CLOSE_SINGAL					P36
// 开机信号(外部中断3)
#define I_OPEN_SINGAL					P37
// 强制启动信号
#define I_FORCE_START_SINGAL			P05
// 停止按键（对应于开始或强制启动）
#define I_STOP_SINGAL					P20
// 射线源打开检查
#define I_RAY_OPEN_CHECK				P21
// 急停按键
#define I_FORCE_STOP_SINGAL				P22

// 射线源开关控制端（低电平打不开）
#define O_RAY_CONTROL					P23


// 485控制端1
#define O_485_DIR1						P44
// 485控制端2
#define O_485_DIR2						P45
// 踢废退
#define O_FILTER_MOTOR_BACK				P60
// 踢废进
#define O_FILTER__MOTOR_FORWARD			P61
// 关机信号输出（继电器）
#define O_CLOSE_SYSTEM					P62
//	一级报警输出						
#define O_FIRST_ALARM_WARNING			P63
// 停止输送
#define O_STOP_DELIVER					P64
// 射线输出
#define O_RAY_OUTPUT					P65
// 开输送
#define O_START_DELIVER					P66
// 接收箱电源输出
#define O_RECEIVEBOX_POWER_OUTPUT		P67
// 二级报警输出
#define O_SECOND_ALARM_WARNING			P70




// 下面是一些关于IO动作的定义
#define B_IS_START_BTN_DOWN()			IS_LOW(I_OPEN_SINGAL)
#define B_IS_FORCE_START_BTN_DOWN()		IS_LOW(I_FORCE_START_SINGAL)
#define B_IS_STOP_BTN_DOWN()			IS_LOW(I_STOP_SINGAL)
#define B_IS_FORCE_STOP_BTN_DOWN()		IS_LOW(I_FORCE_STOP_SINGAL)
#define B_IS_CLOSE_BTN_DOWN()			IS_LOW(I_CLOSE_SINGAL)

// 按钮状态标志位
#define NO_BTN_DOWN				0x00
#define START_BTN_DOWN			0x01
#define STOP_BTN_DOWN			0x02
#define FORCE_START_BTN_DOWN	0x04
#define FORCE_STOP_BTN_DOWN		0x08
#define CLOSE_BTN_DOWN			0x10
#define BTN_UPDATE				0x80

#define IS_BTN_UPDATE(x)			((x)&BTN_UPDATE)					
#define CLR_BTN_UPDATE(x)		((x) &= ~BTN_UPDATE)
#define SET_BTN_UPDATE(x)		((x) |= BTN_UPDATE)



// 系统按钮状态标志
extern volatile u8 button_state;
//检测按钮状态
extern void CheckBtn(void);
//初始化端口
extern void InitPort(void);
#endif