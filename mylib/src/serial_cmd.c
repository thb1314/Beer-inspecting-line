#include "mytype.h"
#include <STC15F2K60S2.H>
#include "serial_cmd.h"

/******************************************************************* 
 *  Copyright(c) 2016 THB-CCUT  
 *  All rights reserved. 
 *   
 *  文件名称: serail_cmd.c
 *  简要描述: 串口发送与接收
 *   
 *  创建日期: 2016-11-12
 *  作者: THB
 *  说明: 在ROM中定义一些协议字段
 *		  
 *   
 *  修改日期: 
 *  作者: 
 *  说明: 
 ******************************************************************/ 
 
u8 code CMD_TEST[PROTOCOL_LENGTH] = {CMD_BYTE_HEADER,CMD_COM_TEST,0x00,0x00,0x00,CMD_COM_TEST};
//volatile SERIAL_CMD serial_cmd_struct;
 
