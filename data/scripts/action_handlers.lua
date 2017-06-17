function do_nothing(agent, target, ms_passed) -- najprostsza funkcja, która nie robi nic
  return true
end

-- podnoszenie ziaren przez mrówki
function pickup_grain(agent, target, time_passed)
  if time_passed >= 500 then
    target:destroy_me()
    return true
  end
  return false
end

-- upuszczenie ziarna do gniazda
function deliver_grain(agent, target, time_passed)
  if time_passed >= 500 then
    e = target:energy_store()
    if(e ~= nil and e ~= 0) then -- nie wiem czy ten if wogóle działa jak należy
      e.amount = e.amount + 100 
    end
    return true
  end
  return false
end

-- zabicie wroga
function kill_enemy(agent, target, time_passed)
  if time_passed >= 100 then
    target:destroy_me()
    return true
  end
  return false
end

-- picie
function drink_something(agent, target, time_passed)
  --print("perform drinking")
  agent:aspect():set_color(50, 50, 200)
  if time_passed >= 2000 then
    --print("drinking")
    agent:needs().thirst = 0
    agent:aspect():reset_color()
    return true
  end
  return false
end

-- jedzenie
function eat_something(agent, target, time_passed)
  agent:aspect():set_color(50, 150, 50)
  if time_passed >= 5000 then
      --print("eating")
      agent:needs().hunger = 0
      agent:aspect():reset_color()
    return true
  end
  return false
end

-- odpoczywanie
function rest_for_a_while(agent, target, time_passed)
  agent:aspect():set_color(50, 50, 50)
  if time_passed >= 10 then
      --print("resting")
      agent:needs().weariness = 0
      agent:aspect():reset_color()
    return true
  end
  return false
end

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

--[[
function do_nothing() -- najprostsza funkcja, która nie robi nic
  -- zmienne inicjowane na starcie akcji
  return function(agent, target, ms_passed)
    return true
  end
end

-- podnoszenie ziaren przez mrówki
function pickup_grain()
  --print("init pickup_grain")
  --local time_passed = 0 -- to (i wszystkie pozostałe zmienne lokalne) powoduje memory leak i HeapCorruptionException, fajnie
  --local duration = 500
  time_passed = 0 -- to (i wszystkie pozostałe zmienne lokalne) powoduje memory leak i HeapCorruptionException, fajnie
  duration = 500
  
  return function(agent, target, ms_passed)
    --print("picking up grain")
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
  --print("init deliver_grain")
  time_passed = 0
  duration = 500
  
  return function(agent, target, time_passed)
    time_passed = time_passed + ms_passed
    if time_passed >= duration then
      e = target:getEnergyStore()
      if(e ~= nil) then -- nie wiem czy ten if wogóle działa jak należy
        print("got energy store")
        e.amount = e.amount + 100 
      end
      return true
    end
    return false
  end
end

-- zabicie wroga
function kill_enemy()
  --print("init kill_enemy")
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

-- test
function test()
  local v = nil
  for i=1,100000 do
    v = kill_enemy()
  end
end

test()
]]