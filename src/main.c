// COPYRIGHT (C) HARRY CLARK 2025
// HITACHI SH4 FPU EMULATOR WITH SH2 FP SUPPORT

// NESTED INCLUDES

#include "sh.h"
#include "sh_types.h"

int main(void) 
{
    INIT_FPU();

    SH_FP_REGISTERS[0] = 1.3f; // FR0 = 1.5
    SH_FP_REGISTERS[1] = 2.5f; // FR1 = 2.5

    printf("SH-4 FPU FADD:\n");
    uint16_t OPCODE = 0x0001; // REG_M = 1, REG_N = 0

    FADD(OPCODE);
    PRINT_FPU_REGISTERS();

    float SH4_RESULT = SH_FP_REGISTERS[0];

    INIT_FPU();
    SH_FP_REGISTERS[0] = 1.5f; // FR0 = 1.5
    SH_FP_REGISTERS[1] = 2.5f; // FR1 = 2.5

    printf("\nSH-2 FP EMULATION USING SH-4 FPU:\n");
    SH2_FADD(OPCODE);
    PRINT_FPU_REGISTERS();

    float SH2_RESULT = SH_FP_REGISTERS[0];
    if (FLOAT_EQUAL(SH2_RESULT, SH4_RESULT)) 
    {
        printf("\nSH-2 and SH-4 ARE EQUAL.\n");
    } 
    else 
    {
        printf("\nSH-2 and SH-4 results ARE NOT EQUAL.\n");
    }

    return 0;
}
