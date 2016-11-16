#ifndef __TASK_H_
#define __TASK_H_

/******************************************************************* 
 *  Copyright(c) 2016 THB-CCUT  
 *  All rights reserved. 
 *   
 *  �ļ�����: task.h
 *  ��Ҫ����: ���������
 *   
 *  ��������: 2016-11-08
 *  ����: THB
 *  ˵��: ���񣨶�ʱ����ʱ����ز�����
 *   
 *  �޸�����: 
 *  ����: 
 *  ˵��: 
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




