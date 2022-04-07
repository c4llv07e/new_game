
println("Welcome ", "to", " the ", "new_game", "!!!")

prtSomething = function ()
   println("hi")
end

ref = add_eventlistener(prtSomething, "12")
del_eventlistener(ref)
