function empty_scanner(agent)
  
end

function thirst_scanner(agent)
  needs = agent:needs()
  goap = agent:goap()
  if (needs ~= nil and cneeds ~= 0) then
    goap:set_state("thirsty", needs.thirst >= 50)
  end
end

function hunger_scanner(agent)
  needs = agent:needs()
  goap = agent:goap()
  if (needs ~= nil and cneeds ~= 0) then
    goap:set_state("hungry", needs.hunger >= 80)
  end
end

function weariness_scanner(agent)
  needs = agent:needs()
  goap = agent:goap()
  if (needs ~= nil and cneeds ~= 0) then
    goap:set_state("weary", needs.weariness >= 150)
  end
end

function grain_scanner(agent)
  goap = agent:goap()
  bag = agent:bag()
  if (bag ~= nil and bag ~= 0) then
    goap:set_state("have_grain", bag.grains > 0)
  end
end

function delivery_scanner(agent)
  goap = agent:goap()
  goap:set_state("grain_delivered", false)
end

function enemy_scanner(agent)
  goap = agent:goap()
  goap:set_state("enemy_killed", false)
end