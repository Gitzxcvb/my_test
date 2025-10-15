//
// Created by ʰ�� on 2024/11/24.
//

#include "computer_up.h"



uint8_t to_vofa_buff[40];
uint8_t to_bule_buff[100]={0};//������40���ֽڣ������ټ�


//�ڴ��� Send_buff_to_vofa֮ǰ�轫float����˺������int
//ע�˺���������λС��
int FourPoints_float(float data_t)
{
   int volatile data = 0;
   data = (int)(data_t * 10000);
   return data;
}
//���͸�vofa+�Ķ���api
//huart:���͵Ĵ���
//�����data֮ǰ�����data������ �� Send_buff_to_vofa(huart7,3,data1,data2,data3)
//data����Ҫ����Ĳ�������FourPoints_float()�ٴ���˺������˺�����֧��ֱ�Ӵ���float
void Send_buff_to_vofa(UART_HandleTypeDef *huart,int data,...)
{
    memset(to_vofa_buff,0,40);
     uint8_t  count=0;
     va_list pArgs;//����ɱ�����б�ָ��
     va_start(pArgs, data);//��ȡ�ɱ��������

     for(uint8_t i = 0; i < data; i++)
	 {
         float data_t = va_arg(pArgs,int)/10000.0000f;
         memcpy(&to_vofa_buff[count],&data_t,sizeof (data_t));
         count+=sizeof (data_t);
     }

    va_end(pArgs);//�����ɱ����ָ�����
    to_vofa_buff[count++] = 0x00;
    to_vofa_buff[count++] = 0x00;
    to_vofa_buff[count++] = 0x80;
    to_vofa_buff[count++] = 0x7f;

    DMA_Usart_Send(huart, to_vofa_buff, count);
}


//���͸�bule�Ķ���api
//huart:���͵Ĵ���
//�����data֮ǰ�����data*2������ �� Send_buff_to_bule(huart1,8,DATA8,data1,DATA16,data2,INT32,data3,FLOAT32,data4)
//data����Ҫ�����float���Ͳ�������FourPoints_float()�ٴ���˺������˺�����֧��ֱ�Ӵ���float
void Send_buff_to_blue(UART_HandleTypeDef *huart,int data,...)
{
    memset(to_bule_buff,0,100);
    uint8_t count=0;
    to_bule_buff[count] = 0xA5;//��ͷ���
    count++;

    uint16_t data16;
    int  int32;
    float  float32;

    va_list pArgs;//����ɱ�����б�ָ��
    va_start(pArgs, data);//��ȡ�ɱ��������
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
    va_end(pArgs);//�����ɱ����ָ�����

    for(uint8_t i=1;i<count;i++)
    {
        to_bule_buff[count] += to_bule_buff[i];//У���λ���
    }
    count++;
    to_bule_buff[count] = 0x5A;//��β���
    DMA_Usart_Send(huart, to_bule_buff, count+1);
}








