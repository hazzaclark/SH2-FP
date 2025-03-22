// COPYRIGHT (C) HARRY CLARK 2025
// HITACHI SH4 FPU EMULATOR WITH SH2 FP SUPPORT

// NESTED INCLUDES

#include "sh.h"
#include "sh_types.h"

int main(void) 
{
    // CHANGE THIS TO TEST OUT EMU MODES

    INIT_FPU_WITH_MODE(FP_SH4);
    
    SH_FP_REGISTERS[0] = 1.3f;
    SH_FP_REGISTERS[1] = 2.5f;

    printf("\n--- TESTING SH-4 NATIVE FPU MODE ---\n");
    uint16_t OPCODE = 0x0001; // REG_M = 1, REG_N = 0
    
    FADD(OPCODE);
    PRINT_FPU_REGISTERS();
    
    float SH4_RESULT = SH_FP_REGISTERS[0];
    
    INIT_FPU_WITH_MODE(FP_SH2);
    
    SH_FP_REGISTERS[0] = 1.3f;
    SH_FP_REGISTERS[1] = 2.5f;
    
    printf("\n--- TESTING SH-2 EMULATION MODE ---\n");
    FADD(OPCODE);
    PRINT_FPU_REGISTERS();
    
    float SH2_RESULT = SH_FP_REGISTERS[0];
    
    printf("\n--- COMPARISON RESULTS ---\n");
    printf("SH4: %f\n", SH4_RESULT);
    printf("SH2: %f\n", SH2_RESULT);
    
    if (FLOAT_EQUAL(SH2_RESULT, SH4_RESULT)) 
    {
        printf("RESULTS ARE EQUAL (WITHIN RANGE)\n");
    } 
    else 
    {
        printf("RESULTS DIFFER\n");
        printf("DIFF: %f\n", SH4_RESULT - SH2_RESULT);
    }
    
    return 0;
}
