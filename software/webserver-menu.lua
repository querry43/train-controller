return function (path, query)
  return 200,
     '<html>'
  ..   '<ul>'
  ..     '<li><a href="/status" target="content">status</a></li>'
  ..     '<li><a href="/network" target="content">network</a></li>'
  ..     '<li><a href="/control" target="content">train control</a></li>'
  ..   '</ul>'
  .. '</html>'
end