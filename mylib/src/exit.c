#include "exit.h"
#include "myport.h"
#include "delay.h"
#include <STC15F2K60S2.H>


void InitExit(void)
{
	//�����ⲿ�ж�0 1 2 3
	IT0 = 1;
	EX0 = 1;
	
	//�ⲿ�ж� 1
	IT1 = 1;
	EX1 = 1;
	
	// ʹ���ⲿ�ж� 2
	INT_CLKO |= 0x10;
	
	// ʹ���ⲿ�ж� 3
	INT_CLKO |= 0x20;
	
}

void exint3() interrupt 11
{
	u8 tmp = NO_BTN_DOWN;
	u8 temp_btn_state = NO_BTN_DOWN;
	if(B_IS_START_BTN_DOWN())
	{
		temp_btn_state = START_BTN_DOWN;
	}
	if((button_state&(~BTN_UPDATE)) == temp_btn_state) 
		return;
	delay_ms(5);
	if(B_IS_START_BTN_DOWN())
	{
		tmp = START_BTN_DOWN;
	}
	//�����״̬��ԭ���Ĳ�ͬ ˵���Ǹ���
	if(tmp != temp_btn_state)
		return;
	//���°���״̬
	button_state = tmp;
	SET_BTN_UPDATE(button_state);
}
// �ػ���ť���ⲿ�ж�2
void exint2() interrupt 10
{
	u8 tmp = NO_BTN_DOWN;
	u8 temp_btn_state = NO_BTN_DOWN;


	if(B_IS_CLOSE_BTN_DOWN())
	{
		temp_btn_state = CLOSE_BTN_DOWN;
	}
	delay_ms(5);
	if(B_IS_CLOSE_BTN_DOWN())
	{
		tmp = CLOSE_BTN_DOWN;
	}
	//�����״̬��ԭ���Ĳ�ͬ ˵���Ǹ���
	if(tmp != temp_btn_state)
		return;
	//���°���״̬
	button_state = tmp;
	SET_BTN_UPDATE(button_state);

}

