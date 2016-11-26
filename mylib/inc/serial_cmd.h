#ifndef __SERIAL_CMD_H
#define __SERIAL_CMD_H

#include "mytype.h"

#define PROTOCOL_LENGTH (7)

#define CMD_BYTE_HEADER				0x55,0xAA

#define CMD_CLOSE_SYSTEM    		0x00        //关闭系统
#define CMD_START           		0x01        //开始强制输送
#define CMD_STOP            		0x02        //停止强制输送
#define CMD_COM_TEST        		0x03        //通讯自检
#define CMD_SENSORS_TEST    		0x04        //传感器自检
#define CMD_TRANS_TEST      		0x05        //传动系统自检
#define CMD_START_INSPECT   		0x07        //开始检测
#define CMD_STOP_INSPECT    		0x08        //停止检测
#define CMD_SENSOR_DELAY    		0x09        //设置传感器延迟
#define CMD_TRANS_SPEED     		0x0A        //设置传送带速度
#define CMD_SENSOR_TRIGGERED    		0x00        //关闭系统

#define SENSOR1             0x01        //传感器1编号
#define SENSOR2             0x02        //传感器2编号
#define SENSOR3             0x03        //传感器3编号
#define SENSOR4             0x04        //传感器4编号
#define SENSOR5             0x05        //传感器5编号

#define TRANS1              0x01        //传送带1编号
#define TRANS2              0x02        //传送带2编号
#define TRANS3              0x03        //传送带3编号



extern u8 code CMD_TEST[PROTOCOL_LENGTH];
 
typedef struct 
{
	u16 header;
	u8 cmd;
	u8 election;
	u16 dat;
	u8 check_sum;
} SERIAL_CMD;

typedef union 
{
	SERIAL_CMD serial_struct;
	u8 dat[7];
} U_SERIAL_CMD;

//extern volatile SERIAL_CMD serial_cmd_struct;

//u8 SERIAL_CMD_STRUCT_Init(u8*);
#endif