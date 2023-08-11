from flask import (
    abort, Flask, jsonify, redirect, render_template, request,
    session, url_for
)
from flask_sqlalchemy import SQLAlchemy
import os 
import random
import string

app = Flask(__name__)
app.secret_key = b'#pi*CO0@^z_beep_beep_boop_boop'

sqlite_uri = 'sqlite:///' + os.path.abspath(os.path.curdir) + '/hpcvc.db'
app.config['SQLALCHEMY_DATABASE_URI'] = sqlite_uri
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)

from models import User, Computer

'''
This code implements the following routes:

  POST /api/register/
  POST /api/login/
  /api/login/  (any method)
  GET /
  GET /api/status/<int:computer_id>/
  GET /api/statuses/
  PUT /api/reserve/<int:computer_id>/
  PUT /api/release/<int:computer_id>/

See each route implementation below for required parameters and
proper return values.

'''

with app.app_context():
    try:
        Computer.query.all()
    except:
        db.create_all()
        default_user = User(
            username='hpcvc_default_user',
            password=''.join(random.choices(string.ascii_uppercase +
                            string.digits, k=16)),
            email='donotreply@bvu.edu',
        )
        db.session.add(default_user)
        db.session.commit()
        computers = [
            Computer(id=1, user_id=default_user.id),
            Computer(id=2, user_id=default_user.id),
            Computer(id=3, user_id=default_user.id),
            Computer(id=4, user_id=default_user.id),
            Computer(id=5, user_id=default_user.id),
            Computer(id=6, user_id=default_user.id),
            Computer(id=7, user_id=default_user.id),
            Computer(id=8, user_id=default_user.id),
        ]
        for computer in computers:
            db.session.add(computer)
        db.session.commit()

        # DEBUGGING
        u = User(
            username='jbshep',
            password='a',
            email='shepherd@bvu.edu',
        )
        db.session.add(u)
        db.session.commit()


DEFAULT_USER_ID = 1


def get_user_id():
    return session.get('user_id')


def validate(d, keys):
    for k in keys:
        if k not in d:
            raise Exception(f'{d} does not contain {k}')


# Create new user if username does not already exist
@app.route('/api/register/', methods=['POST'])
def register():
    try:
        validate(request.form, ['username', 'password', 'email'])
        u, p, e = request.form['username'], request.form['password'], \
                  request.form['email']

        if not User.query.filter_by(username=u).first() == None:
            return 'fail - duplicate username'

        new_user = User(username=u, password=p, email=e)
        db.session.add(new_user)
        db.session.commit()
        return 'ok'

    except Exception as e:
        return str(e), 400


# Login user is username and password in login form
@app.route('/api/login/', methods=['POST'])
def login():
    try:
        validate(request.form, ['username', 'password'])
        u, p = request.form['username'], request.form['password']
        user = User.query.filter_by(username=u, password=p).first()
        if user:
            session['user_id'] = user.id
            print(f"user_id: {session['user_id']}")
            return 'ok'
        else:
            return 'fail'

    except Exception as e:
        return str(e), 400


# Logout user
@app.route('/api/logout/')
def logout():
    if 'user_id' in session:
        del session['user_id']

    return 'ok'


# Render the main page
@app.route('/')
def index():
    return render_template('app.html')


# Returns whether the computer based on computer_id is reserved (True or False)
@app.route('/api/status/<int:computer_id>/', methods=['GET'])
def get_status(computer_id):
    try:
        validate(session, ['user_id'])

        # Maybe want the full computer serialized object
        #return jsonify(Computer.query.get(computer_id).is_reserved)
        return jsonify(Computer.query.get(computer_id).serialize())

    except:
        return 'Not authenticated', 403


# Gets the statuses of all computers
@app.route('/api/statuses/', methods=['GET'])
def get_all_statuses():
    ''' Returns a JSON array of Computer objects, like this:

        [
            {
                id: 1,
                userID: 1,
                isReserved: false
            },
            // ...
            {
                id: 8,
                userID: 2,
                isReserved: true
            },
        ]
    '''
    try:
        validate(session, ['user_id'])
    except:
        return 'Not authenticated', 403

    computers = list(map(lambda c: c.serialize(), Computer.query.all()))
    return jsonify(computers)


# 
@app.route('/api/reserve/<int:computer_id>/', methods=['PUT'])
def reserve(computer_id):
    try:
        validate(session, ['user_id'])
    except:
        return 'Not authenticated', 403

    desired_computer = Computer.query.get(computer_id)

    # can't reserve a computer that is already reserved
    if desired_computer.is_reserved:
        return 'fail'

    # update state of desired computer
    desired_computer.is_reserved = True
    desired_computer.user_id = get_user_id()
    db.session.add(desired_computer)
    db.session.commit()
    return 'ok'



@app.route('/api/release/<int:computer_id>/', methods=['PUT'])
def release(computer_id):
    try:
        validate(session, ['user_id'])
    except:
        return 'Not authenticated', 403

    desired_computer = Computer.query.get(computer_id)

    # maybe check if computer is being reserved by the active user
    if not desired_computer.user_id == session['user_id']:
        return 'fail'

    if not desired_computer.is_reserved:
        return 'fail'

    desired_computer.is_reserved = False
    desired_computer.user_id = DEFAULT_USER_ID
    db.session.add(desired_computer)
    db.session.commit()
    return 'ok'

