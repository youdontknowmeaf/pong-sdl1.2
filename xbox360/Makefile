CC = xenon-gcc 
SRC = main.c -c
OUT = -o main.o
INCLUDE = -I. -I$DEVKITXENON/usr/include
FLAGS = -O2 -mcpu=cell -mtune=cell -m32 -mno-altivec -mhard-float -fno-pic -mpowerpc64
OBJ = main.o
LIB = ./libSDL.a
ELFOUT = -o xenon.elf
XENON = $(FLAGS) -L$DEVKITXENON/xenon/lib/32 -L$DEVKITXENON/usr/lib -T$DEVKITXENON/app.lds -u read -u _start -u exc_base -lxenon -lm
#xenon-objcopy -O binary pong.elf pong.bin

all:
	$(CC) $(SRC) $(OUT) $(INCLUDE) $(FLAGS)
	$(CC) $(OBJ) $(LIB) $(ELFOUT) $(XENON)
	file xenon.elf
