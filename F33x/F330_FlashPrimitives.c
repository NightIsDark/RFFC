//-----------------------------------------------------------------------------
// F330_FlashPrimitives.c
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

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include "F330_FlashPrimitives.h"
#include <c8051F330.h>

//-----------------------------------------------------------------------------
// Structures, Unions, Enumerations, and Type Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------

// FLASH read/write/erase routines
void FLASH_ByteWrite (FLADDR addr, char byte);
unsigned char FLASH_ByteRead (FLADDR addr);
void FLASH_PageErase (FLADDR addr);

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// FLASH Routines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// FLASH_ByteWrite
//-----------------------------------------------------------------------------
//
// This routine writes <byte> to the linear FLASH address <addr>.
//
// To do:
//  -- optimize to skip 0xFF bytes
//
void FLASH_ByteWrite (FLADDR addr, char byte)
{
   bit EA_SAVE = EA;                   // preserve EA
   char xdata * data pwrite;           // FLASH write pointer

   EA = 0;                             // disable interrupts

   // change clock speed to slow, then restore later

   VDM0CN = 0x80;                      // enable VDD monitor


   RSTSRC = 0x02;                      // enable VDD monitor as a reset source

   pwrite = (char xdata *) addr;

   FLKEY  = 0xA5;                      // Key Sequence 1
   FLKEY  = 0xF1;                      // Key Sequence 2
   PSCTL |= 0x01;                      // PSWE = 1


   VDM0CN = 0x80;                      // enable VDD monitor


   RSTSRC = 0x02;                      // enable VDD monitor as a reset source

   *pwrite = byte;                     // write the byte

   PSCTL &= ~0x01;                     // PSWE = 0

   EA = EA_SAVE;                       // restore interrupts
}

//-----------------------------------------------------------------------------
// FLASH_ByteRead
//-----------------------------------------------------------------------------
//
// This routine reads a <byte> from the linear FLASH address <addr>.
//
unsigned char FLASH_ByteRead (FLADDR addr)
{
   bit EA_SAVE = EA;                   // preserve EA
   char code * data pread;             // FLASH read pointer
   unsigned char byte;

   EA = 0;                             // disable interrupts

   pread = (char code *) addr;

   byte = *pread;                      // read the byte

   EA = EA_SAVE;                       // restore interrupts

   return byte;
}

//-----------------------------------------------------------------------------
// FLASH_PageErase
//-----------------------------------------------------------------------------
//
// This routine erases the FLASH page containing the linear FLASH address
// <addr>.
//
void FLASH_PageErase (FLADDR addr)
{
   bit EA_SAVE = EA;                   // preserve EA
   char xdata * data pwrite;           // FLASH write pointer

   EA = 0;                          // disable interrupts
   // change clock speed to slow, then restore later

   VDM0CN = 0x80;                      // enable VDD monitor


   RSTSRC = 0x02;                   // enable VDD monitor as a reset source

   pwrite = (char xdata *) addr;

   FLKEY  = 0xA5;                   // Key Sequence 1
   FLKEY  = 0xF1;                   // Key Sequence 2
   PSCTL |= 0x03;                   // PSWE = 1; PSEE = 1


   VDM0CN = 0x80;                      // enable VDD monitor


   RSTSRC = 0x02;                   // enable VDD monitor as a reset source
   *pwrite = 0;                     // initiate page erase

   PSCTL &= ~0x03;                  // PSWE = 0; PSEE = 0

   EA = EA_SAVE;                    // restore interrupts
}