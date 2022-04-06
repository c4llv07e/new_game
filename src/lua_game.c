
#include "lua_game.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

Return
lua_state_create(None)
{
  lua_State* state;
  Return res;
  state = luaL_newstate();
  luaL_openlibs(state);

  res.data = state;
  res.is_null = (state==null);

  return res;
}

Int
lua_state_close(Return state)
{
  if (state.is_null)
    {
      fprintf(stderr, "error , lua state already null\n");
      return warn_already;
    }
  
  lua_close(state.data);
  state.data = null;
  state.is_null = true;

  return ok;
}

Return
lua_state_exec_file(Return state, const char* path)
{
  if (state.is_null)
    {
      fprintf(stderr, "error , can't execute file without lua state");
      return state;
    }
  luaL_dofile(state.data, path);
  return state;
}

Return
lua_state_exec_string(Return state, const char* com)
{
  if (state.is_null)
    {
      fprintf(stderr, "error , can't execute command without state\n");
      return state;
    }
  luaL_dostring(state.data, com);
  return state;
}

Return
lua_state_register_func(Return state, const char* name, int (*func)(lua_State*))
{
  if (state.is_null)
    {
      fprintf(stderr, "error , can't register function to null state\n");
      return state;
    }

  lua_register(state.data, name, func);

  return state;
}

Return
lua_set_func(Return state, const char* name)
{
  if (state.is_null)
    {
      fprintf(stderr, "error , can't set function for null state\n");
      return state;
    }
  lua_getglobal(state.data, name);
  return state;
}

Return
lua_call_func(Return state, Int arg_cout, Int ret_cout)
{
  if (state.is_null)
    {
      fprintf(stderr, "error , can't call function from null state\n");
      return state;
    }
  lua_call(state.data, arg_cout, ret_cout);
  return state;
}
