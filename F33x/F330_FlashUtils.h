//-----------------------------------------------------------------------------
// F330_FlashUtils.h
//-----------------------------------------------------------------------------
// Copyright 2004 Silicon Laboratories, Inc.
//
// This program contains several useful utilities for writing and updating
// FLASH memory.
//
// AUTH: BW & GP
// DATE: 21 JUL 04
//
// Target: C8051F33x
// Tool chain: KEIL C51 7.06
//
// Release 1.0
//

#ifndef F330_FLASHUTILS_H
#define F330_FLASHUTILS_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include "F330_FlashPrimitives.h"

//-----------------------------------------------------------------------------
// Structures, Unions, Enumerations, and Type Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Exported Function Prototypes
//-----------------------------------------------------------------------------

// FLASH read/write/erase routines
extern void FLASH_Write (FLADDR dest, char *src, unsigned numbytes);
extern char * FLASH_Read (char *dest, FLADDR src, unsigned numbytes);
extern void FLASH_Clear (FLADDR addr, unsigned numbytes);

// FLASH update/copy routines
extern void FLASH_Update (FLADDR dest, char *src, unsigned numbytes);   // copy with destination preservation
extern void FLASH_Copy (FLADDR dest, FLADDR src, unsigned numbytes);    // low-level FLASH/FLASH byte copy

// FLASH test routines
extern void FLASH_Fill (FLADDR addr, ULONG length, UCHAR fill);

#endif // F330_FLASHUTILS_H