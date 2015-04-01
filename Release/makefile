################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include arduino/core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
/Users/Khadesha/Documents/2015arduino-mouse/Release/arduino.ar \

ELF += \
micromouse.elf \

EEP += \
micromouse.eep \

FLASH_IMAGE += \
micromouse.hex \


# All Target
all: micromouse

# Tool invocations
micromouse: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-size" -A "/Users/Khadesha/Documents/2015arduino-mouse/Release/micromouse.elf"
	@echo 'Finished building target: $@'
	@echo ' '

/Users/Khadesha/Documents/2015arduino-mouse/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-ar" rcs  "/Users/Khadesha/Documents/2015arduino-mouse/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

micromouse.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-gcc" -Os -Wl,--gc-sections -mmcu=atmega328p  -o "/Users/Khadesha/Documents/2015arduino-mouse/Release/micromouse.elf"   $(LINK_OBJ) $(AR)  "/Users/Khadesha/Documents/2015arduino-mouse/Release/arduino.ar" "-L/Users/Khadesha/Documents/2015arduino-mouse/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

micromouse.eep: $(ELF)
	@echo 'Create eeprom image'
	"/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "/Users/Khadesha/Documents/2015arduino-mouse/Release/micromouse.elf" "/Users/Khadesha/Documents/2015arduino-mouse/Release/micromouse.eep"
	@echo 'Finished building: $@'
	@echo ' '

micromouse.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-objcopy" -O ihex -R .eeprom  "/Users/Khadesha/Documents/2015arduino-mouse/Release/micromouse.elf" "/Users/Khadesha/Documents/2015arduino-mouse/Release/micromouse.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(C_DEPS)$(AR)$(EEP)$(FLASH_IMAGE)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS) micromouse
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
