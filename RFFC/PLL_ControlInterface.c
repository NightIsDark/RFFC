#include "RFFC2071.h"
#define  MAX_FRE (270000)    	//2.7G
#define  MIN_FRE (8500) 			//85M

/*
U8 set_pll_reg(U32 freq)
{
	U8  div = 0;
	U16 int_value		=	0;
	U32 frac_value	=	0;	
	U32 undiv_freq	=	0;
	
	div	=	get_vco_divider(freq);
	if(div ==0)
	{
		return 0;
	}
	else
	{
		//RFOUT = [INT + (FRAC/MOD)] * [fPFD]/RF divider
		undiv_freq	=	div * freq;
		int_value 	=	(U16)(undiv_freq/REF_F);
		frac_value	=	undiv_freq%REF_F;
		frac_value  = (frac_value/10000+5)/10; //Integer-valued
		set_pll(div,int_value,frac_value);	
	}
	return 1;
}
void RFFC2071_test(S_RFFC2071_REG * rffc2071_reg_t)
{
	U8 i=31;
	U16 DATA;
	U16 * str = (U16 *)rffc2071_reg_t;
		
	for(i=0;i<=RFFC2071_MAP_DEV_CTRL;i++)
	{
		DATA = * str;
		
		RFFC2071_write(i, DATA );
		
		str += 1;
	}
}
void RFFC2071_setup(void)
{
	S8 * ret;
	
	U32 buffer,fre;
	U32 NoFre[4]={0,0,0,0};
	U16 NoWid[4]={0,0,0,0};
	U8 enabl=0,i,MAXf=0,MINf=0;
	
	if(!CENTER_FREQ_FLAG)		return;
	if(vSystem_Sw_s.IS_ON == OFF)  return;
	


	//取第一子带中心频点
	ret = DataBuf + RAM_NO1_FREQ;
	for(i=0;i<4;i++)
	{
		buffer = (U32)*ret;
		buffer &= (U32)0x000000ff;		
		
		NoFre[0] |= (buffer << (8*i));
		ret++;
	}
	//取第一子带带宽
	ret = DataBuf + RAM_NO1_BANDWIDTH;
	for(i=0;i<2;i++)
	{
		buffer = (U32)*ret;
		buffer &= (U32)0x000000ff;		
		
		NoWid[0] |= (buffer << (8*i));
		ret++;
	}
	//取第2子带中心频点
	ret = DataBuf + RAM_NO2_FREQ;
	for(i=0;i<4;i++)
	{
		buffer = (U32)*ret;
		buffer &= (U32)0x000000ff;		
		
		NoFre[1] |= (buffer << (8*i));
		ret++;
	}
	//取第2子带带宽
	ret = DataBuf + RAM_NO2_BANDWIDTH;
	for(i=0;i<2;i++)
	{
		buffer = (U32)*ret;
		buffer &= (U32)0x000000ff;		
		
		NoWid[1] |= (buffer << (8*i));
		ret++;
	}
	//取第3子带中心频点
	ret = DataBuf + RAM_NO3_FREQ;
	for(i=0;i<4;i++)
	{
		buffer = (U32)*ret;
		buffer &= (U32)0x000000ff;		
		
		NoFre[2] |= (buffer << (8*i));
		ret++;
	}
	//取第3子带带宽
	ret = DataBuf + RAM_NO3_BANDWIDTH;
	for(i=0;i<2;i++)
	{
		buffer = (U32)*ret;
		buffer &= (U32)0x000000ff;		
		
		NoWid[2] |= (buffer << (8*i));
		ret++;
	}
	//取第4子带中心频点
	ret = DataBuf + RAM_NO4_FREQ;
	for(i=0;i<4;i++)
	{
		buffer = (U32)*ret;
		buffer &= (U32)0x000000ff;		
		
		NoFre[3] |= (buffer << (8*i));
		ret++;
	}
	//取第4子带带宽
	ret = DataBuf + RAM_NO4_BANDWIDTH;
	for(i=0;i<2;i++)
	{
		buffer = (U32)*ret;
		buffer &= (U32)0x000000ff;		
		
		NoWid[3] |= (buffer << (8*i));
		ret++;
	}
	//使能子带
	if(DataBuf[RAM_NO1_OFFON])
	{enabl |= 1;}
	if(DataBuf[RAM_NO2_OFFON])
	{enabl |= 2;}	
	if(DataBuf[RAM_NO3_OFFON])
	{enabl |= 4;}
	if(DataBuf[RAM_NO4_OFFON])
	{enabl |= 8;}
	
	//去最大、最小中心频点 序号
	for(i=0;i<4;i++)
	{
		if(enabl & (0x01<<i))
		{
			MAXf = i;MINf = i;
			break;
		}
	}
	for(i=MAXf;i<4;i++)
	{
		if(!(enabl & (0x01<<i)))
		{continue;}
		
		if(NoFre[MAXf] < NoFre[i])
		{MAXf = i;}
		
		if(NoFre[MINf] > NoFre[i])
		{MINf = i;}
	}
	
	//得到下行中心频点
	fre = (NoFre[MINf] - (NoWid[MINf] / 2) + NoFre[MAXf] + (NoWid[MAXf] / 2))/2 ;
	ret = DataBuf + RAM_TX_CENTER_FREQ;
	for(i=0;i<4;i++)
	{
		*ret = (S8) (fre >> (8*i));
		ret++;
	}
	fre += 9216 ;	//10kHz
	RFFC2071_set(fre) ;	
	
	//得到上行中心频点
	fre -= 9216 ;	//10kHz
	fre -= 9500 ; //10kHz
	ret = DataBuf + RAM_RX_CENTER_FREQ;
	for(i=0;i<4;i++)
	{
		*ret = (S8) (fre >> (8*i));
		ret++;
	}
	fre -= 9216 ;	//10kHz	
	RFFC2071_set(fre) ;
	
	CENTER_FREQ_FLAG = 0;		//clear flag

}
*/

// the unit of freq: 10Khz

U8 pll_set(U32 fre)
{
	S_RFFC2071_REG idata str;

	if((fre > MAX_FRE)||(fre < MIN_FRE))
	{
		return 0;
	}
	else
	{

		RFFC2071_reset_device(&str);
		
		RFFC2071_REG_INIT(&str);
		
		RFFC2071_PD_INIT(&str);	

		RFFC2071_N_INIT(fre,&str);	//10kHz	
		
		RFFC2071_setup_device(&str);					//1
		RFFC2071_set_calibration(&str);				//2
		RFFC2071_set_oper_freq(&str);					//3
		RFFC2071_set_calibration_mode(&str);	//4
		RFFC2071_enable_device(&str);					//5
		return 1;
	}
}
bit pll_get_lockstate(void)
{
	return RFFC2071_lock();
}