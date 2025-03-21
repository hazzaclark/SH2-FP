// COPYRIGHT (C) HARRY CLARK 2025
// HITACHI SH4 FPU EMULATOR WITH SH2 FP SUPPORT

// THIS FILE PERTAINS TOWARDS BASIC TYPES OF THE CPU WITHOUT HAVING TO NECESSARILY 
// EMULATE THE ENTIRE MICROPROCESSER, ENOUGH TO GET THE FPU WORKING

#ifndef SH_H
#define SH_H

#if defined(USE_FP_ARGS)
#define USE_FP_ARGS
#else
#define USE_FP_ARGS

#define         SH_REG_F0           0x800
#define         SH_REG_F_COUNT      10
#define         SH_REG_F_LEN        SH_REG_F0 + SH_REG_F_COUNT

#define         SH_FLAG_C           0x01
#define         SH_FLAG_V           0x02
#define         SH_FLAG_Z           0x04
#define         SH_FLAG_S           0x08
#define         SH_FLAG_U           0x10

#endif
#endif