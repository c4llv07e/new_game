
#ifndef GAME_RENDER_INC
#define GAME_RENDER_INC

#include "standard.h"
#include "types.h"
#include "define.h"

extern Int render_init(None);
extern Int render_terminate(None);
extern Return render_window_create(const char* name, Int width, Int height);
extern Int render_window_destroy(Return window);
extern Return render_window_show(Return window);
extern Return render_window_clear(Return window);
extern Bool render_window_should_close(Return window);
extern Return render_window_poll_events(Return window);
extern Return render_line(Return window, Int x,Int y,Int x2,Int y2, Render_color color);

typedef struct Render_color
{
  Byte r, g, b, a;
} Render_color;

typedef struct Render_window_option
{
  Render_color clear_color;
} Render_window_option;

typedef struct Render_window
{
  Ptr window;
  Ptr render;
  Bool window_should_close;
  Render_window_option* option;
} Render_window;

#endif /* GAME_RENDER_INC */
