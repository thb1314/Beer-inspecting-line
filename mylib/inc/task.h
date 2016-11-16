#ifndef __TASK_H_
#define __TASK_H_

/******************************************************************* 
 *  Copyright(c) 2016 THB-CCUT  
 *  All rights reserved. 
 *   
 *  文件名称: task.h
 *  简要描述: 任务操作库
 *   
 *  创建日期: 2016-11-08
 *  作者: THB
 *  说明: 任务（定时、延时）相关操作库
 *   
 *  修改日期: 
 *  作者: 
 *  说明: 
 ******************************************************************/ 

#include "mytype.h"

#define DELAY_TASK 0
#define TIME_TASK  1

#define MAX_TASK_NUM 8


typedef struct myTask{
	u8 isstart;
	u8 type;
	u16	timer;
	u16 _timer;
	void (*function)(void*);
	u8 id;
	
} Task;

typedef struct myTaskBuffer {
	u8 length;
	Task* task[MAX_TASK_NUM];
} TaskBuffer;

extern u8 TaskInit(Task*);
extern TaskBuffer taskbuffer;
extern u8 TaskDelete(Task*);
#endif




