
#include "standard.h"
#include "types.h"
#include "define.h"

#include "game.h"
#include "render.h"
#include "lua_game.h"
#include "system.h"

/* main */

Return window = {.data = null, .is_null = true};
Return lua_state = {.data = null, .is_null = true};
Int current_error = ok;

Int
testCall(lua_State* state)
{
  lua_getglobal(state, "print");
  lua_pushstring(state, "test");
  lua_call(state, 0x1, 0x0);
  lua_pushnumber(state, 42);
  return 0x1;
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
  render_line(window, x, y, x2 , y2,
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
  render_line(window, x, y, x2 , y2,
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

Int
main(None)
{
  if (render_init() != ok)
    return error_upper;

  window = render_window_create("test", 0x800, 0x800);

  game_start();

  lua_state = lua_state_create();
  lua_state_register_func(lua_state, "testCall", testCall);
  lua_state_register_func(lua_state, "draw_line", draw_line);
  lua_state_register_func(lua_state, "draw_color_line", draw_color_line);
  lua_state_register_func(lua_state, "delay", delay);

  while (!render_window_should_close(window))
    {
      render_window_clear(window);
      lua_state_exec_file(lua_state, "main.lua");
      render_window_show(window);
      render_window_poll_events(window);
    }

  game_end();
  lua_state_close(lua_state);
  render_window_destroy(window);

  if ((current_error = render_terminate()) != ok)
    return current_error;
  
  return ok;
}
