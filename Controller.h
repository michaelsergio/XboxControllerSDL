#include "SDL2/SDL.h"

typedef struct _button {
  float perX;
  float perY;
  const char* format;
  float value;
  SDL_Color activatedColor;
} Button;

typedef struct _controller {
  Button lb;
  Button rb;
  Button lt;
  Button rt;
  Button ls_ns;
  Button ls_we;
  Button rs_ns;
  Button rs_we;
  Button a;
  Button b;
  Button x;
  Button y;
  Button d_u;
  Button d_d;
  Button d_l;
  Button d_r;
  Button back;
  Button start;
  Button xbox;
  SDL_Joystick *joystick;
} Controller;

Controller ControllerInit();
void ControllerInitSDL();
void ContorllerUpdate(Controller *controller, SDL_Event *event);
void ControllerDraw(Controller *controller, SDL_Renderer *renderer);
