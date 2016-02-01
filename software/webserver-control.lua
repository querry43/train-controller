dofile('mcp4131.lua')

TrainControl = {}

TrainControl[1] = MCP4131:new({cs = 8})
TrainControl[2] = MCP4131:new({cs = 2})
TrainControl[3] = MCP4131:new({cs = 4})

for i=1,3 do
  TrainControl[i].val = 0
  TrainControl[i].reverse = false
end

return function (path, query)
  if(query.speed1) then
    for i=1,3 do
      TrainControl[i]:set(query['speed' .. i])
      TrainControl[i].val = query['speed' .. i]
      TrainControl[i].reverse = query['rev' .. i] == 'true'
    end
  end

  return 200,
     '<html>'
  ..   '<div style="text-align:center">'
  ..     '<h2>Train Control</h2>'
  ..     '<input type="range" id="speed1" min="0" max="100" step="10" onchange="refresh()" value="' .. TrainControl[1].val .. '">'
  ..     '<input type="text" id="speed1_val" size="1" disabled value="' .. TrainControl[1].val .. '%">'
  ..     '<input type="checkbox" id="rev1" onchange="refresh()" ' .. (TrainControl[1].reverse and 'checked' or '') .. '>Reverse'
  ..     '<br />'
  ..     '<input type="range" id="speed2" min="0" max="100" step="10" onchange="refresh()" value="' .. TrainControl[2].val .. '">'
  ..     '<input type="text" id="speed2_val" size="1" disabled value="' .. TrainControl[2].val .. '%">'
  ..     '<input type="checkbox" id="rev2" onchange="refresh()" ' .. (TrainControl[2].reverse and 'checked' or '') .. '>Reverse'
  ..     '<br />'
  ..     '<input type="range" id="speed3" min="0" max="100" step="10" onchange="refresh()" value="' .. TrainControl[3].val .. '">'
  ..     '<input type="text" id="speed3_val" size="1" disabled value="' .. TrainControl[3].val .. '%">'
  ..     '<input type="checkbox" id="rev3" onchange="refresh()" ' .. (TrainControl[3].reverse and 'checked' or '') .. '>Reverse'
  ..   '</div>'
  ..   '<script type="text/javascript">'
  ..     'function refresh() {'
  ..       'var queryParams = [];'
  ..       'for (i = 1; i <=3 ; i++) {'
  ..         'var speed = document.getElementById("speed" + i).value;'
  ..         'document.getElementById("speed" + i + "_val").value = speed + "%";'
  ..         'queryParams.push("speed" + i + "=" + speed);'
  ..         'queryParams.push("rev" + i + "=" + document.getElementById("rev" + i).checked);'
  ..       '}'
  ..       'var req = new XMLHttpRequest();'
  ..       'req.open("GET", "/control?" + queryParams.join("&"), true);'
  ..       'req.send();'
  ..     '}'
  ..   '</script>'
  .. '</html>'
end
