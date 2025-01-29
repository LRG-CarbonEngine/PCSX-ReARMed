/***************************************************************************
                            spu.h  -  description
                             -------------------
    begin                : Wed May 15 2002
    copyright            : (C) 2002 by Pete Bernert
    email                : BlackDove@addcom.de
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version. See also the license.txt file for *
 *   additional informations.                                              *
 *                                                                         *
 ***************************************************************************/

#ifndef __P_SPU_H__
#define __P_SPU_H__

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define HTOLE16(x) __builtin_bswap16(x)
#define LE16TOH(x) __builtin_bswap16(x)
#else
#define HTOLE16(x) (x)
#define LE16TOH(x) (x)
#endif

struct SPUFreeze;
struct xa_decode;

long CALLBACK SPUopen(void);
long CALLBACK SPUinit(void);
long CALLBACK SPUshutdown(void);
long CALLBACK SPUclose(void);
void CALLBACK SPUwriteRegister(unsigned long, unsigned short, unsigned int);
unsigned short CALLBACK SPUreadRegister(unsigned long, unsigned int);
void CALLBACK SPUregisterCallback(void (*cb)(int));
void CALLBACK SPUregisterScheduleCb(void (*cb)(unsigned int));
long CALLBACK SPUfreeze(unsigned int, struct SPUFreeze *, unsigned int);
void CALLBACK SPUasync(unsigned int, unsigned int);

void CALLBACK SPUreadDMAMem(unsigned short * pusPSXMem,int iSize,unsigned int cycles);
void CALLBACK SPUwriteDMAMem(unsigned short * pusPSXMem,int iSize,unsigned int cycles);

void CALLBACK SPUplayADPCMchannel(struct xa_decode *xap, unsigned int cycle, int is_start);
int  CALLBACK SPUplayCDDAchannel(short *pcm, int bytes, unsigned int cycle, int is_start);
void CALLBACK SPUsetCDvol(unsigned char ll, unsigned char lr,
		unsigned char rl, unsigned char rr, unsigned int cycle);

// internal
void ClearWorkingState(void);
#endif /* __P_SPU_H__ */
