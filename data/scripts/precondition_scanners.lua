function empty_scanner(agent)
  
end

function needs_to_drink(agent)
  needs = agent:needs()
  goap = agent:goap()
  if (needs ~= nil and cneeds ~= 0) then
    if (needs.thirst >= 50) then
      --print("thirsty")
      goap:set_state("thirsty", true)
      --print("ok")
    else
      goap:set_state("thirsty", false)
    end
  end
end

function needs_to_eat(agent)
  needs = agent:needs()
  goap = agent:goap()
  if (needs ~= nil and cneeds ~= 0) then
    if (needs.hunger >= 80) then
      --print("hungry")
      goap:set_state("hungry", true)
      --print("ok")
    else
      goap:set_state("hungry", false)
    end
  end
end

function needs_to_rest(agent)
  needs = agent:needs()
  goap = agent:goap()
  if (needs ~= nil and cneeds ~= 0) then
    if (needs.weariness >= 150) then
      --print("weary")
      goap:set_state("weary", true)
      --print("ok")
    else
      goap:set_state("weary", false)
    end
  end
end