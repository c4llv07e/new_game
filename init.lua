
println("Welcome ", "to", " the ", "new_game", "!!!")

key_event = function (key)
   println(key)
end

mouse_event = function (x, y)
   println(x, " ", y)
end

add_eventlistener(key_event, event.key_down)
add_eventlistener(mouse_event, event.mouse_move)
