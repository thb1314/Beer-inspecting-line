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
#define CMD_SENSOR_TRIGGERED    	0x0B        //传感器触发

#define SENSOR1             0x01        //传感器1编号
#define SENSOR2             0x02        //传感器2编号
#define SENSOR3             0x03        //传感器3编号
#define SENSOR4             0x04        //传感器4编号
#define SENSOR5             0x05        //传感器5编号

#define TRANS1              0x01        //传送带1编号
#define TRANS2              0x02        //传送带2编号
#define TRANS3              0x03        //传送带3编号

#define _OK					0x05		//返回值，表示正确
#define _NG					0x06		//返回值，表示错误


extern u8 code CMD_TEST[PROTOCOL_LENGTH];
extern u8 code CMD_TEST_RE[PROTOCOL_LENGTH];
extern u8 code CMD_CLOSE_PC[PROTOCOL_LENGTH];
extern u8 code CMD_CLOSE_PC_RE_OK[PROTOCOL_LENGTH];
extern u8 code CMD_CLOSE_PC_RE_FAIL[PROTOCOL_LENGTH];

extern u8 code CMD_TSTART_INSPECTING[PROTOCOL_LENGTH];
extern u8 code CMD_TSTOP_INSPECTING[PROTOCOL_LENGTH];

extern u8 code CMD_FORCE_STARTUP[PROTOCOL_LENGTH];
extern u8 code CMD_FORCE_STARTUP_RE_OK[PROTOCOL_LENGTH];


extern u8 code CMD_SENSOR1_TRIGGER[PROTOCOL_LENGTH];
extern u8 code CMD_SENSOR2_TRIGGER[PROTOCOL_LENGTH];
extern u8 code CMD_SENSOR3_TRIGGER[PROTOCOL_LENGTH];
extern u8 code CMD_SENSOR4_TRIGGER[PROTOCOL_LENGTH];
extern u8 code CMD_SENSOR5_TRIGGER[PROTOCOL_LENGTH];
typedef struct 
{
	u16 header;
	u8 cmd;
	u8 election;
	u8 dat[2];
	u8 check_sum;
} SERIAL_CMD;

typedef union 
{
	SERIAL_CMD serial_struct;
	u8 dat[PROTOCOL_LENGTH];
} U_SERIAL_CMD;


typedef union 
{
	u8 dat8[2];
	u16 dat16;
} U_SERIAL_CMD_DAT;


//extern volatile SERIAL_CMD serial_cmd_struct;

//u8 SERIAL_CMD_STRUCT_Init(u8*);
#endif