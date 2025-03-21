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
#define         SH_REG_F_LEN        (SH_REG_F0 + SH_REG_F_COUNT)

#define         SH_FLAG_C           0x01
#define         SH_FLAG_V           0x02
#define         SH_FLAG_Z           0x04
#define         SH_FLAG_S           0x08
#define         SH_FLAG_U           0x10

#define         SH_FP_ROUND_TRUNC       0
#define         SH_FP_ROUND_BASE        1
#define         SH_FP_ROUND_UP          2
#define         SH_FP_ROUND_DOWN        3
#define         SH_FP_ROUND_DEFAULT     4

#endif

#if defined(USE_SH_OPS)
#define USE_SH_OPS
#else 
#define USE_SH_OPS

enum OPCODE_TYPE
{
    OP_INVALID,
    OP_NOP,
    OP_ADD,
    OP_ADDC,
    OP_SUB,
    OP_SUBC,
    OP_MUL,
    OP_MULS,
    OP_MULU,
    OP_SHLR,
    OP_DT,
    OP_CMP,
    OP_TST,
    OP_AND,
    OP_OR,
    OP_XOR,
    OP_SHLL,
    OP_SHLR,
    OP_ROTL,
    OP_ROTR,
    OP_BF,
    OP_BT,
    OP_BRA,
    OP_BSR,
    OP_RTS
};

#endif
#endif
