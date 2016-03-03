dofile('network.lua')

Network.ap_ssid = 'train control tower ' .. node.chipid();

Network:load()

dofile('webserver.lua')()

content_path = '/control'

WebServerPages['^/network'] = function(path, query) return dofile('webserver-network.lua')(path, query) end
WebServerPages['^/status'] = function(path, query) return dofile('webserver-status.lua')(path, query)  end
WebServerPages['^/$'] = function(path, query) return dofile('webserver-frame.lua')(path, query)  end
WebServerPages['^/menu'] = function(path, query) return dofile('webserver-menu.lua')(path, query)  end

WebServerPages['^/control'] = function(path, query)
  file.open('webserver-control.html')
  local contents = ''
  local line = ''
  repeat
    contents = contents .. line
    line = file.readline()
  until line == nil
  file.close()

  return 200, contents
end

WebServerPages['^/control1.js'] = function(path, query)
  file.open('webserver-control1.js')
  local contents = ''
  local line = ''
  repeat
    contents = contents .. line
    line = file.readline()
  until line == nil
  file.close()

  return 200, contents
end

WebServerPages['^/control2.js'] = function(path, query)
  file.open('webserver-control2.js')
  local contents = ''
  local line = ''
  repeat
    contents = contents .. line
    line = file.readline()
  until line == nil
  file.close()

  return 200, contents
end

WebServerPages['^/control/api'] = dofile('webserver-control-api.lua')
