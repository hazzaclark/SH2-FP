// COPYRIGHT (C) HARRY CLARK 2025
// HITACHI SH4 FPU EMULATOR WITH SH2 FP SUPPORT

// THIS FILE PERTAINS TOWARDS BASIC TYPES OF THE CPU WITHOUT HAVING TO NECESSARILY 
// EMULATE THE ENTIRE MICROPROCESSER, ENOUGH TO GET THE FPU WORKING

#ifndef SH_TYPES_H
#define SH_TYPES_H

// NESTED INCLUDES

#include "sh.h"

#define         SH_FP_RS_BIN(VALUE)         SH_BASE_T->FR[(VALUE)]
#define         SH_FP_RS(VALUE)             * (float *) (SH_BASE_T->FR + (VALUE))
#define         SH_FP_RD(VALUE)             * (double *) (SH_BASE_T->FR + (VALUE))
#define         SH_FP_XS(VALUE)             SH_BASE_T->XR[(VALUE)]
#define         SH_FP_XFS(VALUE)            *( (float *)(SH_BASE_T->XR + (VALUE)) )
#define         SH_FP_XFD(VALUE)            *( (double *)(SH_BASE_T->XR + (VALUE)) )

#endif
