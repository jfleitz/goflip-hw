/********************************************************************************************************
 * File: sysclk.h
 * Description:
 *   include sytem clock function prototypes and global constants/variables
 *
 * Last modified: 21 Apr 2006
 ********************************************************************************************************
 * Copyright (C) 2008 by Zilog, Inc.  All Rights Reserved.
 ********************************************************************************************************/
#ifndef _SYSCLK_H_
#define _SYSCLK_H_

#define OSCCTL  (*(unsigned char volatile far*)0xF86)              // Reset = 0x20 Oscillator Control


//////////////////////////////////////////////////////////////////////////////
// Oscillator enable bits
#define OSC_INTEN               0x80   // Internal Precision Oscillator Enable
#define OSC_XTLEN               0x40   // External Oscillator Enable
#define OSC_WDTEN               0x20   // Watchdog Timer Oscillator Enable
// System Clock Oscillator Select bits
#define SCK_IPO                 0x00   // Internal precision oscillator at 5.5296MHz
#define SCK_IPO_32K             0x01   // Internal precision oscillator at 32KHz
#define SCK_XTAL                0x02   // Crystal oscillator or external RC oscillator
#define SCK_WDT                 0x03   // Watch-Dog Timer oscillator
#define SCK_CLKIN               0x04   // External clock signal on PB3 (8-Pin PA1)
#define SCK_IPO_MASK			0x01   // Mask bit of internal precision oscillator

// System clock options
#define CLOCK_INTERNAL          0
#define CLOCK_EXTERNAL		    1
#define CLOCK_SOURCE_DEFAULT    CLOCK_INTERNAL


//////////////////////////////////////////////////////////////////////////////
// Function Prototypes
void sysclk_init(void);


#endif
