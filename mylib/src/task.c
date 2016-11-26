#include "task.h"
#include "uart.h"


volatile TaskBuffer taskbuffer = {
	0,{0x00}
};

u8 TaskInit(Task* mytask)
{
	if(taskbuffer.length < MAX_TASK_NUM) 
	{
		taskbuffer.task[taskbuffer.length] = mytask;
		mytask->id = taskbuffer.length;
		mytask->_timer = 0;
		taskbuffer.length++;
		return taskbuffer.length;
	}
	else
	{
		return 0;
	}
}

u8 TaskDelete(Task* mytask)
{
	u8 i = 0;
	u8 tmp = (taskbuffer.length - 1);
			
	if(mytask->id >= MAX_TASK_NUM)
		return MAX_TASK_NUM;
	// MAX_TASK_NUM 是一个错误标志
	if(0 == taskbuffer.length)
		return MAX_TASK_NUM;
	//如果是在末尾
	if(mytask->id == tmp)
	{
		taskbuffer.task[tmp] = 0;
		
	}
	else
	{


		for(i = mytask->id;i < tmp; i++)
		{
			
			taskbuffer.task[i] = taskbuffer.task[i+1];
			//更新任务ID
			taskbuffer.task[i]->id = i;
			
		}
		
	}
	mytask->id = MAX_TASK_NUM;
	
	taskbuffer.length--;
	
	return taskbuffer.length;
	
	
	
	
}


