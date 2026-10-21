MCU     ?= atmega128
F_CPU   ?= 16000000UL

CC      := avr-gcc
OBJCOPY := avr-objcopy
SIZE    := avr-size
HOSTCC  ?= gcc

BUILD   := build
TARGET  := $(BUILD)/smart_home

FW_DIRS := firmware/APP firmware/LIB $(wildcard firmware/MCAL/*) $(wildcard firmware/HAL/*)
FW_SRCS := $(foreach d,$(FW_DIRS),$(wildcard $(d)/*.c))
FW_OBJS := $(patsubst %.c,$(BUILD)/avr/%.o,$(FW_SRCS))
FW_INCS := $(addprefix -I,$(FW_DIRS))

CFLAGS  := -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -std=gnu99 -Wall -ffunction-sections -fdata-sections
LDFLAGS := -mmcu=$(MCU) -Wl,--gc-sections

# Host unit tests: HAL drivers are compiled for the PC and linked against
# tests/fake_dio.c instead of the real DIO driver.
TEST_SRCS := $(wildcard tests/*.c) \
	         firmware/HAL/SSD/SSD_program.c \
	         firmware/HAL/KPD/KPD_program.c \
	         firmware/HAL/DC_MOTOR/DC_MOTOR_program.c
TEST_BIN  := $(BUILD)/host/unit_tests

.PHONY: all size test clean

all: $(TARGET).hex size

$(BUILD)/avr/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(FW_INCS) -c $< -o $@

$(TARGET).elf: $(FW_OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

size: $(TARGET).elf
	$(SIZE) $<

$(TEST_BIN): $(TEST_SRCS) $(wildcard tests/*.h)
	@mkdir -p $(dir $@)
	$(HOSTCC) -std=gnu99 -Wall -g -Itests $(FW_INCS) $(TEST_SRCS) -o $@

test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -rf $(BUILD)
