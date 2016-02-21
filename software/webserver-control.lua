dofile('mcp4131.lua')

TrainControl = {}

TrainControl[1] = MCP4131:new({cs = 8})
TrainControl[2] = MCP4131:new({cs = 2})
TrainControl[3] = MCP4131:new({cs = 4})

for i=1,3 do
  TrainControl[i]:set(0)
  TrainControl[i].val = 0
end

return function (path, query)
  if(query.speed1) then
    for i=1,3 do
      local s = query['speed' .. i]
      TrainControl[i]:set(100 - math.abs(s))
      TrainControl[i].val = s
    end
  end

  return 200,
     '<html>'
  ..   '<div style="text-align:center">'
  ..     '<h2>Train Control</h2>'
  ..     '<input type="range" id="speed1" min="-100" max="100" step="10" style="width: 50%;" onchange="refresh()" value="' .. TrainControl[1].val .. '">'
  ..     '<output id="speed1_val" for="speed1"></output>'
  ..     '<br />'
  ..     '<input type="range" id="speed2" min="-100" max="100" step="10" style="width: 50%;" onchange="refresh()" value="' .. TrainControl[2].val .. '">'
  ..     '<output id="speed2_val" for="speed2"></output>'
  ..     '<br />'
  ..     '<input type="range" id="speed3" min="-100" max="100" step="10" style="width: 50%;" onchange="refresh()" value="' .. TrainControl[3].val .. '">'
  ..     '<output id="speed3_val" for="speed3"></output>'
  ..   '</div>'
  ..   '<script type="text/javascript">'
  ..     'function refresh() {'
  ..       'var queryParams = [];'
  ..       'for (i = 1; i <=3 ; i++) {'
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
