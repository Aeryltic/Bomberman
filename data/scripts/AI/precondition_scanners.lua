function empty_scanner(agent)
  
end

function thirst_scanner(agent)
  --needs = agent:needs()
  --goap = agent:goap()
  --if (needs ~= nil and cneeds ~= 0) then
    agent:goap():set_state("thirsty", agent:needs().thirst >= 50)
  --end
  --needs = nil
  --goap = nil
end

function hunger_scanner(agent)
  --needs = agent:needs()
  --goap = agent:goap()
  --if (needs ~= nil and cneeds ~= 0) then
    agent:goap():set_state("hungry", agent:needs().hunger >= 80)
  --end
  --needs = nil
  --goap = nil
end

function weariness_scanner(agent)
  --needs = agent:needs()
  --goap = agent:goap()
  --if (needs ~= nil and cneeds ~= 0) then
    agent:goap():set_state("weary", agent:needs().weariness >= 150)
  --end
  --needs = nil
  --goap = nil
end

function grain_scanner(agent)
  --goap = agent:goap()
  --bag = agent:bag()
  if (agent:bag() ~= nil and agent:bag() ~= 0) then
    agent:goap():set_state("have_grain", agent:bag():get_item("grains") > 0)
  end
  --needs = nil
  --goap = nil
end

function delivery_scanner(agent)
  agent:goap():set_state("grain_delivered", false)
end

function wood_scanner(agent)
  if (agent:bag() ~= nil and agent:bag() ~= 0) then
    agent:goap():set_state("have_wood", agent:bag():get_item("wood") > 0)
  end
end

function wood_delivery_scanner(agent)
  --goap = agent:goap()
  agent:goap():set_state("wood_delivered", false)
  --goap = nil
end

function enemy_scanner(agent)
  --goap = agent:goap()
  agent:goap():set_state("enemy_killed", false)
  --goap = nil
end