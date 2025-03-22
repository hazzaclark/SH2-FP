// COPYRIGHT (C) HARRY CLARK 2025
// HITACHI SH4 FPU EMULATOR WITH SH2 FP SUPPORT

// THIS FILE PERTAINS TOWARDS BASIC TYPES OF THE CPU WITHOUT HAVING TO NECESSARILY 
// EMULATE THE ENTIRE MICROPROCESSER, ENOUGH TO GET THE FPU WORKING

// NESTED INCLUDES

#include "sh.h"
#include "sh_types.h"

static bool FPU_RTS = false;

// FLOATING POINT ADD FROM FLOATING REGISTER M TO N BASED OFF THE RESULT OF THE PROCEDURE REGISTER (RTS)

void FADD(const uint16_t OPCODE) 
{
    uint32_t REG_M = SH_REG_M(OPCODE);
    uint32_t REG_N = SH_REG_N(OPCODE);

    printf("FADD: REG_M = %u (FR%u = %f), REG_N = %u (FR%u = %f)\n",
           REG_M, REG_M, SH_FP_RS(REG_M), REG_N, REG_N, SH_FP_RD(REG_N));

    if (FPU_RTS) 
    {
        // WHEN RTS IS TRUE, MAKE A MASK
        
        REG_N = REG_N & 0xE; 
        REG_M = REG_M & 0xE; 

        SH_FP_RD(REG_N) = SH_FP_RD(REG_N) + SH_FP_RS(REG_M);
    } 
    else 
    {
        SH_FP_RS(REG_N) = SH_FP_RS(REG_N) + SH_FP_RS(REG_M);
    }

    printf("FADD: Result in FR%u = %f\n", REG_N, SH_FP_RD(REG_N));
}
