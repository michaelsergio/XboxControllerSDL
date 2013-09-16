#include "SDL2/SDL.h"
#include "draw.h"
#include "Controller.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


SDL_Window *win = NULL;
SDL_Renderer *ren = NULL;


int init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    printf("SDL init Error: %s\n", SDL_GetError());
    return 1;
  }

  win = SDL_CreateWindow("Hello World", 100, 100, 
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!win) {
    printf("SDL Error: %s\n", SDL_GetError());
    return 1;
  }

  ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!ren) {
    printf("SDL Error: %s\n", SDL_GetError());
    return 1;

  }

  DrawTTFInit();

  return 0;
}

int main(int argc, char**argv) {
  init();
  ControllerInitSDL();
  Controller controller = ControllerInit();

  SDL_RenderClear(ren);

  SDL_Color white = {255,255,255};
  DrawText(40, 100, "Hello World", white, ren);
  SDL_RenderPresent(ren);

  int quit = 0;
  while (!quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_QUIT:
          quit = 1;
        break;
        case SDL_KEYDOWN:
          if (e.key.keysym.sym == SDLK_SPACE) {
            // test out vibration in a rotation shape
            // I can't really tell the direction, but I should test it more
            ControllerVibrate(&controller);
          }
          if (e.key.keysym.sym == SDLK_ESCAPE ||
              e.key.keysym.sym == SDLK_RETURN) {
            quit = 1;
          }
        break;
      }
      ContorllerUpdate(&controller, &e);

    }
      SDL_RenderClear(ren);
      ControllerDraw(&controller, ren);
      SDL_RenderPresent(ren);
  }

  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}
