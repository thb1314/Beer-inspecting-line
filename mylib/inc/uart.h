#ifndef __UART_H__
#define __UART_H__
/******************************************************************* 
 *  Copyright(c) 2016 THB-CCUT  
 *  All rights reserved. 
 *   
 *  文件名称: uart.h
 *  简要描述: 串口发送与接收
 *   
 *  创建日期: 2016-11-12
 *  作者: THB
 *  说明: 光棍节后开始写的，将串口一的波特率和串口二的波特率设置为一样
 *        这样串口一和串口二就共用定时器二
 *		  
 *   
 *  修改日期: 2016-11-20
 *  作者: 
 *  说明: 增加了RS485和接收一帧数据
 ******************************************************************/ 
#include "myfosc.h"
#include "myport.h"


#define UART1
//#define UART2



#define UART_BAUDRATE   57600       // set 
// 一组数据帧超时时间基准
#define UART_DATA_TIMEOUT 5


#ifdef UART2

// UART2用作485
#define UART2_USE_RS485
#define UART2_RS485_CTL_PORT O_RS485_CTL_2


/*Define UART parity mode*/
#define UART2_NONE_PARITY 0
#define UART2_ODD_PARITY 1
#define UART2_EVEN_PARITY 2
#define UART2_MARK_PARITY 3
#define UART2_SPACE_PARITY 4
#define UART2_PARITYBIT UART2_NONE_PARITY

#define UART2_MAX_COMCHAR_LEN 8

#define S2RI 0x01		// S2CON.0
#define S2TI 0x02		// S2CON.1
#define S2RB8 0x04		// S2CON.2
#define S2TB8 0x08		// S2CON.3


extern bit uart2_bit9;
extern bit uart2_flagRxd; 

extern volatile unsigned char uart2_cntRxd;
extern volatile unsigned char uart2_t_cntRxd;
extern unsigned char uart2_bufRxd[UART2_MAX_COMCHAR_LEN];
extern bit uart2_is_start_check_timer;


/**
 * 串口初始化设置
 * return void
 */
extern void Uart2Init(void);

/**
 * 串口2接收中断函数
 * return void 
 */
extern void Uart2Rcv(void);
extern void Uart2Write(unsigned char *, unsigned char);



#endif


#ifdef UART1




// UART1用作485
#define UART1_USE_RS485
#define UART1_RS485_CTL_PORT O_RS485_CTL_1


/*Define UART parity mode*/
#define UART1_NONE_PARITY 0
#define UART1_ODD_PARITY 1
#define UART1_EVEN_PARITY 2
#define UART1_MARK_PARITY 3
#define UART1_SPACE_PARITY 4
#define UART1_PARITYBIT UART1_NONE_PARITY

#define UART1_MAX_COMCHAR_LEN 8



extern bit uart1_bit9;
extern bit uart1_flagRxd; 
extern bit uart1_is_start_check_timer;

extern volatile unsigned char uart1_cntRxd;
extern volatile unsigned char uart1_t_cntRxd;

extern unsigned char uart1_bufRxd[UART1_MAX_COMCHAR_LEN];



/**
 * 串口初始化设置
 * return void
 */
extern void Uart1Init(void);

/**
 * 串口1接收中断函数
 * return void 
 */
extern void Uart1Rcv(void);
extern void Uart1Write(unsigned char *, unsigned char);

#endif


#endif