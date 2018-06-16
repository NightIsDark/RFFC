/****************************************************************
*
*UART0
*****************************************************************/ 
#include "serial.h"
U8 idata ReceiveFrame[20];  	//����Ϊ״̬,����,
U8 idata SendFrame[20];  			//����Ϊ״̬,����,
U8 idata SendCount;     				//�����ֽ���
U8 idata TotalSendCount;				//��������
U8 idata ReceiveCount; 		 		//�����ֽ���
U8 idata TotalReceiveCount; 		//�����ֽ���
bit   bReceiveData;  //���յ����� 
/****************************************************************
*
*UART0��ʼ������
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
	if(RI0==1)		//�����ж�?
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
					if(ReceiveCount<20)	//��ֹ���
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

