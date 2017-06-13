local socket = require'socket'

get_time = socket.gettime

function prepare_action() -- tego typu funkcje bedą wywoływane przy rozpoczynaniu akcji
  start = get_time()
  duration = .500
  function action()
    return get_time() >= start + duration
  end
  return action
end


a = prepare_action()
start_at = get_time()
while not a() do 
  --io.write("+") 
end
io.write('a: end after: ' .. get_time() - start_at .. '\n')

b = prepare_action()
start_at = get_time()
while not b() do 
  --io.write("+") 
end
io.write('b: end after: ' .. get_time() - start_at .. '\n')