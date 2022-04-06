
#ifndef GAME_LUA_LIB_INC
#define GAME_LUA_LIB_INC

#include "types.h"
#include "standard.h"
#include "define.h"
#include "lua_game.h"
#include "render.h"

#include <SDL2/SDL_events.h>

#define CALLBACK_BUFFER_SIZE 0x40

extern UInt callback_last;
extern Int callback_func[CALLBACK_BUFFER_SIZE];
extern lua_State* callback_func_state[CALLBACK_BUFFER_SIZE];
extern SDL_EventType callback_func_type[CALLBACK_BUFFER_SIZE];

extern Return lua_lib_init(Return state, Return _window);
extern Int event_handle(SDL_Event event);

#endif /* GAME_LUA_LIB_INC */
