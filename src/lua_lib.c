
#include "lua_lib.h"

extern Int print(lua_State* state);

typedef enum functions
  {
    print_func = 0x0,
    functions_len,
  } functions;

const char* functions_names[functions_len] =
  {
    [print_func] = "print",
  };

Int (*functions_pointers[functions_len])(lua_State* state) =
  {
    [print_func] = print,
  };


Int
print(lua_State* state)
{
  Int arg_len;
  const char* log;
  
  arg_len = lua_gettop(state);

  for (Int i = 0x0; i < arg_len; ++i)
    {
      log = lua_tolstring(state, -1, null);
      lua_pop(state, 1);
      fputs(log, stdout);
    }
  return 0x0;
}


Return
lua_lib_init(Return state)
{
  if (state.is_null)
    return state;
  for (Int i = 0x0; i < functions_len; ++i)
    {
      lua_state_register_func(state, functions_names[i], functions_pointers[i]);
    }
  return state;
}
