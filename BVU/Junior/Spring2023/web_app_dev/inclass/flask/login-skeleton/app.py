from flask import abort, Flask, request
app = Flask(__name__)

# matches things like GET /login?username=phil&password=12345
@app.route('/login/', methods=['GET'])
def login():
    username = request.args.get('username')
    password = request.args.get('password')
    if not username or not password:
        abort(400)
    else:
        return f'Welcome {username}'
