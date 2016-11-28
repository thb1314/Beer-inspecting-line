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
u8 code CMD_TEST_RE[PROTOCOL_LENGTH] = {CMD_BYTE_HEADER,CMD_COM_TEST,_OK,0x00,0x00,CMD_COM_TEST+_OK};


// CLOSE PC
u8 code CMD_CLOSE_PC[PROTOCOL_LENGTH] = {CMD_BYTE_HEADER,CMD_CLOSE_SYSTEM,0x00,0x00,0x00,CMD_CLOSE_SYSTEM};
u8 code CMD_CLOSE_PC_RE_OK[PROTOCOL_LENGTH] = {CMD_BYTE_HEADER,CMD_CLOSE_SYSTEM,_OK,0x00,0x00,CMD_CLOSE_SYSTEM+_OK};
u8 code CMD_CLOSE_PC_RE_FAIL[PROTOCOL_LENGTH] = {CMD_BYTE_HEADER,CMD_CLOSE_SYSTEM,_NG,0x00,0x00,CMD_CLOSE_SYSTEM+_NG};


u8 code CMD_TSTOP_INSPECTING[PROTOCOL_LENGTH] = {CMD_BYTE_HEADER,CMD_STOP_INSPECT,0x00,0x00,0x00,CMD_STOP_INSPECT};
u8 code CMD_TSTART_INSPECTING[PROTOCOL_LENGTH] = {CMD_BYTE_HEADER,CMD_START_INSPECT,0x00,0x00,0x00,CMD_START_INSPECT};


u8 code CMD_FORCE_STARTUP[PROTOCOL_LENGTH] = {CMD_BYTE_HEADER,CMD_START,0x00,0x00,0x00,CMD_START};

u8 code CMD_FORCE_STARTUP_RE_OK[PROTOCOL_LENGTH] = {CMD_BYTE_HEADER,CMD_START,_OK,0x00,0x00,CMD_START+_OK};
// volatile SERIAL_CMD serial_cmd_struct;
 



