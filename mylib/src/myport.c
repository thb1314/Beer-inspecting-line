#include "myport.h"
 
u8 button_state = NO_BTN_DOWN; 
bit is_btn_state_update button_state^7;
u8 temp_state = NO_BTN_DOWN;
// 初始化端口
void InitPort(void)
{
	//注意: STC15W4K32S4系列的芯片,上电后所有与PWM相关的IO口均为
	//      高阻态,需将这些口设置为准双向口或强推挽模式方可正常使用
	//相关IO: P0.6/P0.7/P1.6/P1.7/P2.1/P2.2
	//        P2.3/P2.7/P3.7/P4.2/P4.4/P4.5
	
	// 配置相关IO口为准双向口
	// P06 P07 准双向口
	P0M1 &= 0x3F;
	P0M0 &= 0x3F;
	// P16 P17 准双向口
	P1M1 &= 0x3F;
	P1M0 &= 0x3F;
	// P21 P22 P23 P27 准双向口
	P2M1 &= 0x71;
	P2M0 &= 0x71;
	// P37 准双向口
	P3M1 &= 0x7F;
	P3M0 &= 0x7F;
	// P42 P44 P45
	P4M1 &= 0xCB;
	P4M0 &= 0xCB;
	
	//初始化按钮状态
	button_state = NO_BTN_DOWN;
}

// 检测按钮状态 可以防止重复按下
void CheckBtn(void)
{
	if(B_IS_START_BTN_DOWN())
	{
		temp_state = START_BTN_DOWN;
		
	}
	else if( B_IS_STOP_BTN_DOWN())
	{
		temp_state = STOP_BTN_DOWN;
	}
	else if(B_IS_FORCE_START_BTN_DOWN())
	{
		temp_state = FORCE_START_BTN_DOWN;
	}
	else if(B_IS_FORCE_STOP_BTN_DOWN())
	{
		temp_state = FORCE_STOP_BTN_DOWN;
	}
	else if( B_IS_CLOSE_BTN_DOWN())
	{
		temp_state = CLOSE_BTN_DOWN;
	}
	else
	{
		// 没有按键按下
		return;
	}
	//可能会有按键按下
	//取消之前的按键更新
	CLR_BTN_UPDATE();
	if(button_state == temp_state) 
		return;
	// 延时消抖
	delay_ms(10);
	if(B_IS_START_BTN_DOWN())
	{
		button_state = START_BTN_DOWN;
		
	}
	else if( B_IS_STOP_BTN_DOWN())
	{
		button_state = STOP_BTN_DOWN;
	}
	else if(B_IS_FORCE_START_BTN_DOWN())
	{
		button_state = FORCE_START_BTN_DOWN;
	}
	else if(B_IS_FORCE_STOP_BTN_DOWN())
	{
		button_state = FORCE_STOP_BTN_DOWN;
	}
	else if( B_IS_CLOSE_BTN_DOWN())
	{
		button_state = CLOSE_BTN_DOWN;
	}
	else
	{
		// 没有按键按下
		return;
	}
	//更新按键状态
	SET_BTN_UPDATE();
}