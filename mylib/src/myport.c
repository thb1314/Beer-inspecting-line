#include "myport.h"
 
u8 button_state = NO_BTN_DOWN; 
bit is_btn_state_update button_state^7;
u8 temp_state = NO_BTN_DOWN;
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
		// û�а�������
		return;
	}
	//���ܻ��а�������
	//ȡ��֮ǰ�İ�������
	CLR_BTN_UPDATE();
	if(button_state == temp_state) 
		return;
	// ��ʱ����
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
		// û�а�������
		return;
	}
	//���°���״̬
	SET_BTN_UPDATE();
}