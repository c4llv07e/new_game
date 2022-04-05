
#include "game.h"

Bool is_running = false;

Bool
game_is_running(None)
{
  return is_running;
}

Bool
game_start(None)
{
  return is_running = true;
}

Bool
game_end(None)
{
  return is_running = false;
}
