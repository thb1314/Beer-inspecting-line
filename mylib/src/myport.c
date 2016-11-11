#include "myport.h"
#include "tim.h"
#include <STC15F2K60S2.H>
#include "delay.h"

volatile u8 button_state = NO_BTN_DOWN; 
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
	u8 tmp = NO_BTN_DOWN;
	u8 temp_btn_state = NO_BTN_DOWN;
	if( B_IS_STOP_BTN_DOWN())
	{
		temp_btn_state = STOP_BTN_DOWN;
	}
	else if(B_IS_FORCE_START_BTN_DOWN())
	{
		temp_btn_state = FORCE_START_BTN_DOWN;
	}
	else if(B_IS_FORCE_STOP_BTN_DOWN())
	{
		temp_btn_state = FORCE_STOP_BTN_DOWN;
	}
	else if( B_IS_CLOSE_BTN_DOWN())
	{
		temp_btn_state = CLOSE_BTN_DOWN;
	}
	else
	{
		// 没有按键按下
		return;
	}
	//避免重复按键操作
	if((button_state&(~BTN_UPDATE)) == temp_btn_state) 
		return;
	// 延时消抖
	delay_ms(10);
	
	if(B_IS_STOP_BTN_DOWN())
	{
		tmp = STOP_BTN_DOWN;
	}
	else if(B_IS_FORCE_START_BTN_DOWN())
	{
		tmp = FORCE_START_BTN_DOWN;
	}
	else if(B_IS_FORCE_STOP_BTN_DOWN())
	{
		tmp = FORCE_STOP_BTN_DOWN;
	}
	else if( B_IS_CLOSE_BTN_DOWN())
	{
		tmp = CLOSE_BTN_DOWN;
	}
	else
	{
		// 没有按键按下
		return;
	}
	//如果和状态和原来的不同 说明是干扰
	if(tmp != temp_btn_state)
		return;
	//更新按键状态
	button_state = tmp;
	SET_BTN_UPDATE(button_state);
}

// 检测按键事件大于n个基准 时基
void CheckIsClose(void)
{
	static u16 timer = 0;
	
	if(B_IS_CLOSE_BTN_DOWN())
	{
		timer++;
	}
	else
	{
		// 取消定时器
		CLR_PORT(is_start_check_close_btn);
		//取消标志位
		return;
	}
	
	
	
	
	
	
	
	
}






