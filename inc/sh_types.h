// COPYRIGHT (C) HARRY CLARK 2025
// HITACHI SH4 FPU EMULATOR WITH SH2 FP SUPPORT

// THIS FILE PERTAINS TOWARDS BASIC TYPES OF THE CPU WITHOUT HAVING TO NECESSARILY 
// EMULATE THE ENTIRE MICROPROCESSER, ENOUGH TO GET THE FPU WORKING

#ifndef SH_TYPES_H
#define SH_TYPES_H

// NESTED INCLUDES

#include "sh.h"

static float SH_FP_REGISTERS[16];

#define         SH_FP_RS_BIN(VALUE)         SH_BASE_T->FR[(VALUE)]
#define         SH_FP_XS_BIN(VALUE)         SH_BASE_T->XR[(VALUE)]
#define         SH_FP_RS(VALUE)             (SH_FP_REGISTERS[VALUE])
#define         SH_FP_RD(VALUE)             (SH_FP_REGISTERS[VALUE])
#define         SH_FP_XFS(VALUE)            (SH_FP_REGISTERS[VALUE] + SH_BASE_T->XR)
#define         SH_FP_XFD(VALUE)            (SH_FP_REGISTERS[VALUE] + SH_BASE_T->XR)

void FADD(const uint16_t OPCODE);
void FSUB(const uint16_t OPCODE);
void FMUL(const uint16_t OPCODE);
void FDIV(const uint16_t OPCODE);
void FMAC(const uint16_t OPCODE);
void FSQRT(const uint16_t OPCODE);

#endif
