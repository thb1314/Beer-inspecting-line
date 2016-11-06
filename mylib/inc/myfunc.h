#ifndef __MYFUNC_H_
#define __MYFUNC_H_

/******************************************************************* 
 *  Copyright(c) 2016 THB-CCUT  
 *  All rights reserved. 
 *   
 *  �ļ�����: myfunc.h
 *  ��Ҫ����: ����һЩ����IO�����ĺ�
 *   
 *  ��������: 2016-11-06
 *  ����: THB
 *  ˵��: 
 *   
 *  �޸�����: 
 *  ����: 
 *  ˵��: 
 ******************************************************************/


// ����һЩ���ݴ���
#define GET_LOW_8BIT(x) (u8(x))
#define GET_HIGH_8BIT(x) (u8(x >> 8))

// ����IO�ڵĸߵ͵�ƽ���ж�
#define SET_PORT(x)		(x)=1
#define CLR_PORT(x)		(x)=0
#define IS_LOW(x)		(0 == (x))
#define IS_HIGH(x)		(1 == (x))
#define WATE_FOR_HIGH	while(IS_LOW(x))
#define WATE_FOR_LOW	while(IS_HIGH(x))
	
#endif