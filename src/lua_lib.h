
#ifndef GAME_LUA_LIB_INC
#define GAME_LUA_LIB_INC

#include "types.h"
#include "standard.h"
#include "define.h"
#include "lua_game.h"
#include "render.h"

extern char* key_func_name[100];
extern Return key_func_state[100];

extern Return lua_lib_init(Return state, Return _window);

#endif /* GAME_LUA_LIB_INC */
