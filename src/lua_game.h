
#ifndef GAME_LUA_GAME_INC
#define GAME_LUA_GAME_INC

#include "types.h"
#include "standard.h"
#include "define.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

extern Return lua_state_create(None);
extern Int lua_state_close(Return state);
extern Return lua_state_exec_file(Return state, const char* path);
extern Return lua_state_exec_string(Return state, const char* com);
extern Return lua_state_register_func(Return state, const char* name, int (*func)(lua_State*));
extern Return lua_call_func(Return state, Int arg_cout, Int ret_cout);
extern Return lua_set_func(Return state, const char* name);
extern Return lua_set_func_ref(Return state, Int ref);

#endif /* GAME_LUA_GAME_INC */
