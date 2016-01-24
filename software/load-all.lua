dofile('network.lua')
Network:load()

dofile('webserver.lua')()

WebServerPages['^/network'] = dofile('webserver-network.lua')
WebServerPages['^/status'] = dofile('webserver-status.lua')
WebServerPages['^/$'] = dofile('webserver-frame.lua')
WebServerPages['^/menu'] = dofile('webserver-menu.lua')
WebServerPages['^/control'] = dofile('webserver-control.lua')