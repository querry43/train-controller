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
