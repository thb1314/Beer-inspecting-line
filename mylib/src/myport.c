#include "myport.h"
#include "tim.h"
#include <STC15F2K60S2.H>
#include "delay.h"

volatile u8 button_state = NO_BTN_DOWN; 
// ��ʼ���˿�
void InitPort(void)
{
	//ע��: STC15W4K32S4ϵ�е�оƬ,�ϵ��������PWM��ص�IO�ھ�Ϊ
	//      ����̬,�轫��Щ������Ϊ׼˫��ڻ�ǿ����ģʽ��������ʹ��
	//���IO: P0.6/P0.7/P1.6/P1.7/P2.1/P2.2
	//        P2.3/P2.7/P3.7/P4.2/P4.4/P4.5
	
	// �������IO��Ϊ׼˫���
	// P06 P07 ׼˫���
	P0M1 &= 0x3F;
	P0M0 &= 0x3F;
	// P16 P17 ׼˫���
	P1M1 &= 0x3F;
	P1M0 &= 0x3F;
	// P21 P22 P23 P27 ׼˫���
	P2M1 &= 0x71;
	P2M0 &= 0x71;
	// P37 ׼˫���
	P3M1 &= 0x7F;
	P3M0 &= 0x7F;
	// P42 P44 P45
	P4M1 &= 0xCB;
	P4M0 &= 0xCB;
	
	//��ʼ����ť״̬
	button_state = NO_BTN_DOWN;
}

// ��ⰴť״̬ ���Է�ֹ�ظ�����
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
		// û�а�������
		return;
	}
	//�����ظ���������
	if((button_state&(~BTN_UPDATE)) == temp_btn_state) 
		return;
	// ��ʱ����
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
		// û�а�������
		return;
	}
	//�����״̬��ԭ���Ĳ�ͬ ˵���Ǹ���
	if(tmp != temp_btn_state)
		return;
	//���°���״̬
	button_state = tmp;
	SET_BTN_UPDATE(button_state);
}

// ��ⰴ���¼�����n����׼ ʱ��
void CheckIsClose(void)
{
	static u16 timer = 0;
	
	if(B_IS_CLOSE_BTN_DOWN())
	{
		timer++;
	}
	else
	{
		// ȡ����ʱ��
		CLR_PORT(is_start_check_close_btn);
		//ȡ����־λ
		return;
	}
	
	
	
	
	
	
	
	
}






