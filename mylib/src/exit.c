#include "exit.h"
#include "myport.h"
#include "delay.h"
#include <STC15F2K60S2.H>


void InitExit(void)
{
	//开启外部中断0 1 2 3
	IT0 = 1;
	EX0 = 1;
	
	//外部中断 1
	IT1 = 1;
	EX1 = 1;
	
	// 使能外部中断 2
	INT_CLKO |= 0x10;
	
	// 使能外部中断 3
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
	//如果和状态和原来的不同 说明是干扰
	if(tmp != temp_btn_state)
		return;
	//更新按键状态
	button_state = tmp;
	SET_BTN_UPDATE(button_state);
}
// 关机按钮进外部中断2
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
	//如果和状态和原来的不同 说明是干扰
	if(tmp != temp_btn_state)
		return;
	//更新按键状态
	button_state = tmp;
	SET_BTN_UPDATE(button_state);

}

