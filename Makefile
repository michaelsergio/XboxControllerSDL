LDFLAGS=
CFLAGS= -g -Wall
CC=gcc

DEPS= sdl2 SDL2_ttf

CFLAGS += `pkg-config --cflags $(DEPS)`
LDFLAGS += `pkg-config --libs $(DEPS)`

EXECUTABLE=input.exe

all: input.exe

input.exe: xbox.c draw.c Controller.c 
	$(CC) $(CFLAGS) $^ -o $(EXECUTABLE) $(LDFLAGS)

clean:
	rm $(EXECUTABLE)

#gcc -g -Wall draw.c Controller.c xbox.c `pkg-config --cflags sdl2 SDL2_ttf` -o input `pkg-config --libs sdl2 SDL2_ttf` 
