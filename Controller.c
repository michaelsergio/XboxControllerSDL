#include "Controller.h"
#include <limits.h>
#include "draw.h"

#define FMT_STICK_NS "^ %.2f%% v"
#define FMT_STICK_WE "< %.2f%% >"
#define FMT_BUTTON "%.0f"
#define UNACTIVATED_COLOR {255,255,255, 0}

#define AXIS_L_WE 0
#define AXIS_L_NS 1
#define AXIS_L_T  2
#define AXIS_R_WE 3
#define AXIS_R_NS 4
#define AXIS_R_T  5

#define HAT_DPAD 0

#define BUTTON_A 0
#define BUTTON_B 1
#define BUTTON_X 2
#define BUTTON_Y 3
#define BUTTON_LB 4
#define BUTTON_RB 5
#define BUTTON_BACK 6
#define BUTTON_START 7
#define BUTTON_XBOX 8

#define SHORT_RANGE  (SHRT_MAX - (int) SHRT_MIN)

float shrtToPercent(short value) {
  float percent = (float) value / (float) SHORT_RANGE + 0.5f;
  return percent;
}

Controller ControllerInit() {
  Controller controller;

  SDL_Joystick *joystick = SDL_JoystickOpen(0);
  if (joystick) puts("Joystick found"); else puts("Joystick not found");
  controller.joystick = joystick;

  Button lb = {0.05f, 0.2f, FMT_BUTTON, 0, UNACTIVATED_COLOR};
  Button rb = {0.75f, 0.2f, FMT_BUTTON, 0, UNACTIVATED_COLOR};
  Button lt = {0.05f, 0.1f, FMT_STICK_WE, 0, UNACTIVATED_COLOR};
  Button rt = {0.75f, 0.1f, FMT_STICK_WE, 0, UNACTIVATED_COLOR};
  Button ls_ns = {0.05f, 0.3f, FMT_STICK_NS, 0, UNACTIVATED_COLOR};
  Button ls_we = {0.05f, 0.4f, FMT_STICK_WE, 0, UNACTIVATED_COLOR};
  Button rs_ns = {0.75f, 0.7f, FMT_STICK_NS, 0, UNACTIVATED_COLOR};
  Button rs_we = {0.75f, 0.8f, FMT_STICK_WE, 0, UNACTIVATED_COLOR};
  Button     a = {0.75f, 0.6f, FMT_BUTTON, 0, {0,255,0}}; 
  Button     b = {0.85f, 0.5f, FMT_BUTTON, 0, {255,0,0}}; 
  Button     x = {0.65f, 0.5f, FMT_BUTTON, 0, {0,0,255}}; 
  Button     y = {0.75f, 0.4f, FMT_BUTTON, 0, {255,255,0}}; 
  Button   d_u = {0.15f, 0.6f, FMT_BUTTON, 0, UNACTIVATED_COLOR};
  Button   d_d = {0.15f, 0.8f, FMT_BUTTON, 0, UNACTIVATED_COLOR};
  Button   d_l = {0.05f, 0.7f, FMT_BUTTON, 0, UNACTIVATED_COLOR};
  Button   d_r = {0.25f, 0.7f, FMT_BUTTON, 0, UNACTIVATED_COLOR};
  Button  back = {0.25f, 0.5f, FMT_BUTTON, 0, UNACTIVATED_COLOR};
  Button  xbox = {0.35f, 0.5f, FMT_BUTTON, 0, {0,255,0}};
  Button start = {0.45f, 0.5f, FMT_BUTTON, 0, UNACTIVATED_COLOR};

  controller.lb = lb;
  controller.rb = rb;
  controller.lt = lt;
  controller.rt = rt;
  controller.ls_ns = ls_ns;
  controller.ls_we = ls_we;
  controller.rs_ns = rs_ns;
  controller.rs_we = rs_we;
  controller.a = a;
  controller.b = b;
  controller.x = x;
  controller.y = y;
  controller.d_u = d_u;
  controller.d_d = d_d;
  controller.d_l = d_l;
  controller.d_r = d_r;
  controller.back = back;
  controller.xbox = xbox;
  controller.start = start;

  return controller;
}
void ContorllerUpdate(Controller *controller, SDL_Event *event) {
    if (event->type == SDL_JOYAXISMOTION) {
      switch (event->jaxis.axis) {
        case AXIS_L_WE:
          controller->ls_we.value = shrtToPercent(event->jaxis.value);
          break;
        case AXIS_L_NS: 
          controller->ls_ns.value = shrtToPercent(event->jaxis.value);
          break;
        case AXIS_L_T:
          controller->lt.value = shrtToPercent(event->jaxis.value);
          break;
        case AXIS_R_WE:
          controller->rs_we.value = shrtToPercent(event->jaxis.value);
          break;
        case AXIS_R_NS: 
          controller->rs_ns.value = shrtToPercent(event->jaxis.value);
          break;
        case AXIS_R_T:
          controller->rt.value = shrtToPercent(event->jaxis.value);
          break;
      }
    }
    if (event->type == SDL_JOYHATMOTION) {
      switch (event->jhat.value) {
        case SDL_HAT_CENTERED:
          controller->d_u.value = 0;
          controller->d_d.value = 0;
          controller->d_l.value = 0;
          controller->d_r.value = 0;
          break;
        case SDL_HAT_LEFT: controller->d_l.value = 1; break; 
        case SDL_HAT_RIGHT: controller->d_r.value = 1.0f; 
                            break;
        case SDL_HAT_UP: controller->d_u.value = 1; break;
        case SDL_HAT_DOWN: controller->d_d.value = 1; break;
        case SDL_HAT_LEFTUP: 
          controller->d_l.value = 1; 
          controller->d_u.value = 1; 
        break;
        case SDL_HAT_LEFTDOWN: 
          controller->d_l.value = 1; 
          controller->d_d.value = 1; 
        break;
        case SDL_HAT_RIGHTUP: 
          controller->d_r.value = 1; 
          controller->d_u.value = 1; 
        break;
        case SDL_HAT_RIGHTDOWN: 
          controller->d_r.value = 1; 
          controller->d_d.value = 1; 
        break;
      }
    }
    if (event->type == SDL_JOYBUTTONDOWN || event->type == SDL_JOYBUTTONUP) {
      SDL_JoyButtonEvent be = event->jbutton;
      switch (be.button) {
        //printf("Button %d is down(%d)\n", be.button, be.state);
        case BUTTON_A: controller->a.value = be.state == SDL_PRESSED; break;
        case BUTTON_B: controller->b.value = be.state == SDL_PRESSED; break;
        case BUTTON_X: controller->x.value = be.state == SDL_PRESSED; break;
        case BUTTON_Y: controller->y.value = be.state == SDL_PRESSED; break;
        case BUTTON_LB: controller->lb.value = be.state == SDL_PRESSED; break;
        case BUTTON_RB: controller->rb.value = be.state == SDL_PRESSED; break;
        case BUTTON_BACK: controller->back.value = be.state == SDL_PRESSED; break;
        case BUTTON_START: controller->start.value = be.state == SDL_PRESSED; break;
        case BUTTON_XBOX: controller->xbox.value = be.state == SDL_PRESSED; break;
      }
    }
}

void ButtonDraw(Button *button, SDL_Renderer *renderer) {
  int width = 640;
  int height = 480;

  int x = width * button->perX;
  int y = height * button->perY;
  size_t bufferSize = 15;
  char textBuffer[bufferSize];
  snprintf(textBuffer, bufferSize, button->format, button->value);
  DrawText(x, y, textBuffer, button->activatedColor, renderer);
}

int stateOn = 0;
void ControllerDraw(Controller *controller, SDL_Renderer *renderer) {
  if (controller->rt.value >= 0.99f) {
    puts("Right Triggered Fired");
  }
  if (controller->a.value >= 0.99f) {
    if (!stateOn) {
      stateOn = 1;
      puts("A Pressed");
    }
  }
  else {
    if (stateOn) {
      stateOn = 0;
      puts("A Depressed");

    }
  }

  ButtonDraw(&controller->a, renderer);
  ButtonDraw(&controller->b, renderer);
  ButtonDraw(&controller->x, renderer);
  ButtonDraw(&controller->y, renderer);

  ButtonDraw(&controller->d_u, renderer);
  ButtonDraw(&controller->d_d, renderer);
  ButtonDraw(&controller->d_l, renderer);
  ButtonDraw(&controller->d_r, renderer);

  ButtonDraw(&controller->lt, renderer);
  ButtonDraw(&controller->rt, renderer);

  ButtonDraw(&controller->lb, renderer);
  ButtonDraw(&controller->rb, renderer);

  ButtonDraw(&controller->ls_ns, renderer);
  ButtonDraw(&controller->ls_we, renderer);

  ButtonDraw(&controller->rs_ns, renderer);
  ButtonDraw(&controller->rs_we, renderer);

  ButtonDraw(&controller->back, renderer);
  ButtonDraw(&controller->xbox, renderer);
  ButtonDraw(&controller->start, renderer);

  SDL_Color white = {255,255,255};
  DrawText(0, 440, "Space - Vibrate    Esc/Enter - Quit", white, renderer);
}


void ControllerInitSDL() {
  SDL_InitSubSystem(SDL_INIT_JOYSTICK);
}

void ControllerVibrate(Controller *controller) {
  if (controller) {
	  SDL_Haptic *haptic;
	  SDL_HapticEffect effect;
	  int north_id, east_id, west_id, south_id;

	  // Open the device
    haptic = SDL_HapticOpenFromJoystick(controller->joystick);
    if (haptic == NULL) return; // Most likely joystick isn't haptic

	  // See if it can do sine waves
	  if ((SDL_HapticQuery(haptic) & SDL_HAPTIC_SINE)==0) {
	    SDL_HapticClose(haptic); // No sine effect
	    return;
	  }
	
	  memset( &effect, 0, sizeof(SDL_HapticEffect) ); // 0 is safe default
	  effect.type = SDL_HAPTIC_SINE;
	  effect.periodic.direction.type = SDL_HAPTIC_POLAR; // Polar coordinates
	  effect.periodic.direction.dir[0] = 18000; // Force comes from south
	  effect.periodic.period = 1000; // 1000 ms
	  effect.periodic.magnitude = 20000; // 20000/32767 strength
	  effect.periodic.length = 1000; // 1 seconds long
	  effect.periodic.attack_length = 500; // Takes 1 second to get max strength
	  effect.periodic.fade_length = 500; // Takes 1 second to fade away 

 	  // Upload the effect
	  south_id = SDL_HapticNewEffect( haptic, &effect );

    effect.periodic.direction.dir[0] = 0;
	  north_id = SDL_HapticNewEffect( haptic, &effect );

	  effect.periodic.direction.dir[0] = 9000;
	  east_id = SDL_HapticNewEffect( haptic, &effect );

	  effect.periodic.direction.dir[0] = 27000;
	  west_id = SDL_HapticNewEffect( haptic, &effect );

	  // Test the effect
	  SDL_HapticRunEffect( haptic, north_id, 1 );
	  SDL_Delay( 1000); // Wait for the effect to finish
	  SDL_HapticRunEffect( haptic, south_id, 1 );
	  SDL_Delay( 1000); // Wait for the effect to finish
	  SDL_HapticRunEffect( haptic, east_id, 1 );
	  SDL_Delay( 1000); // Wait for the effect to finish
	  SDL_HapticRunEffect( haptic, west_id, 1 );
	  SDL_Delay( 1000); // Wait for the effect to finish

    // We destroy the effect, although closing the device also does this
	  SDL_HapticDestroyEffect( haptic,north_id );
	  SDL_HapticDestroyEffect( haptic,south_id );
	  SDL_HapticDestroyEffect( haptic,east_id );
	  SDL_HapticDestroyEffect( haptic,west_id );

	  // Close the device
	  SDL_HapticClose(haptic);
  }
}

