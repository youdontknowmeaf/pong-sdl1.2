CC 	= m68k-amigaos-gcc
CFLAGS 	= -Damiga -I./SDL1.2/include -I../ -noixemul -O3 -fomit-frame-pointer -m68020-60 -mhard-float -L./SDL1.2/lib
CLIBS	= -lSDL
TARGET	= amiga_pong
SRC	= ../main.c

all: $(SRC) ../config.h
	@echo "Assuming path: /opt/amiga/bin/$(CC) for the compiler."
	/opt/amiga/bin/$(CC) $(CFLAGS) $(SRC) $(CLIBS) -o $(TARGET)
	@file "$(TARGET)"
