/******************************************************************* 
 *  Copyright(c) 2016 THB-CCUT  
 *  All rights reserved. 
 *   
 *  �ļ�����: myport.h
 *  ��Ҫ����: ������һЩMCU��IO�ڵĹ��ܣ���Ҫ������ʲô��
 *   
 *  ��������: 2016-11-06
 *  ����: THB
 *  ˵��: I������ǰ׺ OΪ���ǰ׺
 *   
 *  �޸�����: 
 *  ����: 
 *  ˵��: 
 ******************************************************************/ 

 
#ifndef __MYPORT_H_
#define __MYPORT_H_


// ��ڹ��
#define I_GATE_PHOTOELECTRIC_SENSOR		P00
// �������
#define I_COUNT_PHOTOELECTRIC_SENSOR	P33
// �޳���Ʒ���
#define I_FILTER_PHOTOELECTRIC_SENSOR	P01
// �������
#define I_BLOCK_PHOTOELECTRIC_SENSOR	P02

// �ſ������ź�
#define I_GATE_OPEN_WARNING				P32
// �ػ��ź�
#define I_CLOSE_SINGAL					P36
// �����ź�
#define I_OPEN_SINGAL					P37
// ǿ�������ź�
#define I_FORCE_START_SINGAL			P05
// ֹͣ��������Ӧ�ڿ�ʼ��ǿ��������
#define I_STOP_SINGAL					P20
// ����Դ�򿪼��
#define I_RAY_OPEN_CHECK				P21
// ��ͣ����
#define I_FORCE_STOP_SINGAL				P22

// ����Դ���ؿ��ƶˣ��͵�ƽ�򲻿���
#define O_RAY_CONTROL					P23


// 485���ƶ�1
#define O_485_DIR1						P44
// 485���ƶ�2
#define O_485_DIR2						P45
// �߷���
#define O_FILTER_MOTOR_BACK				P60
// �߷Ͻ�
#define O_FILTER__MOTOR_FORWARD			P61
// �ػ��ź�������̵�����
#define O_CLOSE_SYSTEM					P62
//	һ���������						
#define O_FIRST_ALARM_WARNING			P63
// ֹͣ����
#define O_STOP_DELIVER					P64
// �������
#define O_RAY_OUTPUT					P65
// ������
#define O_START_DELIVER					P66
// �������Դ���
#define O_RECEIVEBOX_POWER_OUTPUT		P67
// �����������
#define O_SECOND_ALARM_WARNING			P70




// ������һЩ����IO�����Ķ���
#define BTN_IS_OPEN()			IS_LOW(I_OPEN_SINGAL)
#define BTN_IS_FORCE_OPEN()		IS_LOW(I_FORCE_START_SINGAL)



// ����IO��״̬
#define NO_BTN_DOWN		0x00
#define START_BTN_DOWN	0x01
#define STOP_BTN_DOWN	0x02
#define FORCE_START_BTN_DOWN 0x03
#endif