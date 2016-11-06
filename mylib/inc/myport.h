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


// 入口光电
#define I_GATE_PHOTOELECTRIC_SENSOR		P00
// 计数光电
#define I_COUNT_PHOTOELECTRIC_SENSOR	P33
// 剔除废品光电
#define I_FILTER_PHOTOELECTRIC_SENSOR	P01
// 阻塞光电
#define I_BLOCK_PHOTOELECTRIC_SENSOR	P02

// 门开报警信号
#define I_GATE_OPEN_WARNING				P32
// 关机信号
#define I_CLOSE_SINGAL					P36
// 开机信号
#define I_OPEN_SINGAL					P37
// 强制启动信号
#define I_FORCE_START_SINGAL			P05
// 停止按键（对应于开始或强制启动）
#define I_STOP_SINGAL					P20
// 射线源打开检查
#define I_ray_OPEN







#endif