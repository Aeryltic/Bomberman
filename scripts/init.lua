current_path = string.gsub(debug.getinfo(1).short_src, "^(.+\\)[^\\]+$", "%1")
print("current path is " .. current_path)

dofile("scripts/config.lua")
dofile("scripts/script.lua")
dofile("scripts/entities.lua")
dofile("scripts/action_handlers.lua")

function initSettings()

end

function reload()

end