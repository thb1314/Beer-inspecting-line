/******************************************************************* 
 *  Copyright(c) 2016 THB-CCUT  
 *  All rights reserved. 
 *   
 *  文件名称: event.h
 *  简要描述: 事件处理器
 *   
 *  创建日期: 2016-11-08
 *  作者: THB
 *  说明: 
 *   
 *  修改日期: 
 *  作者: 
 *  说明: 
 ******************************************************************/
#ifndef __EVENT_H__
#define __EVENT_H__
#include "mytype.h"
//事件处理机制
// 事件标志位
extern volatile u16 event;
// 事件标志的定义
 
typedef enum  {
	NO_EVENT = 0x0000,
	START_SYS_EVENT = 0x0001,
	STOP_SYS_EVENT = 0x0002,
	FORCE_START_SYS_EVENT = 0x0004,
	FORCE_STOP_SYS_EVENT = 0x0008,
	CLOSE_SYS_EVENT = 0x0010,
} EventType;

//置位事件
#define SET_Event(event_type) (event |= event_type)
//清除时间
#define CLR_Event(event_type) (event &= ~event_type)
//判断事件状态
#define IS_Event_Valid(event_type) (event & event_type)
extern void UpdateEvent(void);
extern void HandleEvent(void);
#endif
