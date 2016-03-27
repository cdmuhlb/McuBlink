# Default flags (optional)
CXXFLAGS += -Os -Wall -Wextra
#CXXFLAGS += -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics

# Flags required by the source code
override CXX = avr-g++
override CPPFLAGS += -DF_CPU=16000000L
override CXXFLAGS += -std=c++11 -mmcu=atmega328p
override LDFLAGS += -Wl,--gc-sections

# Flags required by the Makefile
override CPPFLAGS += -MMD -MP

# Source files
SRCS = $(wildcard *.cc)

# Substitution references used by the Makefile
OBJS = $(SRCS:%.cc=%.o)
DEPS = $(SRCS:%.cc=%.d)

# Default target
.PHONY: all
all: main.eep main.hex

# ELF executable
main.elf: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJS)

# EEPROM
main.eep: main.elf
	avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $< $@

# Hex executable
main.hex: main.elf
	avr-objcopy -O ihex -R .eeprom $< $@

# Upload to Pro Trinket
.PHONY: avrdude
avrdude: main.hex main.eep
	avrdude -v -patmega328p -cusbtiny -Uflash:w:$<:i

# Cleanup
.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPS) main.elf main.eep main.hex

# Include rules for source code dependencies
-include $(DEPS)
