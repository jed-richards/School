from flask import (
    abort, Flask, jsonify, redirect, render_template, request,
    session, url_for
)
import os 

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')
