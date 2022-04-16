
#ifndef NEW_GAME_GAME_INC
#define NEW_GAME_GAME_INC

#include "standard.h"
#include "types.h"
#include "define.h"
#include "render.h"

typedef struct Game_rect
{
  Float x, y, w, h;
  Render_color color;
  Bool is_rendered;
} Game_rect;

extern Int game_loop(None);
extern Int game_init(Return window);
extern Return game_rect_render(Return rect);
extern Return game_rect_delete(Return rect);
extern Return game_rect_create(Float x, Float y, Float w,
                               Float h, Render_color color);
extern Return game_rect_disable_render(Return rect);
extern Return game_rect_enable_render(Return rect);

#endif /* NEW_GAME_GAME_INC */
