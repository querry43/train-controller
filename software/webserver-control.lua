dofile('mcp4131.lua')

TrainControl = {}

TrainControl[1] = MCP4131:new({cs = 8, dir_pin = 3})
TrainControl[2] = MCP4131:new({cs = 2, dir_pin = 0})

for i=1,2 do
  TrainControl[i]:set(0)
  TrainControl[i].val = 0
  gpio.mode(TrainControl[i].dir_pin, gpio.OUTPUT)
  gpio.write(TrainControl[i].dir_pin, gpio.LOW)
end

return function (path, query)
  if(query.speed1) then
    for i=1,2 do
      local s = tonumber(query['speed' .. i])
      TrainControl[i]:set(100 - math.abs(s))
      TrainControl[i].val = s

      if(s < 0) then
        print('controller ' .. i .. ' speed ' .. s .. ' (reverse)')
        gpio.write(TrainControl[i].dir_pin, gpio.HIGH)
      else
        print('controller ' .. i .. ' speed ' .. s .. ' (forward)')
        gpio.write(TrainControl[i].dir_pin, gpio.LOW)
      end
    end
  end

  return 200,
     '<html>'
  ..   '<div style="text-align:center">'
  ..     '<h2>Train Control</h2>'
  ..     'Line 1: <output id="speed1_val" for="speed1"></output><br />'
  ..     '<input type="range" id="speed1" min="-100" max="100" step="10" style="width: 50%;" onchange="refresh()" value="' .. TrainControl[1].val .. '">'
  ..     '<br /><br />'
  ..     'Line 2: <output id="speed2_val" for="speed2"></output><br />'
  ..     '<input type="range" id="speed2" min="-100" max="100" step="10" style="width: 50%;" onchange="refresh()" value="' .. TrainControl[2].val .. '">'
  ..   '</div>'
  ..   '<script type="text/javascript">'
  ..     'function refresh() {'
  ..       'var queryParams = [];'
  ..       'for (i = 1; i <=2 ; i++) {'
  ..         'var speed = document.getElementById("speed" + i).value;'
  ..         'document.getElementById("speed" + i + "_val").value = speed + "%";'
  ..         'queryParams.push("speed" + i + "=" + speed);'
  ..       '}'
  ..       'var req = new XMLHttpRequest();'
  ..       'req.open("GET", "/control?" + queryParams.join("&"), true);'
  ..       'req.send();'
  ..     '}'
  ..     'refresh();'
  ..   '</script>'
  .. '</html>'
end
