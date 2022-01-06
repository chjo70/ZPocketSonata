/* bmpLib.h - bitmap library header file */

/* Copyright 1998-2000 Wind River Systems, Inc. */

/*
modification history
--------------------
01c,04aug00,pfl  cleaned up, added comment.
01b,19nov98,tam  added bitGet().
01a,15sep98,tam  written.
*/

#ifndef __INCbmpLibh
#define __INCbmpLibh

#ifdef __cplusplus
extern "C" {
#endif


/* bitmap macros */

#define	BMP_WORD_BIT_SIZE	32

extern UINT	bitFirstGet (UINT32 * , UINT , UINT);

/*******************************************************************************
*
* bitGet - get the value of a bit 
*
* DESCRIPTION
* This macro returns the value of a bit in a bitmap. <bitNo> is the
* bit position between 0 and (bitmap size - 1). <addr> is the start
* address of the bitmap.
*
* RETURNS
* Value of a specific bit.
*
* NOMANUAL
*/

#define bitGet(bitNo,addr)                                              \
                ((*(UINT32 *)(((UINT32 *)(addr)) + ((bitNo) >> 5))) &   \
                (0x80000000 >> ((bitNo) & (BMP_WORD_BIT_SIZE-1))))

/*******************************************************************************
*
* bitSet - set a bit 
*
* DESCRIPTION
* This macro sets the value (1) of a bit in a bitmap. <bitNo> is the 
* bit position between 0 and (bitmap size - 1). <addr> is the start 
* address of the bitmap.
*
* RETURNS
* N/A
*
* NOMANUAL
*/

#define bitSet(bitNo,addr)                                              \
                (*(UINT32 *)(((UINT32 *)(addr)) + ((bitNo) >> 5))) |=   \
                (0x80000000 >> ((bitNo) & (BMP_WORD_BIT_SIZE-1)))

/*******************************************************************************
*
* bitClear - clear a bit 
*
* DESCRIPTION
* This macro clears the value (0) of a bit in a bitmap. <bitNo> is the 
* bit position between 0 and (bitmap size - 1). <addr> is the start 
* address of the bitmap.
*
* RETURNS
* N/A
*
* NOMANUAL
*/

#define bitClear(bitNo,addr)                                            \
                (*(UINT32 *)(((UINT32 *)(addr)) + ((bitNo) >> 5))) &=   \
                ~(0x80000000 >> ((bitNo) & (BMP_WORD_BIT_SIZE-1)))

/*******************************************************************************
*
* bitChange - change a bit 
*
* DESCRIPTION
* This macro toggles the value of a bit in a bitmap. <bitNo> is the 
* bit position between 0 and (bitmap size - 1). <addr> is the start 
* address of the bitmap.
*
* RETURNS
* N/A
*
* NOMANUAL
*/

#define bitChange(bitNo,addr)                                           \
                (*(UINT32 *)(((UINT32 *)(addr)) + ((bitNo) >> 5))) ^=   \
                (0x80000000 >> ((bitNo) & (BMP_WORD_BIT_SIZE-1)))

#ifdef __cplusplus
}
#endif

#endif /* __INCbmpLibh */
