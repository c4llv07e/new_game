
#include "system.h"
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_mouse.h>

Int
system_wait(Int milis)
{
  SDL_Delay(milis);
  return ok;
}

Int
system_mouse_pos(Int* x, Int* y)
{
  SDL_GetMouseState(x, y);
  return ok;
}
