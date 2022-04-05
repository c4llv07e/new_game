
#ifndef GAME_SYSTEM_INC
#define GAME_SYSTEM_INC

#include "types.h"
#include "standard.h"
#include "define.h"
#include "lua_lib.h"
#include <SDL2/SDL_events.h>

extern Int system_wait(Int milis);
extern Int system_mouse_pos(Int* x, Int* y);
extern Int keydown_event_handle(Return* state, SDL_KeyboardEvent event);

#endif /* GAME_SYSTEM_INC */
