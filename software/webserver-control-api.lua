dofile('mcp4131.lua')

TrainControl = {}

TrainControl[0] = MCP4131:new({cs = 8, dir_pin = 3})
TrainControl[1] = MCP4131:new({cs = 2, dir_pin = 0})

num_train_lines = 2

for i=0,num_train_lines-1 do
  TrainControl[i]:set(0)
  TrainControl[i].val = 0
  gpio.mode(TrainControl[i].dir_pin, gpio.OUTPUT)
  gpio.write(TrainControl[i].dir_pin, gpio.LOW)
end

return function (path, query)
  local response = ''

  for i=0,num_train_lines-1 do
    local s = query['speed[' .. i .. ']']
    if(s) then
      local si = tonumber(s)
      TrainControl[i]:set(100 - math.abs(si))
      TrainControl[i].val = si
    end

    if(i>0) then response = response .. ',' end

    response = response .. TrainControl[i].val
  end

  return 200, '{"num_train_lines":' .. num_train_lines ..',"speed":[' .. response .. ']}'
end
