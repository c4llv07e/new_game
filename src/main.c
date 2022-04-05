
#include "standard.h"
#include "types.h"
#include "define.h"

#include "game.h"
#include "render.h"

/* main */

Return window = {.data = null, .is_null = true};
Int current_error = ok;

Int
main(None)
{
  if (render_init() != ok)
    return error_upper;

  window = render_window_create("test", 0x800, 0x800);

  game_start();

  while (!render_window_should_close(window))
    {
      render_window_clear(window);
      render_window_show(window);
      render_window_poll_events(window);
    }

  game_end();
  render_window_destroy(window);

  if ((current_error = render_terminate()) != ok)
    return current_error;
  
  return ok;
}
