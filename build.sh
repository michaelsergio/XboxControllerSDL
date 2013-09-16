#set -v
gcc -g -Wall draw.c Controller.c xbox.c `pkg-config --cflags sdl2 SDL2_ttf` -o input `pkg-config --libs sdl2 SDL2_ttf` 
