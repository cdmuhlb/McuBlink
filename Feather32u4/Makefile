# Host-dependent variables
PROGRAMMER_PORT = /dev/ttyACM0

# Default flags (optional)
CXXFLAGS += -Os -Wall -Wextra
#CXXFLAGS += -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics
#CPPFLAGS += -DUSB_VID=0x239C -DUSB_PID=0x800C -DUSB_MANUFACTURER="Adafruit" -DUSB_PRODUCT="Feather 32u4"

# Flags and commands required by the source code
override CXX = avr-g++
override CPPFLAGS += -DF_CPU=8000000L
override CXXFLAGS += -std=c++11 -mmcu=atmega32u4
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

# Upload to Feather
.PHONY: avrdude
avrdude: main.hex main.eep
	# Uncomment to use CDC serial reset
	#stty -F $(PROGRAMMER_PORT) 1200
	#sleep 1
	avrdude -v -patmega32u4 -cavr109 -P$(PROGRAMMER_PORT) -b57600 -D -Uflash:w:$<:i

# Cleanup
.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPS) main.elf main.eep main.hex

# Include rules for source code dependencies
-include $(DEPS)
