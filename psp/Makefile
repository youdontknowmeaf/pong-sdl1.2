TARGET = sdl_pong
OBJS = main.o

LIBS = -lSDL -lpspaudio -lpspirkeyb -lpsppower -lpspgu -lpspvfpu -lpsphprm -lpspctrl -lpspdebug -lpspdisplay -lpspgum -lpspge -lpspnet -lpspnet_apctl

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = SDL Pong
PSP_EBOOT_ICON = ICON0.png

PSPSDK = $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

all:
	rm *.elf *.SFO *.o
