import requests
from sys import argv

port = 5000
if len(argv) > 1:
    port = int(argv[1])

vote = {
    'full_name' : 'Alfred Bumblewood',
    'person_type' : 'freeloader',
    'favorite_person' : 'Bumble Alfredwood',
}

r = requests.post('http://localhost:{}/favorite/'.format(port), data=vote)
print(r.text)
