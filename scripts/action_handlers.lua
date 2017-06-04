-- SDL_GetTicks() - funkcja z poziomu c++
--[[
function wait_time(ms)
  start_time = SDL_GetTicks()
  return function()
    return (start_time + ms >= SDL_GetTicks())
  end
end
]]

function do_nothing(agent, target)
  return true
end

function pickup_grain(agent, target)
  target:destroy_me()
  return true
end

function deliver_grain(agent, target)
  e = target:getEnergyStore()
  if(e ~= nil) then e.amount = e.amount + 100 end -- nie wiem czy ten if działa jak należy
end

function kill_enemy(agent, target)
  target:destroy_me()
  return true
end
