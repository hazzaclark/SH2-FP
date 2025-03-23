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

void INIT_FPU_WITH_MODE(FPU_MODE MODE) 
{
    INIT_FPU();
    SET_FPU_MODE(MODE);
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
        
        printf("SH4 FPU: FR%u = %f\n", REG_N, SH_FP_RD(REG_N));
    }
}

// BY DESIGN, THE SH2 HAS LOWER PRECISION FP 
// THIS WILL TAKE THE IEEE754 SP FLOAT AND MATCH IT AS CLOSELY TO THE SOFTWARE EMULATION OF THE SH2

// THE WAY IN WHICH THE SH2 HANDLES THE SOFTWARE EMULATION FOR THE FP ARITHMETIC IS BY
// CLEARING THE LOWEST NIBBLE OF THE MANTISSA

// ADDING THE EXPONENT RANGE IF THE INSTRUCTION IS PROCESSING AN INDIRECT ADDRESSING MODE

// FINALLY, ASSIGNS THE CORRESPONDING VALUE IN RELATION TO THE LEFT BIT MASK

float CONVERT_TO_SH2_PRECISION(float VALUE) 
{
    uint32_t BITS;
    memcpy(&BITS, &VALUE, sizeof(float));

    uint32_t SIGN = BITS & SH_FP_SIGN_MASK;
    uint32_t EXPO = (BITS & SH_FP_EXPO_MASK) >> 23;
    uint32_t MANTISSA = BITS & SH_FP_MANTISSA_MASK;

    const uint32_t MANTISSA_KEEP_BITS = (SH_FP_MANTISSA_MASK << (23 - SH2_MANTISSA_MAX_BITS));
    MANTISSA &= MANTISSA_KEEP_BITS;
    
    if (EXPO > 0 && EXPO < SH2_MIN_EXPO) 
    {
        // RANGE TOO SMALL? CLAMP TO ZERO TO AVOID UNDERFLOW

        EXPO = SH2_MIN_EXPO;
        MANTISSA = 0; 
    } 
    else if (EXPO > SH2_MAX_EXPO) 
    {
        // lIKEWISE FOR OVERFLOW

        EXPO = SH2_MAX_EXPO;
        MANTISSA = MANTISSA_KEEP_BITS; 
    }
    
    BITS = SIGN | (EXPO << 23) | MANTISSA;
    
    float RESULT;
    memcpy(&RESULT, &BITS, sizeof(float));
    
    return RESULT;
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
