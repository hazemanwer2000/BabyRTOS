#############################################################
# 
# Description: STM32F401xB/C Makefile.
# Author: Eng. Hazem Anwer
# Github: https://github.com/hazemanwer2000
# 
#############################################################

# Make workspace (usually '.make')
MAKE_WS := .make

# INCLUDE: Python library
include $(MAKE_WS)/py.mk

# Whitespace-separated list of source files
SRCS := $(call GET_FILES,.,.c)

# Whitespace-separated list of directories, containing header files, prefixed with '-I'
HDR_DIRS := $(addprefix -I,$(call GET_DIRS,.,.h))

# Mapping of 'SRCS' to other types of files
OBJS := $(SRCS:.c=.o)
DEPS := $(SRCS:.c=.d)
ASMS := $(SRCS:.c=.s)
PRES := $(SRCS:.c=.i)

# Compiler command (or, path)
CC := arm-none-eabi-gcc

# Sizer command (or, path)
SIZER := arm-none-eabi-size

# Name of target file
TARGET := main

# uC-related compiler flags
SPECS := -mcpu=cortex-m4 -mthumb -mfloat-abi=hard

# Compiler, pre-processor, and linker flags
CFLAGS := $(SPECS) -std=c99 -g3 -Og -fno-move-loop-invariants -ffunction-sections -fdata-sections -nostartfiles -ffreestanding --specs=nano.specs
PPFLAGS := $(HDR_DIRS)
LDFLAGS := -Wl,-Map,$(TARGET).map -Wl,--gc-sections -T mem.ld -T sections.ld -L./__ldscripts

.PHONY: clean build $(ASMS) $(PRES)

build: $(TARGET).elf

# RULE: Build target file, along with necessary files 
$(TARGET).elf: $(OBJS)
	$(CC) $(PPFLAGS) $(CFLAGS) $(LDFLAGS) $^ -o $@
	$(SIZER) $@

# RULE: Remove all generated files
clean:
	$(PY_DEL) $(addprefix ./$(TARGET).,elf map) $(DEPS) $(OBJS) $(ASMS) $(PRES)

# RULE (phony): Assembly files
$(ASMS): %.s: %.c
	$(CC) -S $(PPFLAGS) $(CFLAGS) $^ -o $@

# RULE (phony): Preprocessor files
$(PRES): %.i: %.c
	$(CC) -E $(PPFLAGS) $^ -o $@

# RULE: Dependencies
%.d: %.c
	$(CC) $(PPFLAGS) -MM -MT $(@:.d=.o) $^ > $@
	$(PY_APPEND_CMD) $@ $(CC) -c $(PPFLAGS) $(CFLAGS) $^ -o $(@:.d=.o)

# Issue an error, in-case of a missing command
ifeq (,$(MAKECMDGOALS))
$(error Missing command)
endif

# Including dependencies (case: 'build')
ifeq (build,$(MAKECMDGOALS))
-include $(DEPS)
endif