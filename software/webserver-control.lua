dofile('mcp4131.lua')

TrainControl = {}
TrainControl[1] = MCP4131:new({cs = 8})
TrainControl[1]:set(0)

return function (path, query)
  if (query.speed == 'stop') then TrainControl[1]:set(0)
  elseif (query.speed == 'slow') then TrainControl[1]:set(50)
  elseif (query.speed == 'fast') then TrainControl[1]:set(100)
  end

  return 200,
     '<html>'
  ..   '<div style="text-align:center">'
  ..     '<form method="get">'
  ..       '<h2>Train Control</h2>'
  ..       '<input type="submit" name="speed" value="stop">'
  ..       '<input type="submit" name="speed" value="slow">'
  ..       '<input type="submit" name="speed" value="fast">'
  ..     '</form>'
  ..   '</div>'
  .. '</html>'
end
