#include "myport.h"
#include "mytype.h"
#include "tim.h"
#include <STC15F2K60S2.H>


bit is_start_check_close_btn = 0;

void InitTimer0()
{
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	
	TL0 = (u8)T0MS;		//���ö�ʱ��ֵ
	TH0 = (u8)(T0MS >> 8);		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־

}


void tim0_isr(void) interrupt 1
{
	if(is_start_check_close_btn)
	{
		CheckIsClose();
	}
}
