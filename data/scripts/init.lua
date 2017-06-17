current_path = string.gsub(debug.getinfo(1).short_src, "^(.+\\)[^\\]+$", "%1")
print("current path is " .. current_path)

dofile("data/scripts/config.lua")
dofile("data/scripts/script.lua")
dofile("data/scripts/entities.lua")
dofile("data/scripts/action_handlers.lua")
dofile("data/scripts/precondition_scanners.lua")

function initSettings()

end

function reload()

end