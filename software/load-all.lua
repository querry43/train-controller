dofile('network.lua')
Network:load()

dofile('webserver.lua')()

WebServerPages['^/network'] = function(path, query) return dofile('webserver-network.lua')(path, query) end
WebServerPages['^/status'] = function(path, query) return dofile('webserver-status.lua')(path, query)  end
WebServerPages['^/$'] = function(path, query) return dofile('webserver-frame.lua')(path, query)  end
WebServerPages['^/menu'] = function(path, query) return dofile('webserver-menu.lua')(path, query)  end

WebServerPages['^/control'] = dofile('webserver-control.lua')