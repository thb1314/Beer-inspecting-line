/******************************************************************* 
 *  Copyright(c) 2016 THB-CCUT  
 *  All rights reserved. 
 *   
 *  �ļ�����: event.h
 *  ��Ҫ����: �¼�������
 *   
 *  ��������: 2016-11-08
 *  ����: THB
 *  ˵��: 
 *   
 *  �޸�����: 
 *  ����: 
 *  ˵��: 
 ******************************************************************/
#ifndef __EVENT_H__
#define __EVENT_H__
#include "mytype.h"
//�¼��������
// �¼���־λ
extern volatile u16 event;
// �¼���־�Ķ���
 
typedef enum  {
	NO_EVENT = 0x0000,
	START_SYS_EVENT = 0x0001,
	STOP_SYS_EVENT = 0x0002,
	FORCE_START_SYS_EVENT = 0x0004,
	FORCE_STOP_SYS_EVENT = 0x0008,
	CLOSE_SYS_EVENT = 0x0010,
} EventType;

//��λ�¼�
#define SET_Event(event_type) (event |= event_type)
//���ʱ��
#define CLR_Event(event_type) (event &= ~event_type)
//�ж��¼�״̬
#define IS_Event_Valid(event_type) (event & event_type)
extern void UpdateEvent(void);
extern void HandleEvent(void);
#endif
