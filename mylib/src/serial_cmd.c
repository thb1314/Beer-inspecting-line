#include "mytype.h"
#include <STC15F2K60S2.H>
#include "serial_cmd.h"

/******************************************************************* 
 *  Copyright(c) 2016 THB-CCUT  
 *  All rights reserved. 
 *   
 *  �ļ�����: serail_cmd.c
 *  ��Ҫ����: ���ڷ��������
 *   
 *  ��������: 2016-11-12
 *  ����: THB
 *  ˵��: ��ROM�ж���һЩЭ���ֶ�
 *		  
 *   
 *  �޸�����: 
 *  ����: 
 *  ˵��: 
 ******************************************************************/ 
 
u8 code CMD_TEST[PROTOCOL_LENGTH] = {CMD_BYTE_HEADER,CMD_COM_TEST,0x00,0x00,0x00,CMD_COM_TEST};
//volatile SERIAL_CMD serial_cmd_struct;
 
