/******************************************************************* 
 *  Copyright(c) 2016 THB-CCUT  
 *  All rights reserved. 
 *   
 *  �ļ�����: main.c
 *  ��Ҫ����: �������ļ�
 *   
 *  ��������: 2016-11-06
 *  ����: THB
 *  ˵��: 
 *   
 *  �޸�����: 
 *  ����: 
 *  ˵��: 
 ******************************************************************/
#include <STC15F2K60S2.H>
#include "main.h"
#include "myfunc.h"
#include "myport.h"
#include "mytype.h"
#include "serial_cmd.h"
 
//ע��: STC15W4K32S4ϵ�е�оƬ,�ϵ��������PWM��ص�IO�ھ�Ϊ
//      ����̬,�轫��Щ������Ϊ׼˫��ڻ�ǿ����ģʽ��������ʹ��
//���IO: P0.6/P0.7/P1.6/P1.7/P2.1/P2.2
//        P2.3/P2.7/P3.7/P4.2/P4.4/P4.5 


void main()
{
	SystenInit();
	while(1)
	{
		
	}
}



// ϵͳ��ʼ������
void SystenInit(void)
{

	
	
	InitPort();
	
}