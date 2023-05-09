from flask import (
    abort, Flask, jsonify, redirect, render_template, request,
    session, url_for
)
import os

app = Flask(__name__)

# set secret key
app.secret_key = b'kjahsfklajdjg;klsfhgljsklhdfgskjdfhlgskldfhjgljksdhflkjgd'

@app.route('/')
def index():
    return redirect(url_for('remember_form'))

@app.route('/remember/', methods=['GET'])
def remember_form():
    return render_template('remember-form.html')

@app.route('/remember/', methods=['POST'])
def remember():
    session['thing'] = request.form['thing']
    return render_template('remember.html', thing=session['thing'])

@app.route('/forget/', methods=['GET'])
def forget():
    if 'thing' in session:
        del session['thing']

    return render_template('remember.html', thing=None)

@app.route('/advertisement/')
def advert():
    if 'thing' in session:
        return render_template('advert.html', thing=session['thing'])
    else:
        return render_template('advert.html', thing=None)

