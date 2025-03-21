## COPYRIGHT (C) HARRY CLARK 2025
## HITACHI SH4 FPU EMULATOR WITH SH2 FP SUPPORT

#########################################################################
##				PREFIXES			       ##
#########################################################################

CC 					= gcc
WARNINGS 			= -std=c99 -Wall -Wextra -Wparentheses -Werror -pedantic
SRC 				= src
INC 				= inc

#########################################################################
##				FILE ACCESS			       ##
#########################################################################

FILES 		= $(wildcard $(SRC)/*.c)
OBJS 		= $(FILES:$(SRC)/%.c=$(SRC)/%.o)

#########################################################################
##			    TARGET LINKING			       ##
#########################################################################

TARGET 				= shfpu.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(WARNINGS) -I$(INC) -o $@ $(OBJS)

$(SRC)/%.o: $(SRC)/%.c
	$(CC) $(WARNINGS) -I$(INC) -c $< -o $@

clean:
	rm -f $(SRC)/*.o $(TARGET)

.PHONY: clean all