#include "delay.h"
#include <intrins.h>
/**
 * 延时函数ms级 @33.1776MHz
 * @param unsigned int ms数 
 * return void
 */
void delay_ms(u16 ms)
{
	u8 i, j;
	while(ms--)
	{
		_nop_();
		_nop_();
		i = 33;
		j = 66;
		do
		{
			while (--j);
		} while (--i);
	}
	
}