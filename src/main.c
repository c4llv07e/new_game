
#include "standard.h"
#include "types.h"
#include "define.h"

#include "render.h"
#include "lua_game.h"
#include "lua_lib.h"
#include "system.h"

/* main */

Return window = {.data = null, .is_null = true};
Return lua_state = {.data = null, .is_null = true};
Int current_error = ok;

Int
main(None)
{
  if (render_init() != ok)
    return error_upper;

  window = render_window_create("test", 0x800, 0x800);
  
  lua_state = lua_state_create();
  lua_lib_init(lua_state, window);

  lua_state_exec_file(lua_state, "init.lua");

  while (!render_window_should_close(window))
    {
      render_window_clear(window);
      lua_state_exec_file(lua_state, "main.lua");
      render_window_show(window);
      render_window_poll_events(window);
    }

  lua_state_close(lua_state);
  render_window_destroy(window);

  if ((current_error = render_terminate()) != ok)
    return current_error;

  return ok;
}
