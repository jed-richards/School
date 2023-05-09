
from flask import Flask
app = Flask(__name__)

@app.route('/')
def index():
    return 'Index Page'

@app.route('/hello/')
def hello():
    return 'Hello World!'

@app.route('/add/<int:x>/<int:y>')
def add(x,y):
    return f'<strong>{x+y}</strong>'

@app.route('/sub/<int:x>/<int:y>')
def sub(x,y):
    return f'<em>{x-y}</em>'



