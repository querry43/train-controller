dofile('mcp4131.lua')

TrainControl = {}
TrainControl[1] = MCP4131:new({cs = 8})
TrainControl[1]:set(0)
TrainControl[1].val = 0

return function (path, query)
  if(query.speed) then
    TrainControl[1]:set(query.speed)
    TrainControl[1].val = query.speed
  end

  return 200,
     '<html>'
  ..   '<script type="text/javascript">'
  ..     'function refresh() {'
  ..       'var req = new XMLHttpRequest();'
  ..       'req.open("GET", "/control?speed=" + document.getElementById("speed1").value, true);'
  ..       'req.send();'
  ..     '}'
  ..   '</script>'
  ..   '<div style="text-align:center">'
  ..     '<h2>Train Control</h2>'
  ..     '<input type="range" id="speed1" min="0" max="100" step="10" onchange="refresh()" value="' .. TrainControl[1].val .. '">'
  ..   '</div>'
  .. '</html>'
end
