dofile('network.lua')

Network.ap_ssid = 'train control tower ' .. node.chipid();

Network:load()

dofile('webserver.lua')()

content_path = '/control'

WebServerPages['^/network'] = function(path, query) return dofile('webserver-network.lua')(path, query) end
WebServerPages['^/status'] = function(path, query) return dofile('webserver-status.lua')(path, query)  end
WebServerPages['^/$'] = function(path, query) return dofile('webserver-frame.lua')(path, query)  end
WebServerPages['^/menu'] = function(path, query) return dofile('webserver-menu.lua')(path, query)  end

WebServerPages['^/control'] = dofile('webserver-control.lua')
