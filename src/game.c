
#include "game.h"

Return game_window = {.data=null, .is_null=true};

UInt game_ents_size = 0x0;
Return* game_ents = null;

Return
game_rect_default(Return rect, Float x, Float y, Float w,
                  Float h, Render_color color)
{
  Game_rect* grect;
  if (rect.is_null)
    return rect;
  grect = rect.data;
  
  grect->x = x;
  grect->y = y;
  grect->w = w;
  grect->h = h;
  grect->is_rendered = true;
  grect->color = color;
  
  return rect;
}

Return
game_rect_create(Float x, Float y, Float w, Float h, Render_color color)
{
  Return rect;

  rect.data = malloc(sizeof(Game_rect));
  rect.is_null = rect.data == null;
  game_rect_default(rect, x, y, w, h, color);

  game_ents = realloc(game_ents, game_ents_size*sizeof(Game_rect));
  
  if (game_ents != null)
    {
      game_ents[game_ents_size] = rect;
      ++game_ents_size;
    }

  return rect;
}

Return
game_rect_delete(Return rect)
{
  if (rect.is_null)
    return rect;

  free(rect.data);
  rect.data = null;
  rect.is_null = true;
  
  return rect;
}

Return
game_rect_render(Return rect)
{
  Game_rect* grect;
  if (rect.is_null)
    return rect;
  grect = rect.data;
  if (!grect->is_rendered)
    return rect;
  
  render_fill_box(game_window, grect->x, grect->y,
                  grect->w, grect->h, grect->color);
  
  return rect;
}

Return
game_rect_disable_render(Return rect)
{
  Game_rect* grect;
  if (rect.is_null)
    return rect;
  grect = rect.data;
  grect->is_rendered = false;
  return rect;
}

Return
game_rect_enable_render(Return rect)
{
  Game_rect* grect;
  if (rect.is_null)
    return rect;
  grect = rect.data;
  grect->is_rendered = true;
  return rect;
}

Int
game_loop(None)
{
  UInt rect;
  for (rect = 0x0; rect < game_ents_size; ++rect)
    {
      if (game_ents[rect].is_null)
        continue;
      game_rect_render(game_ents[rect]);
    }
  return ok;
}

Int
game_init(Return window)
{
  game_window = window;
  return ok;
}
