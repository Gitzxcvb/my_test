//
// Created by 拾柒 on 2024/11/24.
//

#include "computer_up.h"



uint8_t to_vofa_buff[40];
uint8_t to_bule_buff[100]={0};//最大填充40个字节，不够再加


//在传入 Send_buff_to_vofa之前需将float传入此函数变成int
//注此函数保留四位小数
int FourPoints_float(float data_t)
{
   int volatile data = 0;
   data = (int)(data_t * 10000);
   return data;
}
//发送给vofa+的对外api
//huart:发送的串口
//在填充data之前需填充data的数量 如 Send_buff_to_vofa(huart7,3,data1,data2,data3)
//data：将要传入的参数经过FourPoints_float()再传入此函数，此函数不支持直接传入float
void Send_buff_to_vofa(UART_HandleTypeDef *huart,int data,...)
{
    memset(to_vofa_buff,0,40);
     uint8_t  count=0;
     va_list pArgs;//定义可变参数列表指针
     va_start(pArgs, data);//获取可变参数个数

     for(uint8_t i = 0; i < data; i++)
	 {
         float data_t = va_arg(pArgs,int)/10000.0000f;
         memcpy(&to_vofa_buff[count],&data_t,sizeof (data_t));
         count+=sizeof (data_t);
     }

    va_end(pArgs);//结束可变参数指针操作
    to_vofa_buff[count++] = 0x00;
    to_vofa_buff[count++] = 0x00;
    to_vofa_buff[count++] = 0x80;
    to_vofa_buff[count++] = 0x7f;

    DMA_Usart_Send(huart, to_vofa_buff, count);
}


//发送给bule的对外api
//huart:发送的串口
//在填充data之前需填充data*2的数量 如 Send_buff_to_bule(huart1,8,DATA8,data1,DATA16,data2,INT32,data3,FLOAT32,data4)
//data：将要传入的float类型参数经过FourPoints_float()再传入此函数，此函数不支持直接传入float
void Send_buff_to_blue(UART_HandleTypeDef *huart,int data,...)
{
    memset(to_bule_buff,0,100);
    uint8_t count=0;
    to_bule_buff[count] = 0xA5;//包头填充
    count++;

    uint16_t data16;
    int  int32;
    float  float32;

    va_list pArgs;//定义可变参数列表指针
    va_start(pArgs, data);//获取可变参数个数
    for(uint8_t i = 0; i < data; i++)
    {
        uint8_t eArgType = va_arg(pArgs, int);
        switch (eArgType)
        {
            case UINT8:
                to_bule_buff[count] = va_arg(pArgs, int);
                count++;break;
            case UINT16:
                data16 = va_arg(pArgs, int);
                memcpy(&to_bule_buff[count],&data16,sizeof (data16));
                count+=2;break;
            case INT32:
                int32= va_arg(pArgs, int);
                memcpy(&to_bule_buff[count],&int32,sizeof (int32));
                count+=4;break;
            case FLOAT32:
                float32= va_arg(pArgs, int)/10000.0000f;
                memcpy(&to_bule_buff[count],&float32,sizeof (float32));
                count+=4;break;
        }
    }
    va_end(pArgs);//结束可变参数指针操作

    for(uint8_t i=1;i<count;i++)
    {
        to_bule_buff[count] += to_bule_buff[i];//校验和位填充
    }
    count++;
    to_bule_buff[count] = 0x5A;//包尾填充
    DMA_Usart_Send(huart, to_bule_buff, count+1);
}








