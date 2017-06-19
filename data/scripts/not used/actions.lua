-- to będzie trzeba trzymać w jakimś ładnym pliku i konfigurować specjalnym narzędziem
-- jakiś json, czy coś
action = -- dummy
{
  
  cost = 1,
  preconditions = {},
  effects = {},
  handler_init = function() return function() end end -- funkcja zwracająca funkcję, która będzie robiła to co ma być robione i zwracała czy zostało skończone
  
}

actions = 
{
  
  pickup_grain = {
    cost = 1,
    preconditions = {
      have_grain = false
    },
    effects = {
      have_grain = true
    },
    handler_init = wait_time(500) -- tylko że potrzeba czegoś co będzie to inicjować przy starcie akcji
  },

  deliver_grain = {
    cost = 1,
    preconditions = {
      have_grain = true,
      grain_delivered = false
    },
    effects = {
      have_grain = false,
      grain_delivered = true
    },
    handler_init = wait_time(500)
  }
  
}