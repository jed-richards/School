from http.server import *

from sys import argv  # allows command line arguments

# TODO
# 1. Hide this executable when serving content.

# This allows the use of: python3 python-httpd.py <PORT NUMBER>
# Otherwise the default is port 8000
if len(argv) >= 2:
    port = int(argv[1])
else:
    port = 8000


class MyHTTPRequestHandler(SimpleHTTPRequestHandler):
    def __init__(self, request, client_address, server):
        SimpleHTTPRequestHandler.__init__(self, request, client_address, server)

    def do_GET(self):
        print("Serving %s " % self.path)
        print("Serving from %s " % self.translate_path(self.path))
        SimpleHTTPRequestHandler.do_GET(self)



def run(server_class=HTTPServer, handler_class=MyHTTPRequestHandler):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

print(f'Starting HTTP server on port {port}.')
run()
print('Running...')

# Run and visit http://localhost:8000/ in your web browser
