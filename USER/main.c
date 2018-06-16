#include "serial.h"
#include "F330_FlashPrimitives.h"
#include "F330_FlashUtils.h"
#include "compiler_defs.h"
#include "PLL_ControlInterface.h"
sbit LED 	= P0 ^ 0;


typedef enum 
{
	CMD_ERROR,
	PAR_ERROR,
	STF_CMD,
	GTF_CMD,
}MESSAGE_T;

extern void Init_Device(void);
void DataProcess(void);
void ReportMessage(MESSAGE_T type);

FLADDR code FlashAddr	=	0x1A40; 
U32 frequecy	=	0;
#define DEFAULT_FRE	(186200)
void delay_ms(U16 ms)
{
	U16 i;
	while(ms)
	{
		for(i=0;i<1000;i++);
		ms--; 
	}
}
int main(void)
{
	Init_Device();		
	InitSerial();
	FLASH_Read((char *)&frequecy,FlashAddr,4);	
	if(frequecy	==	0)
	{
		frequecy	=	DEFAULT_FRE;
	}
	pll_set(frequecy);
	ReportMessage(GTF_CMD);
	while(1)
	{
			DataProcess();
			LED =	~LED;
			delay_ms(1000);		
			if(pll_get_lockstate())
			{
					
			}
			else
			{
				pll_set(frequecy);
				delay_ms(3000);
			}
	}
}

void ReportMessage(MESSAGE_T type)
{
	U32 tmp = 0;
	unsigned char i;
	tmp =	frequecy*10000;
	switch(type)
	{
		case CMD_ERROR:
		{
			SendFrame[0]=SOF;
			SendFrame[1]='E';
			SendFrame[2]='R';
			SendFrame[3]='R';
			SendFrame[4]='O';
			SendFrame[5]='R';	
			SendFrame[6]='1';	
			SendFrame[7]='!';				
			SendFrame[8]=EOF;
			SendCount=0;
			TotalSendCount=9;
			SCON0 |=0x02;	
			break;
		}
		case PAR_ERROR:
		{
			SendFrame[0]=SOF;
			SendFrame[1]='E';
			SendFrame[2]='R';
			SendFrame[3]='R';
			SendFrame[4]='O';
			SendFrame[5]='R';	
			SendFrame[6]='2';	
			SendFrame[7]='!';				
			SendFrame[8]=EOF;
			SendCount=0;
			TotalSendCount=9;
			SCON0 |=0x02;	
			break;
		}
		case 	STF_CMD:
		{
			SendFrame[0]=SOF;
			SendFrame[1]='S';
			SendFrame[2]='T';
			SendFrame[3]='F';
			SendFrame[4]=':';
			SendFrame[5]='O';	
			SendFrame[6]='K';	
			SendFrame[7]='!';				
			SendFrame[8]=EOF;
			SendCount=0;
			TotalSendCount=9;
			SCON0 |=0x02;	
			break;
		}
		case 	GTF_CMD:
		{
			SendFrame[0]=SOF;
			SendFrame[1]='F';
			SendFrame[2]='R';
			SendFrame[3]='Q';
			SendFrame[4]=':';
			for(i = 14;i>4;i--)
			{				
				SendFrame[i]	=	tmp%10 + 0x30;		
				tmp	/=	10;
			}	
//			SendFrame[14]=0x30;			
			SendFrame[15]=EOF;
			SendCount=0;
			TotalSendCount=16;
			SCON0 |=0x02;	
			break;
		}
		default:
			break;
	}
}
void DataProcess(void)
{
	U32 idata freq	=	0;
	U8 	idata i	=	0;
	if(bReceiveData)
	{
		bReceiveData	=	0;
		if((ReceiveFrame[1]=='S')&&(ReceiveFrame[2]=='T')&&(ReceiveFrame[3]=='F'))  //set the frequecy
		{
			for(i=5;i<14;i++)
			{
				freq	+=	ReceiveFrame[i]-0x30;
				freq  *=	10;
			}
			freq 	+=	(ReceiveFrame[14]-0x30);	
			freq  =	freq/10000;
			if(0 == pll_set(freq))
			{
				ReportMessage(PAR_ERROR);
			}
			else
			{
				ReportMessage(STF_CMD);	
				frequecy	=	freq;	
				FLASH_Update(FlashAddr,(char *)&frequecy,4);					
			}		
			
		}
		else if((ReceiveFrame[1]=='G')&&(ReceiveFrame[2]=='T')&&(ReceiveFrame[3]=='F'))  //get the frequecy
		{
			//todo
			ReportMessage(GTF_CMD);
		}
		else
		{
			ReportMessage(CMD_ERROR);
			//error processing
		}	
	}
}
