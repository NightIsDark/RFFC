/****************************************************************
*
*UART0
*****************************************************************/ 
#include "serial.h"
U8 idata ReceiveFrame[20];  	//依次为状态,数据,
U8 idata SendFrame[20];  			//依次为状态,数据,
U8 idata SendCount;     				//发送字节数
U8 idata TotalSendCount;				//发送总数
U8 idata ReceiveCount; 		 		//接收字节数
U8 idata TotalReceiveCount; 		//接收字节数
bit   bReceiveData;  //接收到数据 
/****************************************************************
*
*UART0初始化函数
*****************************************************************/
void InitSerial(void)
{
   SendCount=0;
	 TotalSendCount=0;
   ReceiveCount=0;
   TotalReceiveCount=0;   
	 bReceiveData = 0;
}

void Serial() interrupt 4
{
	U8 ret;
	if(RI0==1)		//接收中断?
	{
		RI0=0;			
		ret = SBUF0;

		switch(ret)
		{
			case SOF:	
			{
				ReceiveFrame[0]	=	SOF;
				ReceiveCount	=	1;
				break;
			}
			case EOF:	
			{
					ReceiveFrame[ReceiveCount]	=	EOF;
					TotalReceiveCount	=	ReceiveCount;
					ReceiveCount	=	0;	
					bReceiveData	=	1;
				break;
			}
			default :
			{
					if(ReceiveCount<20)	//防止溢出
					{
						ReceiveFrame[ReceiveCount]=ret;
						ReceiveCount++;
					}
					else
					{
						ReceiveCount	=	0;
					}
					break;
			}
		}
	}
	if(TI0==1)
	{
		TI0 = 0;			
		if(SendCount < TotalSendCount)     
		{
				SBUF0=SendFrame[SendCount];
				SendCount++;
		}       	    		
	}
}

