#ifndef __SERIAL_CMD_H
#define __SERIAL_CMD_H

#include "mytype.h"

#define PROTOCOL_LENGTH (7)

#define CMD_BYTE_HEADER				0x55,0xAA

#define CMD_CLOSE_SYSTEM    		0x00        //�ر�ϵͳ
#define CMD_START           		0x01        //��ʼǿ������
#define CMD_STOP            		0x02        //ֹͣǿ������
#define CMD_COM_TEST        		0x03        //ͨѶ�Լ�
#define CMD_SENSORS_TEST    		0x04        //�������Լ�
#define CMD_TRANS_TEST      		0x05        //����ϵͳ�Լ�
#define CMD_START_INSPECT   		0x07        //��ʼ���
#define CMD_STOP_INSPECT    		0x08        //ֹͣ���
#define CMD_SENSOR_DELAY    		0x09        //���ô������ӳ�
#define CMD_TRANS_SPEED     		0x0A        //���ô��ʹ��ٶ�
#define CMD_SENSOR_TRIGGERED    		0x00        //�ر�ϵͳ

#define SENSOR1             0x01        //������1���
#define SENSOR2             0x02        //������2���
#define SENSOR3             0x03        //������3���
#define SENSOR4             0x04        //������4���
#define SENSOR5             0x05        //������5���

#define TRANS1              0x01        //���ʹ�1���
#define TRANS2              0x02        //���ʹ�2���
#define TRANS3              0x03        //���ʹ�3���



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