
#include "render.h"

#define SDL_DISABLE_IMMINTRIN_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

Int
render_init(None)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0x0)
    {
      fprintf(stderr, "error , can't init SDL\n"
              "error: %s\n", SDL_GetError());
      return error_system;
    }
  if (TTF_Init() == -1)
    {
      printf("Couldn't initialize TTF: %s\n", SDL_GetError());
      return error_system;
    }
  comicz = TTF_OpenFont("fonts/comicz.ttf", 48);
  if (!comicz)
    {
      printf("Failed to open ttf: %s\n", SDL_GetError());
      exit(1);
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
  Render_window* rwind;
  
  rwind = (Render_window*) malloc(sizeof(Render_window));
  if (rwind == null)
    return (Return){.data = null, .is_null = true};
  
  ret.data = rwind;
  /* window */
  rwind->window = SDL_CreateWindow(name,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   width, height,
                                   SDL_WINDOW_RESIZABLE);
  if (rwind->window == null)
    return (Return){.data = null, .is_null = true};
  /* render */
  rwind->render = SDL_CreateRenderer(rwind->window,
                                     -0x1,
                                     SDL_RENDERER_ACCELERATED);
  if (rwind->render == null)
    {
      SDL_DestroyWindow(rwind->window);
      return (Return){.data = null, .is_null = true};
    }
  /* window_should_close */
  rwind->window_should_close = false;

  ret.is_null = false;
  return ret;
}

Int
render_window_destroy(Return window)
{
  Render_window* rwind;
  if (window.is_null)
    return warn_already;

  rwind = window.data;

  SDL_DestroyWindow(rwind->window);
  SDL_DestroyRenderer(rwind->render);
  free(window.data);
  window.data = null;
  window.is_null = true;
  
  return ok;
}

Return
render_window_poll_events(Return window)
{
  Render_window* rwind;
  if (window.is_null)
    return window;
  rwind = window.data;
  SDL_Event event;
  while (SDL_PollEvent(&event))
    {
      switch (event.type)
        {
        case SDL_QUIT:
          rwind->window_should_close = true;
        }
    }
  return window;
}

Bool
render_window_should_close(Return window)
{
  Render_window* rwind;
  if (window.is_null)
    return true;

  rwind = window.data;

  return rwind->window_should_close;
}

Return
render_window_clear(Return window)
{
  Render_window* rwind;
  if (window.is_null)
    return window;
  rwind = window.data;
  SDL_SetRenderDrawColor(rwind->render, 0x00, 0x00, 0x00, 0xff);
  SDL_RenderClear(rwind->render);
  return window;
}

Return
render_window_show(Return window)
{
  Render_window* rwind;
  if (window.is_null)
    {
      fprintf(stderr, "error , null window on render_window_show\n");
      return window;
    }
  rwind = window.data;
  SDL_RenderPresent(rwind->render);
  return window;
}

Return
render_line(Return window, Int x, Int y, Int x2, Int y2, roloC color)
{
  Render_window* rwind;
  if (window.is_null)
    return window;
  rwind = window.data;
  SDL_SetRenderDrawColor(rwind->render, color.red, color.green, color.blue, color.alpha);
  SDL_RenderDrawLine(rwind->render, x, y, x2, y2);
  return window;
}







