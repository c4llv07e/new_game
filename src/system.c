
#include "system.h"
#include <SDL2/SDL_timer.h>

Int
system_wait(Int milis)
{
  SDL_Delay(milis);
  return ok;
}
