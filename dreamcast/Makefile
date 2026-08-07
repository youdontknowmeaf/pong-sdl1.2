CC = kos-cc
GETLIB = -I/opt/toolchains/dc/kos-ports/SDL/inst/include/ -L/opt/toolchains/dc/kos-ports/lib/
SRC = main.c
LIBS = -lSDL -lGL -lGLU -lkosutils
TARGET = game.elf
BULLSHIT = config.h
DIRNAME = Pong_Dreamcast_Disc1

all:$(TARGET)

$(TARGET):$(SRC) $(BULLSHIT)
	$(CC) $(GETLIB) $(SRC) $(LIBS) -o $(TARGET)
	@echo "ELF debug executable for emulators. For a dreamcast-ready file please run 'make format'"
format:
	sh-elf-objcopy -O binary $(TARGET) 1ST_READ.BIN.tmp
	$(KOS_BASE)/utils/scramble/scramble 1ST_READ.BIN.tmp 1ST_READ.BIN
	@echo "Using my default IP.BIN, if you modify the code - feel free to change creds. Tho please don't change the creds and say you made the thing and redistribute it without my permission. <3"
	$(KOS_BASE)/utils/makeip/makeip ip.txt IP.BIN
	$(KOS_BASE)/utils/makeip/makeip -l iplogo.png -s iplogo.mr -v -f
	mv iplogo.mr IP.BIN 1ST_READ.BIN $(DIRNAME)/
	@echo "making a standard .iso..."
	#mkisofs -C 0,11702 -G $(DIRNAME)/IP.BIN -l -J -R -o sdlpong.iso $(DIRNAME)/
	genisoimage -C 0,11702 -V "PONG" -G $(DIRNAME)/IP.BIN -r -J -l -o sdlpong.iso $(DIRNAME)/
	@echo "Attempting to make a .cdi image..."
	sleep 10
	./cdi4dc sdlpong.iso Pong_Dreamcast_Disc1_sd.cdi
	[ -e "Pong_Dreamcast_Disc1_sd.cdi" ] && echo "Done!" || echo "Done (Failed to make .cdi)"
	
clean:
	rm *.elf *.cdi *.iso *.BIN.tmp *.BIN $(DIRNAME)/*
