#include "uart.h"
#include "mytype.h"
#include <STC15F2K60S2.H>


bit is_set_tim2 = 0;

#ifdef UART1




bit	uart1_bit9 = 0;
bit uart1_flagRxd = 0; 
unsigned char uart1_bufRxd[UART1_MAX_COMCHAR_LEN] = {0x00}; //串口接收缓冲区
volatile unsigned char uart1_cntRxd = 0;
#endif
#ifdef UART2

bit	uart2_bit9 = 0;
bit uart2_flagRxd = 0; 
unsigned char uart2_bufRxd[UART2_MAX_COMCHAR_LEN] = {0x00}; //串口接收缓冲区
volatile unsigned char uart2_cntRxd = 0;

#endif


#ifdef UART1
void Uart1Init()  //串口配置函数，baud为波特率
{
		// 设定串口优先级为高优先级
		// PS = 1;
	
		#if (UART1_PARITYBIT == UART1_NONE_PARITY)
		SCON |= 0x50;	//	8-bit varaible UART
		#elif (UART1_PARITYBIT == UART1_ODD_PARITY) || (UART1_PARITYBIT == UART1_EVEN_PARITY) || (UART1_PARITYBIT == UART1_MARK_PARITY)
		SCON |= 0xDA;	//	9-bit varaible UART,parity bit initial to 1
		#elif (UART1_PARITYBIT == UART1_SPACE_PARITY)
		SCON |= 0xD5;	//	9-bit varaible UART,parity bit initial to 0
		#endif
		
		if(!is_set_tim2)
		{
			T2L = (u8)( 65536 - (FOSC/4/UART_BAUDRATE) );
			T2H = (u8)(( 65536 - (FOSC/4/UART_BAUDRATE) )>>8);
			AUXR |= 0x04;		// T2为1T模式
			AUXR |= 0x10;		// 启动定时器2
			is_set_tim2 = 1;
		}
		
		
		
		AUXR |= 0x01;		//选择定时器2作为串口1的波特率发生器
		
		ES = 1;	//Enable UART interrupt
		
}
void Uart1Write(unsigned char *buf, unsigned char len)
{
	while(len)
	{
		ACC = *(buf++);
		if(P)
		{
		#if (UART1_PARITYBIT == UART1_ODD_PARITY)
			TB8 = 0;
		#elif (UART1_PARITYBIT == UART1_EVEN_PARITY)
			TB8 = 1;
		#endif
		}
		else
		{
		#if (UART1_PARITYBIT == UART1_ODD_PARITY)
			TB8 = 1;
		#elif (UART1_PARITYBIT == UART1_EVEN_PARITY)
			TB8 = 0;
		#endif
		}
		SBUF = ACC;
		while(!TI);
		TI = 0;
		len--;
	}
}


void Uart1Rcv() interrupt 4
{
	if(RI)
	{
		
		RI = 0;
		if (uart1_cntRxd < UART1_MAX_COMCHAR_LEN) 
		//接收缓冲区尚未用完时，
		{    
			//保存接收字节，并递增计数器
			uart1_bufRxd[uart1_cntRxd++] = SBUF;
		}

		//uart1_flagRxd = 1;
		uart1_bit9 = RB8;
	}
}

#endif

#ifdef UART2


void Uart2Init(void)
{
	#if (UART2_PARITYBIT == UART2_NONE_PARITY)
	S2CON = 0x50;	//	8-bit varaible UART
	#elif (UART2_PARITYBIT == UART2_ODD_PARITY) || (UART2_PARITYBIT == UART2_EVEN_PARITY) || (UART2_PARITYBIT == UART2_MARK_PARITY)
	S2CON = 0xDA;	//	9-bit varaible UART,parity bit initial to 1
	#elif (UART2_PARITYBIT == UART2_SPACE_PARITY)
	S2CON = 0xD5;	//	9-bit varaible UART,parity bit initial to 0
	#endif

		
	if(!is_set_tim2)
	{
		T2L = (u8)( 65536 - (FOSC/4/UART_BAUDRATE) );
		T2H = (u8)(( 65536 - (FOSC/4/UART_BAUDRATE) )>>8);
		AUXR |= 0x04;		// T2为1T模式
		AUXR |= 0x10;		// 启动定时器2
		is_set_tim2 = 1;
	}
	
	IE2 |= 0x01;	//使能串口2中断
	
	
}

void Uart2Rcv() interrupt 8
{
	if(S2CON & S2RI)
	{
		S2CON &= ~S2RI;
		if (uart2_cntRxd < UART2_MAX_COMCHAR_LEN) 
		//接收缓冲区尚未用完时，
		{    
			//保存接收字节，并递增计数器
			uart2_bufRxd[uart2_cntRxd++] = S2BUF;
		}

		uart2_bit9 =(S2CON & S2RB8);
	}
}

void Uart2Write(unsigned char *buf, unsigned char len)
{
	while (len)   //循环发送所有字节
	{
		ACC = *(buf++);
		if(P)
		{
			
		#if (UART2_PARITYBIT == UART2_ODD_PARITY)
			S2CON &= ~S2TB8;	// set parity bit to 0
		#elif (UART2_PARITYBIT == UART2_EVEN_PARITY)
			S2CON |= S2TB8;		// set parity bit to 1
		#endif

		}
		else
		{
		#if (UART2_PARITYBIT == UART2_ODD_PARITY)
			S2CON |= S2TB8;		// set parity bit to 1
		#elif (UART2_PARITYBIT == UART2_EVEN_PARITY)
			S2CON &= ~S2TB8;		// set parity bit to 1
		#endif
		}
		S2BUF = ACC;
		while((S2CON & S2TI)==0);
		S2CON &= ~S2TI;
		len--;
	}
}

#endif

