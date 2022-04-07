
println("Welcome ", "to", " the ", "new_game", "!!!")

prtSomething = function ()
   println("hi")
end


add_eventlistener(prtSomething, "12")
add_eventlistener(prtSomething, "12")
ref = add_eventlistener(prtSomething, "12")
add_eventlistener(prtSomething, "12")
del_eventlistener(ref)
