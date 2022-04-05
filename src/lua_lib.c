
#include "lua_lib.h"
#include "render.h"
#include "system.h"

extern Int print(lua_State* state);
extern Int delay(lua_State* state);
extern Int draw_line(lua_State* state);
extern Int draw_color_line(lua_State* state);
extern Int get_mouse_pos(lua_State* state);

char* key_func_name[100] = {0x0};
Return key_func_state[100] = {0x0};

Return lwindow;

typedef enum functions
  {
    print_func = 0x0,
    delay_func,
    drawline_func,
    drawcolorline_func,
    get_mouse_pos_func,
    functions_len,
  } functions;

const char* functions_names[functions_len] =
  {
    [print_func] = "print",
    [delay_func] = "delay",
    [drawline_func] = "draw_line",
    [drawcolorline_func] = "draw_color_line",
    [get_mouse_pos_func] = "get_mouse_pos",
  };

Int (*functions_pointers[functions_len])(lua_State* state) =
  {
    [print_func] = print,
    [delay_func] = delay,
    [drawline_func] = draw_line,
    [drawcolorline_func] = draw_color_line,
    [get_mouse_pos_func] = get_mouse_pos,
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

Int
get_mouse_pos(lua_State* state)
{
  Int x=0,y=0;

  system_mouse_pos(&x, &y);

  lua_pushinteger(state, x);
  lua_pushinteger(state, y);

  return 0x2;
}

Int
draw_line(lua_State* state)
{
  int x,y,x2,y2;
  x = lua_tointeger(state, -4);
  y = lua_tointeger(state, -3);
  x2 = lua_tointeger(state, -2);
  y2 = lua_tointeger(state, -1);
  lua_pop(state, 4);
  render_line(lwindow, x, y, x2 , y2,
              (Render_color){.a = 0xff, .b = 0xff, .g = 0xff, .r = 0xff});
  return 0x0;
}

Int
draw_color_line(lua_State* state)
{
  double x,y,x2,y2,r,g,b,a;
  x = lua_tonumber(state, -8);
  y = lua_tonumber(state, -7);
  x2 = lua_tonumber(state, -6);
  y2 = lua_tonumber(state, -5);
  r = lua_tonumber(state, -4);
  g = lua_tonumber(state, -3);
  b = lua_tonumber(state, -2);
  a = lua_tonumber(state, -1);
  lua_pop(state, 8);
  render_line(lwindow, x, y, x2 , y2,
              (Render_color){.a = a, .b = b, .g = g, .r = r});
  return 0x0;
}

Int
delay(lua_State* state)
{
  double t;
  t = lua_tonumber(state, -1);
  lua_pop(state,1);
  system_wait(t);
  return 0x0;
}

Return
lua_lib_init(Return state, Return _window)
{
  lwindow = _window;
  if (state.is_null)
    return state;
  for (Int i = 0x0; i < functions_len; ++i)
    {
      lua_state_register_func(state, functions_names[i], functions_pointers[i]);
    }
  return state;
}
