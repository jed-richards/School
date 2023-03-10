from http.server import *
from sys import argv      # allows command line arguments
import time

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

        # If path starts with /dyn/ then jump in only if the path is not only /dyn/
        if self.path.startswith('/dyn/') and self.path != ('/dyn/'):

            # create file variable as path to file
            file = self.translate_path(self.path)

            # split the path and change the file name to 'newfile'
            sp = file.split('/')
            sp[-1] = 'newfile.html'

            # finally join the split list seperated by '/' (reconstruct path)
            newfile = '/'.join(sp)

            '''
            Open the file at designated path to read and open newfile to write to.
            Then copy infile into outfile, replacing '{{sysdate}}' with time.asctime().
            '''
            with open(file, 'r') as inf, open(newfile, 'w') as outf:
                outf.write(inf.read().replace('{{sysdate}}', time.asctime()))

            # Now, manually change path to the newfile and call do_GET on it
            self.path = '/dyn/newfile.html'

        SimpleHTTPRequestHandler.do_GET(self)


def run(server_class=HTTPServer, handler_class=MyHTTPRequestHandler):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

print(f'Starting HTTP server on port {port}.')
run()
print('Running...')

# Run and visit http://localhost:8000/ in your web browser
