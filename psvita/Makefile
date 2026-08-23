CC = arm-vita-eabi-gcc
SRC = main.c
FLAGS = -O3
INCLUDE = -I$VITASDK/arm-vita-eabi/include/SDL
LIB = -lSDL -lSceCommonDialog_stub -lSceIme_stub -lSceHid_stub -lSceDisplay_stub -lSceGxm_stub -lSceCtrl_stub -lSceTouch_stub -lSceAudio_stub -lSceSysmodule_stub
ADDITFLAGS = -Wl,-q 
OUT = -o output.elf

all:
	@echo "==========[ Compiling... ]=========="
	$(CC) $(SRC) $(FLAGS) $(INCLUDE) $(LIB) $(ADDITFLAGS) $(OUT)
	@echo "Out: output.elf"
	@echo "==========[    Done	]=========="
	@echo "Please run the script responsible for turning this into a .vpk"
