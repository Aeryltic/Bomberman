-- SDL_GetTicks() - funkcja z poziomu c++
--[[
function wait_time(ms)
  start_time = SDL_GetTicks()
  return function()
    return (start_time + ms >= SDL_GetTicks())
  end
end
]]

function pick_up(agent, target)
  
end
