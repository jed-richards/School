from flask import (
    abort, Flask, jsonify, redirect, render_template, request,
    session, url_for
)
from flask_sqlalchemy import SQLAlchemy
import os 
from pathlib import Path
from werkzeug.utils import secure_filename

IMAGE_DIR = 'static/img/profilephotos'

app = Flask(__name__)
app.secret_key = b'REPLACE_ME_x#pi*CO0@^z_beep_beep_boop_boop'

sqlite_uri = 'sqlite:///' + os.path.abspath(os.path.curdir) + '/test.db'
app.config['SQLALCHEMY_DATABASE_URI'] = sqlite_uri
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)

from models import Post, Profile, Like

# Get active profile
def get_user():
    if 'user' in session:
        #return jsonify(session['user'])
        return session['user']
    return None

# Check if user exists in session and return username
def get_username():
    if 'user' in session:
        return session['user']['username']
    return None

# Query database for a profile with username and password
# If there is, save the serialized user (table) in the session
def authenticate_login(username, password):
    user = Profile.query.filter_by(username=username, password=password).first()
    if user:
        session['user'] = user.serialize()
        return True
    return False

# Query database to see if username exists
def username_taken(username):
    return Profile.query.filter_by(username=username).first()

# the stuff that is NOT secure
def is_secure_route(request):
    return request.path not in [
            '/login/',
            '/logout/',
            '/profile/new/',
            '/profile/',
        ] and \
        not request.path.startswith('/static/')

# This initializes our app.
@app.before_first_request
def app_init():
    imgdir = Path(IMAGE_DIR)
    if not imgdir.exists():
        imgdir.mkdir(parents=True)

    try:
        Profile.query.all()
    except:
        db.create_all()

# Before each request, if trying to access a secure route, redirect to login_form
@app.before_request
def login_redirect():
    if get_user() == None and is_secure_route(request):
        return redirect(url_for('login_form'))

# redirect to main
@app.route('/', methods=['GET'])
def index():
    return redirect(url_for('main'))

# render main and pass user to the page
@app.route('/main/', methods=['GET'])
def main():
    return render_template('main.html', user=get_user())

# redirect to login_form
@app.route('/login/', methods=['GET'])
def login_form(messages=[]):
    return render_template('login_form.html', messages=messages)

# get login_form data and try to login
@app.route('/login/', methods=['POST'])
def login():
    if authenticate_login(request.form['username'], request.form['password']):
        return redirect(url_for('main'))
    else:
        return render_template('login_form.html', \
                messages=['Invalid username/password combination'])

# if there is an active user, remove them from session and render login_form
@app.route('/logout/')
def logout():
    if 'user' in session:
        del session['user']
        return render_template('login_form.html', \
            messages=['Logged out. Thanks for visiting this site.'])
    return redirect(url_for('login'))

# render create profile form
@app.route('/profile/new/', methods=['GET'])
def create_profile_form():
    return render_template('create_profile_form.html')

# get create_profile_form data and try to create a profile
@app.route('/profile/', methods=['POST'])
def create_profile():
    username = request.form['username']
    password = request.form['password']
    email = request.form['email']
    infile = request.files['image']

    if not infile:
        return render_template('create_profile_form.html', messages=['Invalid Image'])
        
    filename = secure_filename(infile.filename)

    if filename == "":
        return render_template('create_profile_form.html', messages=['Invalid Image'])

    filename = username + "_" + filename
    filepath = os.path.join(IMAGE_DIR, filename)

    if username_taken(username):
        return render_template('create_profile_form.html', messages=['Username Already Taken'])

    if username == "":
        return render_template('create_profile_form.html', messages=['Invalid Username'])

    if password == "":
        return render_template('create_profile_form.html', messages=['Invalid Password'])

    if email == "":
        return render_template('create_profile_form.html', messages=['Invalid Email'])
    

    if infile:
        infile.save(filepath)
        user = Profile(
            username=username,
            password=password,
            email=email,
            photofn=filepath,
            posts=[],
        )
        db.session.add(user)
        db.session.commit()
        return redirect(url_for('login'))
    else:
        return abort(400)


