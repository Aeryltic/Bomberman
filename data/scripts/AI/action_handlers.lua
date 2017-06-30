-- timestep - stała z poziomu C++

function do_nothing(agent, target, ms_passed) -- najprostsza funkcja, która nie robi nic
  return true
end

function go_to(agent, target, ms_passed)
  agent:movement():set_speed(agent:physical_form().pos:movement_step(target:physical_form().pos, agent:movement().max_speed / timestep))
  return false
end

-- podnoszenie ziaren przez mrówki
function pickup_grain(agent, target, ms_passed)
  if agent:goap():time_passed() >= 500 then
    target:destroy_me()
    agent:bag():set_item("grains", agent:bag():get_item("grains") + 1)
    return true
  end
  return false
end

-- upuszczenie ziarna do gniazda
function deliver_grain(agent, target, ms_passed)
  if agent:goap():time_passed() >= 500 then
    --e = target:energy_store()
    --if(e ~= nil and e ~= 0) then -- nie wiem czy ten if wogóle działa jak należy
      target:energy_store().amount = target:energy_store().amount + 100 
      agent:bag():set_item("grains", agent:bag():get_item("grains") - 1)
    --end
    --e = nil
    return agent:bag():get_item("grains") == 0
  end
  return false
end

-- 
function chop_wood(agent, target, ms_passed) -- tu już jest problem, bo nie mogę zrobić dynamicznego dodawania względem czasu, bo co jeśli już miał?
  if agent:goap():time_passed() >= 1500 then
    c = target:property():get("condition")
    if c > 10 then
      agent:bag():set_item("wood", agent:bag():get_item("wood") + 10)
      target:property():set("condition", target:property():get("condition") - 10)
    else
      agent:bag():set_item("wood", agent:bag():get_item("wood") + c)
      target:property():set("condition", 0)
      target:destroy_me()
    end
    return true
  end
  return false
end

-- 
function deliver_wood(agent, target, ms_passed)
  if agent:goap():time_passed() >= 500 then
    --e = target:energy_store()
    --if(e ~= nil and e ~= 0) then -- nie wiem czy ten if wogóle działa jak należy
      --target:energy_store().amount = target:energy_store().amount + 100 
      target:bag():set_item("wood", agent:bag():get_item("wood"))
      agent:bag():set_item("wood", 0)
    --end
    --e = nil
    return true
  end
  return false
end

-- zabicie wroga
function kill_enemy(agent, target, ms_passed)
  if agent:goap():time_passed() >= 100 then
    target:destroy_me()
    return true
  end
  return false
end

-- picie
function drink_something(agent, target, ms_passed)
  --print("perform drinking")
  agent:aspect():set_color(50, 50, 200)
  if agent:goap():time_passed() >= 2000 then
    --print("drinking")
    agent:needs().thirst = 0
    agent:aspect():reset_color()
    return true
  end
  return false
end

-- jedzenie
function eat_something(agent, target, ms_passed)
  agent:aspect():set_color(150, 150, 50)
  if agent:goap():time_passed() >= 5000 then
      --print("eating")
      agent:needs().hunger = 0
      agent:aspect():reset_color()
    return true
  end
  return false
end

-- odpoczywanie
function rest_for_a_while(agent, target, ms_passed)
  agent:aspect():set_color(50, 50, 50)
  if agent:goap():time_passed() >= 10000 then
      --print("resting")
      agent:needs().weariness = 0
      agent:aspect():reset_color()
    return true
  end
  return false
end
