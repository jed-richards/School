from flask import (
    abort, Flask, jsonify, redirect, render_template, request,
    session, url_for
)
from flask_sqlalchemy import SQLAlchemy
import os 

app = Flask(__name__)
app.secret_key = b'REPLACE_ME_x#pi*CO0@^z_beep_beep_boop_boop'

sqlite_uri = 'sqlite:///' + os.path.abspath(os.path.curdir) + '/test.db'
app.config['SQLALCHEMY_DATABASE_URI'] = sqlite_uri
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)

def get_username():
    if 'username' in session:
        return session['username']

    return None

def authenticate(username, password):
    if username == 'cartman' and password == 'beefcake':
        session['username'] = username
        return True

    return False

def is_secure_route(request):
    return request.path not in ['/login/', '/logout/'] and \
        not request.path.startswith('/static/')

@app.before_request
def login_redirect():
    if get_username() == None and is_secure_route(request):
        return redirect(url_for('login_form'))

@app.route('/')
def index():
    return redirect(url_for('main'))

@app.route('/main/')
def main():
    return render_template('main.html', username=get_username())

@app.route('/login/', methods=['GET'])
def login_form():
    return render_template('login_form.html')

@app.route('/login/', methods=['POST'])
def login():
    if authenticate(request.form['username'], request.form['password']):
        return redirect(url_for('main'))
    else:
        return render_template('login_form.html', \
                messages=['Invalid username/password combination'])

@app.route('/logout/')
def logout():
    if 'username' in session:
        del session['username']
    return render_template('login_form.html', \
            messages=['Logged out. Thanks for visiting this site.'])

