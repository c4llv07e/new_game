
#include "lua_lib.h"
#include "render.h"
#include "system.h"

#include <stddef.h>

extern Int print(lua_State* state);
extern Int println(lua_State* state);
extern Int delay(lua_State* state);
extern Int draw_line(lua_State* state);
extern Int draw_text(lua_State* state);
extern Int get_mouse_pos(lua_State* state);
extern Int draw_color_line(lua_State* state);
extern Int add_eventlistener(lua_State* state);
extern Int del_eventlistener(lua_State* state);

/* internal funciton */
static Int fix_eventlisteners();

UInt callback_last = 0x0;
Int callback_func[CALLBACK_BUFFER_SIZE] = { 0x0 };
lua_State* callback_func_state[CALLBACK_BUFFER_SIZE] = { null };
SDL_EventType callback_func_type[CALLBACK_BUFFER_SIZE] = { SDL_FIRSTEVENT };

Return lwindow;

typedef enum functions
  {
    print_func = 0x0,
    println_func,
    delay_func,
    drawline_func,
    drawtext_func,
    drawcolorline_func,
    get_mouse_pos_func,
    add_eventlistener_func,
    del_eventlistener_func,
    functions_len,
  } functions;

const char* functions_names[functions_len] =
  {
    [print_func] = "print",
    [println_func] = "println",
    [delay_func] = "delay",
    [drawline_func] = "draw_line",
    [drawtext_func] = "draw_text",
    [get_mouse_pos_func] = "get_mouse_pos",
    [drawcolorline_func] = "draw_color_line",
    [add_eventlistener_func] = "add_eventlistener",
    [del_eventlistener_func] = "del_eventlistener",
  };

Int (*functions_pointers[functions_len])(lua_State* state) =
  {
    [print_func] = print,
    [println_func] = println,
    [delay_func] = delay,
    [drawline_func] = draw_line,
    [drawtext_func] = draw_text,
    [get_mouse_pos_func] = get_mouse_pos,
    [drawcolorline_func] = draw_color_line,
    [add_eventlistener_func] = add_eventlistener,
    [del_eventlistener_func] = del_eventlistener,
  };


Int
print(lua_State* state)
{
  Int arg_len;
  const char* log;

  arg_len = lua_gettop(state);

  for (Int i = 0x0; i < arg_len; ++i)
    {
      log = lua_tolstring(state, i-arg_len, null);
      fputs(log, stdout);
    }
  fflush(stdout);
  lua_pop(state, arg_len);
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
  double x,y,x2,y2;
  x = lua_tonumber(state, -4);
  y = lua_tonumber(state, -3);
  x2 = lua_tonumber(state, -2);
  y2 = lua_tonumber(state, -1);
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
  lua_pop(state, 1);
  system_wait(t);
  return 0x0;
}

Int
println(lua_State* state)
{
  lua_pushstring(state, "\n");
  print(state);
}

Int
draw_text(lua_State* state)
{
  Int x, y;
  const char* text;
  x = lua_tointeger(state, -3);
  y = lua_tointeger(state, -2);
  text = lua_tolstring(state, -1, null);
  lua_pop(state, 3);
  render_text(lwindow, x, y, text,
              (Render_color){.a = 0xff, .b = 0xff, .g = 0xff, .r = 0xff});
  return 0x0;
}

Int
add_eventlistener(lua_State* state)
{
  Int type;
  Int ref;
  
  type = lua_tointeger(state, -0x1);
  lua_pop(state, 0x1);
  
  ref = luaL_ref(state, LUA_REGISTRYINDEX);
  lua_pop(state, 0x1);

  callback_func[callback_last] = ref;
  callback_func_state[callback_last] = state;
  callback_func_type[callback_last] = type;
  ++callback_last;

  lua_pushnumber(state, ref);
  
  return 0x1;
}

static Int
fix_eventlisteners(None)
{
  Int offset;
  offset = 0x0;
  Int i;
  for (i = 0x0; i+offset < callback_last; ++i)
    {
      while (callback_func_state[i+offset] == null)
        ++offset;
      if (offset == 0x0)
        continue;
      callback_func[i] = callback_func[i+offset];
      callback_func_state[i] = callback_func_state[i+offset];
      callback_func_type[i] = callback_func_type[i+offset];
      callback_func_state[i+offset] = null;
    }
  callback_last = i;

  return offset;
}

Int
del_eventlistener(lua_State* state)
{
  Int ref;
  
  ref = lua_tonumber(state, -1);
  lua_pop(state, 0x1);

  for (Int i = 0x0; i < callback_last; ++i)
    {
      if (callback_func_state[i] == null)
        continue;
      if (callback_func[i] == ref)
        callback_func_state[i] = null;
    }
  fix_eventlisteners();
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
  lua_newtable(state.data);
  lua_pushstring(state.data, "key_down");
  lua_pushinteger(state.data, SDL_KEYDOWN);
  lua_settable(state.data, -0x3);
  lua_pushstring(state.data, "mouse_move");
  lua_pushinteger(state.data, SDL_MOUSEMOTION);
  lua_settable(state.data, -0x3);
  lua_setglobal(state.data, "event");
  return state;
}

typedef enum Event_arg_type
  {
    type_none = 0x0,
    type_int,
    type_string,
    type_sdl_keycode,
    types_length
  } Event_arg_type;

typedef struct Lua_event_handle_bundle
{
  SDL_Event event;
  Int args_len;
  size_t arguments[0x5];
  Event_arg_type args_types[0x5];
} Lua_event_handle_bundle;

Lua_event_handle_bundle events_config_bundle[] =
  {
    {
      .event = SDL_KEYDOWN,
      .args_len = 0x1,
      .arguments = {
        offsetof(SDL_Event, key.keysym.sym),
      },
      .args_types = {
        type_sdl_keycode
      }
    },
    {
      .event = SDL_MOUSEMOTION,
      .args_len = 0x2,
      .arguments = {
        offsetof(SDL_Event, motion.x),
        offsetof(SDL_Event, motion.y),
      },
      .args_types = {
        type_int,
        type_int
      }
    },
  };

UInt
find_event_number(SDL_Event event)
{
  UInt config_iter;
  config_iter = 0x0;
  while (events_config_bundle[config_iter].event.type != event.type
         && (sizeof(events_config_bundle)/sizeof(Lua_event_handle_bundle)) > config_iter)
    ++config_iter;

  return config_iter;
}

Int
inter_lua_push_event_args(Return state, SDL_Event event)
{
  UInt config_iter = 0x0;

  if (state.is_null)
    return 0x0;

  config_iter = find_event_number(event);
  
  for (Int i = 0x0; i < events_config_bundle[config_iter].args_len; ++i)
    {
      size_t offset;
      const void* data;
      
      offset = events_config_bundle[config_iter].arguments[i];
      data = (((void*)&event)+offset);

      
      if (events_config_bundle[config_iter].args_types[i] == type_sdl_keycode)
        data = (void*)SDL_GetKeyName(*(SDL_Keycode*)data);
      
      if (events_config_bundle[config_iter].args_types[i] == type_sdl_keycode)
        lua_pushstring(state.data, (const char*)data);
      else
        lua_pushinteger(state.data, *(Int*)data);
    }
  return events_config_bundle[config_iter].args_len;
}

Int
event_handle(SDL_Event event)
{
  for (Int i = 0x0; i < callback_last; ++i)
    {
      if (callback_func_type[i] == event.type
          && callback_func_state[i] != null)
        {
          Return state;
          Int args_len;
          
          state = (Return)
            { .data = callback_func_state[i], .is_null = callback_func_state[i] == null };
          lua_set_func_ref(state, callback_func[i]);
          args_len = inter_lua_push_event_args(state, event);
          lua_call_func(state, args_len, 0x0);
        }
    }
}
