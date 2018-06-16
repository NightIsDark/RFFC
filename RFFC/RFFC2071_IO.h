#ifndef  __RFFC2071_IO_H__
#define  __RFFC2071_IO_H__

#include "compiler_defs.h"
#include "C8051F330_defs.h"

#define CLK_2071_1 (P1 |= 0x10)
#define CLK_2071_0 (P1 &= 0xEF)

#define DATA_2071_1 (P1 |= 0x20)
#define DATA_2071_0 (P1 &= 0xDF)

#define DATA_2071_R ((P1 & 0x20)?1:0) 

#define LE_2071_1  (P1 |= 0x08)
#define LE_2071_0  (P1 &= 0xF7)



sbit LOCK			=	P1 ^ 1;
sbit D_RESET	=	P1 ^ 2;   //digital reset

sbit ENX			=	P1 ^ 3;
sbit CLK			=	P1 ^ 4;        
sbit DATA			=	P1 ^ 5;

sbit ENBL			=	P1 ^ 6;   //analog reset  ENBL
sbit MODE			=	P1 ^ 7;   //MODE

#endif