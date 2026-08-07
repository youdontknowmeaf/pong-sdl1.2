CC = powerpc-eabi-gcc
CCFLAGS = -O2 -mrvl -mcpu=750 -meabi -mhard-float -DGEKKO -D__wii__ -DHW_RVL -ffunction-sections -fdata-sections -I/opt/devkitpro/libogc/include -I/opt/devkitpro/portlibs/wii/include -c
SRC1 = main.c
SRC2 = main.o
OUT1 = -o main.o
OUT2 = -o game.elf
LINK = -mrvl -mcpu=750 -meabi -mhard-float -L/opt/devkitpro/libogc/lib/wii -L/opt/devkitpro/portlibs/wii/lib
LIBS = -lSDL -laesnd -lwiikeyboard -lfat -lwiiuse -lbte -logc -lm

CNVRT = elf2dol
SRC3 = game.elf
OUT3 = Pong.dol

all: $(SRC1)
	@echo "|==[ Compiling (Stage 1/3) ]==========|"
	$(CC) $(CCFLAGS) $(SRC1) $(OUT1)
	@echo "|==[ Linking (Stage 2/3) ]==========|"
	$(CC) $(LINK) $(SRC2) $(OUT2) $(LIBS)
	@echo "|==[ Making .dol (stage 3/3) ]==========|"
	$(CNVRT) $(SRC3) $(OUT3)
	@file $(OUT3)
	@echo "Done."

clean:
	rm -r $(SRC2) $(SRC3) $(OUT3)
