#include "draw.h"

void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend, SDL_Rect *clip){
  SDL_Rect pos;
  pos.x = x;
  pos.y = y;
  //Detect if we should use clip width settings or texture width
  if (clip != NULL){
    pos.w = clip->w;
    pos.h = clip->h;
  }
  else {
    SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
  }
  SDL_RenderCopy(rend, tex, clip, &pos);
}


static TTF_Font *font = NULL;

void DrawText(int x, int y, char *text, SDL_Color color, SDL_Renderer *rend) {
  SDL_Surface *surf = TTF_RenderText_Blended(font, text, color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surf);
  SDL_FreeSurface(surf);
  ApplySurface(x, y, texture, rend, NULL);
}


int DrawTTFInit() {
  TTF_Init();
  font = TTF_OpenFont("FreeSans.ttf", 32);
  if (!font) {
    printf("SDL TTF  Error: %s\n", TTF_GetError());
    return -1;
  }
  return 0;
}

int DrawTTFQuit() {
  TTF_CloseFont(font);
  TTF_Quit();
  return 0;
}
