
#include "lua_lib.h"

extern Int print(lua_State* state);
extern Int println(lua_State* state);

typedef enum functions
  {
    print_func = 0x0,
    println_func,
    functions_len,
  } functions;

const char* functions_names[functions_len] =
  {
    [print_func] = "print",
    [println_func] = "println",
  };

Int (*functions_pointers[functions_len])(lua_State* state) =
  {
    [print_func] = print,
    [println_func] = println,
  };


Int
print(lua_State* state)
{
  Int arg_len;
  const char* log;
  
  arg_len = lua_gettop(state);

  for (Int i = 0x0; i < arg_len; ++i)
    {
      log = lua_tolstring(state, i-arg_len, null);
      fputs(log, stdout);
    }
  lua_pop(state, arg_len);
  return 0x0;
}

Int
println(lua_State* state)
{
  lua_pushstring(state, "\n");
  print(state);
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
