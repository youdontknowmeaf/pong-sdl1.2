CC = mips64r5900el-ps2-elf-gcc
CFLAGS = -D_EE -O2 -G0 -Wall
INCLUDE = -I. -I./include -I$(PS2SDK)/ee/include -I$(PS2SDK)/common/include -I$(PS2SDK)/ee/include/SDL
SRC = main.c
OUT = -o pong.elf
LIBPATH = -L./lib -L$(PS2SDK)/ee/lib
LIB = -lsdlmain -lsdl -lgskit -ldmakit -lgskit_toolkit -lkernel -lc

all: pong.elf
pong.elf : $(SRC)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC) $(OUT) $(LIBPATH) $(LIB)

clean:
	rm *.elf
