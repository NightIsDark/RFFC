#ifndef SERIAL_H
#define SERIAL_H

#include "compiler_defs.h"
#include "C8051F330_defs.h"

void InitSerial(void);

//extern U8 xdata CMD_ACK[10];   
////extern const U8 CMD_NAK[10]; 
//extern U8 xdata CMD_STF[10];
//extern U8 xdata CMD_GTF[10];
extern U8 idata ReceiveFrame[20];  	//依次为状态,数据,
extern U8 idata SendFrame[20];  			//依次为状态,数据,
extern U8 idata SendCount;     				//发送字节数
extern U8 idata TotalSendCount;				//发送总数
extern U8 idata ReceiveCount; 		 		//接收字节数
extern U8 idata TotalReceiveCount; 		//接收字节数
extern bit   bReceiveData;  //接收到数据 
#define SOF '$'
#define EOF '#'
#endif
