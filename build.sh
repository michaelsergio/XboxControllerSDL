#set -v
gcc -g -Wall draw.c Controller.c xbox.c `pkg-config --cflags sdl2 SDL2_ttf` -o test `pkg-config --libs sdl2 SDL2_ttf` 
