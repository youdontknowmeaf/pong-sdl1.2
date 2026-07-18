#---------------------------------------------------------------------------------
# Configuration
#---------------------------------------------------------------------------------
# Ensure these match your installation path
DEVKITPRO := /opt/devkitpro
DEVKITPPC := $(DEVKITPRO)/devkitPPC
CC        := $(DEVKITPPC)/bin/powerpc-eabi-gcc

# Directories
LIBOGC_INC := -I$(DEVKITPRO)/libogc/include
LIBOGC_LIB := -L$(DEVKITPRO)/libogc/lib/wii
PORTLIBS_LIB   := -L$(DEVKITPRO)/portlibs/wii/lib
PORTLIBS_INC := -I$(DEVKITPRO)/portlibs/wii/include

# Flags
CFLAGS   := -O2 -mrvl -meabi -mhard-float -DGEKKO $(LIBOGC_INC) $(PORTLIBS_INC)
LDFLAGS  := -mrvl -meabi -mhard-float $(LIBOGC_LIB) $(PORTLIBS_LIB)

# LIBS MUST be in order of dependency:
# SDL depends on AESND (audio) and core system libs
LIBS := -lSDL -laesnd -lasnd -lwiikeyboard -lwiiuse -lbte -logc -lm

#---------------------------------------------------------------------------------
# Targets
#---------------------------------------------------------------------------------
all: game.elf

game.elf: main.o
	@echo "Linking..."
	$(CC) $(LDFLAGS) main.o -o $@ $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o game.elf

.PHONY: all clean
