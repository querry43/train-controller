dofile('mcp4131.lc')

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


dofile('network.lc')

Network.ap_ssid = 'train control tower ' .. node.chipid();

Network:load()

dofile('webserver.lc')()

default_content_path = '/control.html'
