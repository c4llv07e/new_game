
#include "standard.h"
#include "types.h"
#include "define.h"

/* game */

extern Bool game_is_running(None);

Bool game_is_running = false;

Bool
game_is_running(None)
{
  return game_is_running;
}

/* render */

extern Int render_init(None);
extern Int render_terminate(None);
extern Return render_window_create(const char* name, Int width, Int height);
extern Int render_window_destroy(Return window);

#include <SDL2/SDL.h>

Int
render_init(None)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0x0)
    {
      fprintf(stderr, "error , can't init SDL\n"
              "error: %s\n", SDL_GetError());
      return error_system;
    }

  return ok;
}

Int
render_terminate(None)
{
  SDL_Quit();

  return ok;
}

Return
render_window_create(const char* name, Int width, Int height)
{
  Return ret;
  ret.data = SDL_CreateWindow(name,
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);
  if (ret.data != null)
    ret.is_null = false;

  return ret;
}

Int
render_window_destroy(Return window)
{
  if (window.is_null == true)
    return warn_already;

  SDL_DestroyWindow(window.data);
  window.data = null;
  window.is_null = true;
  
  return ok;
}

/* main */

Int
main(None)
{
  if (render_init() != ok)
    return error_upper;

  render_window_destroy(render_window_create("test", 0x800, 0x800));

  if (render_terminate() != ok)
    return error_upper;
  return ok;
}
