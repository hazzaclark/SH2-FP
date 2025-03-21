# SH2-FP

Hitachi SuperH (SH4) FPU Emulator with innate support for SH2 FP arithmetic

# Motive:

The ambiition behind this project moreover is to provide a means by which FP-related logic is able to repurposed and moulded to suit the innate design of a particular architecture. 
In this case, I want to be able to leverage the SH4's FPU to be able to handle the SH2's FP as well.

This came about as a result of two major developments:

A. I wanted to work on a research piece indicative of something worthwhile

B. This notion of it being worthwhile could fall into the hands of someone willing to expand upon my original idea (SEGA Saturn games ported to the SEGA Dreamcast)

# Writing:

This project will feature a research writing including my findings, the implementation, etc

# Building:

```
git clone

make clean

make
```

the output should be ``./shfpu``

For the time being, there will be a simulator baked into the main file which will serve to prove a basis by which this logic is able to be transposed between FPU's (in spite of the SH2 not having an FPU in the conventional sense)


# Sources:

[MAME](https://github.com/mamedev/mame/tree/master/)

[SH2 RISC Engine](https://antime.kapsi.fi/sega/files/h12p0.pdf)

[Yet another SH Programming Manual](https://bitsavers.computerhistory.org/components/hitachi/superH/1995_SH1_SH2_Programming_Manual_3rd_Edition.pdf)
 
