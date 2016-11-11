#include "myport.h"
#include "mytype.h"
#include "tim.h"
#include <STC15F2K60S2.H>


bit is_start_check_close_btn = 0;

void InitTimer0()
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	
	TL0 = (u8)T0MS;		//设置定时初值
	TH0 = (u8)(T0MS >> 8);		//设置定时初值
	TF0 = 0;		//清除TF0标志

}


void tim0_isr(void) interrupt 1
{
	if(is_start_check_close_btn)
	{
		CheckIsClose();
	}
}
