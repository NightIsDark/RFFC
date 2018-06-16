#ifndef SERIAL_H
#define SERIAL_H

#include "compiler_defs.h"
#include "C8051F330_defs.h"

void InitSerial(void);

//extern U8 xdata CMD_ACK[10];   
////extern const U8 CMD_NAK[10]; 
//extern U8 xdata CMD_STF[10];
//extern U8 xdata CMD_GTF[10];
extern U8 idata ReceiveFrame[20];  	//����Ϊ״̬,����,
extern U8 idata SendFrame[20];  			//����Ϊ״̬,����,
extern U8 idata SendCount;     				//�����ֽ���
extern U8 idata TotalSendCount;				//��������
extern U8 idata ReceiveCount; 		 		//�����ֽ���
extern U8 idata TotalReceiveCount; 		//�����ֽ���
extern bit   bReceiveData;  //���յ����� 
#define SOF '$'
#define EOF '#'
#endif
