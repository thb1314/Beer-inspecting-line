#ifndef __MYFUNC_H_
#define __MYFUNC_H_

/******************************************************************* 
 *  Copyright(c) 2016 THB-CCUT  
 *  All rights reserved. 
 *   
 *  文件名称: myfunc.h
 *  简要描述: 定义一些用于IO操作的宏
 *   
 *  创建日期: 2016-11-06
 *  作者: THB
 *  说明: 
 *   
 *  修改日期: 
 *  作者: 
 *  说明: 
 ******************************************************************/


// 关于一些数据处理
#define GET_LOW_8BIT(x) (u8(x))
#define GET_HIGH_8BIT(x) (u8(x >> 8))

// 关于IO口的高低电平的判定
#define SET_PORT(x)		(x)=1
#define CLR_PORT(x)		(x)=0
#define IS_LOW(x)		(0 == (x))
#define IS_HIGH(x)		(1 == (x))
#define WATE_FOR_HIGH	while(IS_LOW(x))
#define WATE_FOR_LOW	while(IS_HIGH(x))
	
#endif