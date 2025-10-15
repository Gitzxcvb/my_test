//
// Created by ʰ�� on 2024/11/24.
//
//����VOFA+��JustFloat���ͣ���bff��β����{0x00,0x00,0x80,0x7f}4���ֽ�


#ifndef MC02_2025_ENGINEERINGS_VOFA_H
#define MC02_2025_ENGINEERINGS_VOFA_H

#include "stdarg.h"
#include "string.h"
#include "usart.h"
#include "bsp_usart.h"


//�ɱ��������<ArgType, ArgValue>����ʽ���ݣ��Դ���ͬ�ı������
#define  UINT8		1
#define  UINT16		2
#define  INT32			4
#define  FLOAT32		5








int FourPoints_float(float data_t);
void Send_buff_to_vofa(UART_HandleTypeDef *huart,int data,...);
void Send_buff_to_blue(UART_HandleTypeDef *huart,int data,...);





#endif //MC02_2025_ENGINEERINGS_VOFA_H
