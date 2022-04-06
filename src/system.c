
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

Int
keydown_event_handle(SDL_KeyboardEvent event)
{
  for(int i = 0;key_func_name[i] != 0x0;++i){
    lua_set_func(key_func_state[i], key_func_name[i]);
    lua_call_func(key_func_state[i], 0, 0);
  }

  return ok;
}
