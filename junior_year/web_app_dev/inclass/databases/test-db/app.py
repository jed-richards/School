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

# takes app and makes it a db object
db = SQLAlchemy(app)

#from models import User, add_user
from models import *

@app.before_first_request
def setup():
    try:
        User.query.all()
    except:
        db.create_all()

@app.route('/')
def index():
    return redirect(url_for('get_all_users'))

@app.route('/users/form/', methods=['GET'])
def user_form():
    return render_template('user_form.html')

@app.route('/users/', methods=['POST'])
def create_user():
    # Let SQLAlchemy create a user and then redirect to get single user
    user = add_user(request.form)
    return redirect(url_for('get_single_user', the_id=user.id))

@app.route('/users/', methods=['GET'])
def get_all_users():
    users = get_users()
    print(users)
    return render_template('users.html', users=users)

@app.route('/users/<int:the_id>/', methods=['GET'])
def get_single_user(the_id):
    user = get_user(the_id)
    if user == None:
        abort(404)
    else:
        return render_template('user.html', user=user)

@app.route('/users/<int:the_id>/delete/', methods=['GET', 'DELETE'])
def delete_user(the_id):
    username = del_user(the_id)
    print(f'del user {username}')
    users = get_users()
    return render_template('users.html', users=users, username=username)

# decorator for 404 error
@app.errorhandler(404)
def page_not_found(e):
    # note that we set the 404 status explicitly
    return render_template('404.html'), 404
