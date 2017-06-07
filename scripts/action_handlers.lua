-- SDL_GetTicks() - funkcja z poziomu c++
--[[
function wait_time(ms)
  start_time = SDL_GetTicks()
  return function()
    return (start_time + ms >= SDL_GetTicks())
  end
end
]]


--[[
function do()
  return function f(agent, target, ms_passed)
    return true
  end
end
]]

function do_nothing() -- najprostsza funkcja, która nie robi nic
  -- zmienne inicjowane na starcie akcji
  return function(agent, target, ms_passed)
    return true
  end
end

-- podnoszenie ziaren przez mrówki
function pickup_grain()
  time_passed = 0
  duration = 500
  
  return function(agent, target, ms_passed)
    time_passed = time_passed + ms_passed
    if time_passed >= duration then
      target:destroy_me()
      return true
    end
    return false
  end
end

-- upuszczenie ziarna do gniazda
function deliver_grain()
  time_passed = 0
  duration = 500
  
  return function(agent, target, ms_passed)
    time_passed = time_passed + ms_passed
    if time_passed >= duration then
      e = target:getEnergyStore()
      if(e ~= nil) then 
        e.amount = e.amount + 100 
      end -- nie wiem czy ten if działa jak należy
      return true
    end
    return false
  end
end

-- zabicie wroga
function kill_enemy()
  time_passed = 0
  duration = 100
  
  return function(agent, target, ms_passed)
    time_passed = time_passed + ms_passed -- tak na prawdę to tutaj będzie coś bardziej skomplikowanego - jak wykonywanie pojedynczych ciosów, odejmowanie stoponiowe hp wroga itp
    if time_passed >= duration then
      target:destroy_me()
      return true
    end
    return false
  end
end