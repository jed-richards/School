from flask import (
    abort, Flask, jsonify, redirect, render_template, request,
    session, url_for
)
import os

from random import randint

app = Flask(__name__)

fortunes = [
    'Good day for overcoming obstacles.  Try a steeplechase.',
    'Don\'t do drugs.',
    'You will be the victim of a bizarre joke.',
    'Courage is your greatest present need.',
]


@app.route('/')
def index():
    return render_template('index.html')

@app.route('/fortune/')
def fortune():
    return fortunes[ randint(0, len(fortunes)-1) ]
