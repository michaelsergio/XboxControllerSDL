#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend, SDL_Rect *clip);
void DrawText(int x, int y, char *text, SDL_Color color, SDL_Renderer *rend);

int DrawTTFInit();
int DrawTTFQuit();
