//
// Created by 拾柒 on 2024/11/24.
//
//发给VOFA+的JustFloat类型，在bff结尾加上{0x00,0x00,0x80,0x7f}4个字节


#ifndef MC02_2025_ENGINEERINGS_VOFA_H
#define MC02_2025_ENGINEERINGS_VOFA_H

#include "stdarg.h"
#include "string.h"
#include "usart.h"
#include "bsp_usart.h"


//可变参数采用<ArgType, ArgValue>的形式传递，以处理不同的变参类型
#define  UINT8		1
#define  UINT16		2
#define  INT32			4
#define  FLOAT32		5








int FourPoints_float(float data_t);
void Send_buff_to_vofa(UART_HandleTypeDef *huart,int data,...);
void Send_buff_to_blue(UART_HandleTypeDef *huart,int data,...);





#endif //MC02_2025_ENGINEERINGS_VOFA_H
