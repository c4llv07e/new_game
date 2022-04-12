
println("Welcome ", "to", " the ", "new_game", "!!!")

key_event = function ()
   println("hi")
end

mouse_event = function ()
   println("hello")
end

add_eventlistener(key_event, event.key_down)
add_eventlistener(mouse_event, event.mouse_move)
