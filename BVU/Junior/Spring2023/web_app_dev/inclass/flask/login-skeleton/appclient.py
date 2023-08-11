# appclient.py

# Documentation for 'request' library can be found at:
# https://requests.readthedocs.io/en/master/user/quickstart/

import requests
from sys import argv

port = 5000
if len(argv) > 1:
    port = int(argv[1])

credentials = {
    'username': 'jtrich',
    'password': 'pizza',
}

# params is important
r = requests.get(f'http://localhost:{port}/login/', params=credentials)
print(r.text)
