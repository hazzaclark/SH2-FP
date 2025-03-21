// COPYRIGHT (C) HARRY CLARK 2025
// HITACHI SH4 FPU EMULATOR WITH SH2 FP SUPPORT

// THIS FILE PERTAINS TOWARDS BASIC TYPES OF THE CPU WITHOUT HAVING TO NECESSARILY 
// EMULATE THE ENTIRE MICROPROCESSER, ENOUGH TO GET THE FPU WORKING

#ifndef SH_H
#define SH_H

// SYSTEM INCLUDES

#include <stdio.h>
#include <stdint.h>

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

#define     SH_SR_T     0x00000001
#define     SH_SR_S     0x00000002
#define     SH_SR_I     0x000000F0
#define     SH_SR_Q     0x00000100
#define     SH_SR_M     0x00000200

typedef enum OPCODE_TYPE
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

} OPCODE_TYPE;

typedef struct OPCODE_INFO
{
    union PARAMS
    {
        uint8_t OUTPUT;
        uint8_t SIZE;
        uint16_t MASK;
    };

    OPCODE_TYPE OPCODE;
    const char* MNEMONIC;

    uint8_t SIZE;
    uint8_t FLAGS;
    unsigned CONDITION;

} OPCODE_INFO;

#endif

#if defined(USE_SH)
#define USE_SH
#else 
#define USE_SH

typedef struct SH_BASE
{
    uint32_t PC;
    uint32_t PR;
    uint32_t SR;
    uint32_t REGISTER;
    uint32_t EA;
    uint32_t FR[16];
    uint32_t XR[16];

    // SH4 SPECIFICS

    uint32_t PPC;
    uint32_t SPC;
    uint32_t SSR;
    uint32_t FPSCR;
    uint32_t FPUL;

} SH_BASE;

SH_BASE* SH_BASE_T;

#define         SH_REG_N            ((OPCODE_INFO >> 8) & 15)
#define         SH_REG_M            ((OPCODE_INFO >> 4) & 15)

#endif
#endif
