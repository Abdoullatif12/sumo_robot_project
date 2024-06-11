# Directories
C_STANDARD = c99
XC8_ROOT_DIR =  /opt/microchip/xc8/v2.46
XC8_BIN_DIR = $(XC8_ROOT_DIR)/bin
XC8_PIC_INCLUDE_DIR = $(XC8_ROOT_DIR)/pic
XC8_PIC_LIB_DIR = $(XC8_PIC_INCLUDE_DIR)/lib/$(C_STANDARD)
XC8_PIC_PROC_INCLUDE_DIR = $(XC8_PIC_INCLUDE_DIR)/proc
PROJECT_DIR = $(shell pwd)

MPLAB_IPE_DIR = /opt/microchip/mplabx/v6.20/mplab_platform/mplab_ipe
PROGRAMMER = PPK3
TARGET_MCU = 16f877a

INCLUDE_DIRS = $(XC8_PIC_INCLUDE_DIR)	\
				./src 					\
				./external/				\
				./external/printf		\
				./src/common/

LIB_DIRS = $(XC8_PIC_LIB_DIR)
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Toolchain
CC = $(XC8_BIN_DIR)/xc8-cc
AR = $(XC8_BIN_DIR)/xc8-ar
CPPCHECK = cppcheck
FORMAT = clang-format-12

# Files
TARGET = $(BIN_DIR)/sumobot

SOURCE_FILES_WITH_HEADERS = \
		src/drivers/io.c

HEADERS = $(SOURCE_FILES_WITH_HEADERS:.c=.h) \


SOURCES = src/main.c \
			$(SOURCE_FILES_WITH_HEADERS)
		  

# Create object files from source files
OBJECT_NAMES = $(SOURCES:.c=.p1)
OBJECT = $(patsubst %, $(OBJ_DIR)/%, $(OBJECT_NAMES))

# OBJECT = $(OBJ_DIR)/main.p1 \
# 		 $(OBJ_DIR)/led.p1

# Flags
MCU = pic16f877a
WFLAGS = -mwarn=3 -wall
CFLAGS = -mcpu=$(MCU) $(WFLAGS) $(addprefix -I, $(INCLUDE_DIRS)) -O0 -std=$(C_STANDARD)
LDFLAGS = -mcpu=$(MCU) $(addprefix -L, $(LIB_DIRS))

# Build
$(TARGET): $(OBJECT) 
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $^ -o $@

## Compiling
$(OBJ_DIR)/%.p1: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@


# Phonies
.PHONY: all clean flash cppcheck format

all:$(TARGET)

clean:
	rm -r $(BUILD_DIR)

flash:
	bash -c " cd $(MPLAB_IPE_DIR) && \
	ipecmd.sh -T$(PROGRAMMER) -P$(TARGET_MCU) -M -F$(PROJECT_DIR)/$(TARGET).hex"

cppcheck:
	@$(CPPCHECK) --quiet --enable=all --error-exitcode=1 --inline-suppr	\
	-I $(INCLUDE_DIRS) $(SOURCES)	\
	-i external/printf

format:
	@$(FORMAT) -i $(SOURCES) $(HEADERS)



# $(shell cd $(MPLAB_IPE_DIR) && pwd)  
# ipecmd.sh -T$(PROGRAMMER) -P$(TARGET_MCU) -M -F$(BIN_DIR)/$(TARGET).hex 
# cd$(shell cd $(CURRENT_DIR))


	