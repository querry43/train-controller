dofile('network.lua')
Network:load()
dofile('webserver.lua')()
dofile('webserver-network-config.lua')
dofile('webserver-status.lua')
dofile('mcp4131.lua')

pot1 = MCP4131:new({cs = 8})
pot1:set(0)

WebServerPages['/set_speed'] = function (s, path, query_string)
    local speed = path:match('/set_speed/(%d+)')
    if speed then
        s:send(WebServer.status_success .. 'set_speed: ' .. speed)
        pot1:set(speed)
    else
        s:send(WebServer.status_error .. 'could not parse speed from path: ' .. path)
    end
end
