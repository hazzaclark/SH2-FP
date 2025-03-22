// COPYRIGHT (C) HARRY CLARK 2025
// HITACHI SH4 FPU EMULATOR WITH SH2 FP SUPPORT

// THIS FILE PERTAINS TOWARDS BASIC TYPES OF THE CPU WITHOUT HAVING TO NECESSARILY 
// EMULATE THE ENTIRE MICROPROCESSER, ENOUGH TO GET THE FPU WORKING

// NESTED INCLUDES

#include "sh.h"
#include "sh_types.h"

float SH_FP_REGISTERS[16];
static bool FPU_RTS = false;
static FPU_MODE CURRENT_FPU_MODE = FP_SH4;

void SET_FPU_MODE(FPU_MODE MODE) 
{
    CURRENT_FPU_MODE = MODE;
    printf("FPU MODE SET TO: %s\n", MODE == FP_SH4 ? "SH4 NATIVE" : "SH2 EMU");
}

// FLOATING POINT ADD FROM FLOATING REGISTER M TO N

void FADD(const uint16_t OPCODE) 
{
    uint32_t REG_M = SH_REG_M(OPCODE);
    uint32_t REG_N = SH_REG_N(OPCODE);

    printf("FADD: REG_M = %u (FR%u = %f), REG_N = %u (FR%u = %f)\n",
           REG_M, REG_M, SH_FP_RS(REG_M), REG_N, REG_N, SH_FP_RD(REG_N));
    
    if (CURRENT_FPU_MODE == FP_SH2) 
    {
        // CONVERT OPERANDS TO HANDLE PRECISION TYPES

        float SH2_OPERAND_N = CONVERT_TO_SH2_PRECISION(SH_FP_RD(REG_N));
        float SH2_OPERAND_M = CONVERT_TO_SH2_PRECISION(SH_FP_RS(REG_M));        
        float RESULT = SH2_OPERAND_N + SH2_OPERAND_M;
        
        RESULT = CONVERT_TO_SH2_PRECISION(RESULT);
        
        SH_FP_RD(REG_N) = RESULT;
        
        printf("SH2 FP EMULATION: FR%u = %f\n", REG_N, SH_FP_RD(REG_N));
    } 
    else 
    {
        if (FPU_RTS) 
        {
            // WHEN RTS IS TRUE, APPLY MASK FOR PAIRED REGISTER ACCESS
            REG_N = REG_N & 0xE; 
            REG_M = REG_M & 0xE; 
            
            SH_FP_RD(REG_N) = SH_FP_RD(REG_N) + SH_FP_RS(REG_M);
        } 
        else 
        {
            SH_FP_RS(REG_N) = SH_FP_RS(REG_N) + SH_FP_RS(REG_M);
        }
        
        printf("SH4 FPU: Result in FR%u = %f\n", REG_N, SH_FP_RD(REG_N));
    }
}

///////////////////////////////////////////////////////////
//                  MISC FUNCTIONS
///////////////////////////////////////////////////////////

void INIT_FPU() 
{
    for (int i = 0; i < 16; i++) 
    {
        SH_FP_REGISTERS[i] = 0.0f;
    }
}

void PRINT_FPU_REGISTERS() 
{
    printf("FPU REGISTERS:\n");
    for (int i = 0; i < 16; i++) 
    {
        printf("FR%d: %f\n", i, SH_FP_REGISTERS[i]);
    }
}

bool FLOAT_EQUAL(float a, float b) 
{
        return fabs(a - b) < FLOAT_TOLERANCE;
}
