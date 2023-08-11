from flask import (
    abort, Flask, jsonify, redirect, render_template, request,
    session, url_for
)
import os 

app = Flask(__name__)
app.secret_key = b'REPLACE_ME_x#pi*CO0@^z_beep_beep_boop_boop'


def validate(d, keys):
    for k in keys:
        if k not in d:
            raise Exception(f'{d} does not contain {k}')

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/api/login/', methods=['POST'])
def api_login():
    try:
        validate(request.form, ['username', 'password'])
        u, p = request.form['username'], request.form['password']
        if u == 'thor' and p == 'mjolnir':
            session['username'] = u
            return 'ok'
        else:
            return 'fail'

    except Exception as e:
        return str(e), 400

@app.route('/api/avengers/', methods=['GET'])
def api_avengers():
    try:
        validate(session, ['username'])

        return jsonify(['Captain America', 'Iron Man', 'Black Widow'])

    except:
        return 'Not authenticated', 403

