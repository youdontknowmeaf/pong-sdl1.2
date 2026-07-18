#---------------------------------------------------------------------------------
# Makefile for Wii SDL Project
#---------------------------------------------------------------------------------

TARGET		:= project
BUILD		:= build
SOURCES		:= source
INCLUDES	:= include
DATA		:= data

#---------------------------------------------------------------------------------
# Options
#---------------------------------------------------------------------------------
# MACHDEP: Machine-specific compiler flags
# INCLUDE: Paths to include files
# LIBS:    Libraries to link (SDL must be included)

MACHDEP	:= -DGEKKO -mrvl -mcpu=750 -meabi -mhard-float
INCLUDE	:= -I$(CURDIR)/$(INCLUDES)
LIBS := -lSDL -laesnd -lasnd -lwiikeyboard -lwiiuse -lbte -logc -lm

#---------------------------------------------------------------------------------
# Standard devkitPro rules
#---------------------------------------------------------------------------------
include $(DEVKITPRO)/libogc/wii_rules

#---------------------------------------------------------------------------------
# Build Rules
#---------------------------------------------------------------------------------
.PHONY: all clean

all: $(BUILD)
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

$(BUILD):
	@[ -d $@ ] || mkdir -p $@

# The following rules only run inside the build directory
else

DEPENDS	:= $(OFILES:.o=.d)

$(OUTPUT).dol: $(OUTPUT).elf
$(OUTPUT).elf: $(OFILES)

endif

#---------------------------------------------------------------------------------
# Cleanup
#---------------------------------------------------------------------------------
clean:
	@rm -rf $(BUILD) $(TARGET).dol $(TARGET).elf
