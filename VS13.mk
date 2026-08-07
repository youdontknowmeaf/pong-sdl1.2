CC = cl
CFLAGS = /c /W3 /MD /DVSTUDIO /I".\SDL-Windows\SDL-1.2.15\include"
TARGET = pong.exe
OBJ = main.obj
LIBFLAGS = /LIBPATH:".\SDL-Windows\SDL-1.2.15\lib\x86" SDL.lib SDLmain.lib /SUBSYSTEM:WINDOWS

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) main.c
	link $(OBJ) $(LIBFLAGS) /OUT:$(TARGET)


clean:
	del *.obj $(TARGET)
