from flask import (
    abort, Flask, jsonify, redirect, render_template, request,
    session, url_for
)
from werkzeug.utils import secure_filename #something we will use in future
import os

UPLOADS_DIR = 'static/uploads'   # uppercase because variable is static

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('form.html')

@app.route('/image/', methods=['POST'])
def upload_image():
    title = request.form['thetitle']
    imageFile = request.files['thefile']
    filePath = UPLOADS_DIR + '/' + imageFile.filename # .filepath gets filename
    imageFile.save(filePath) 

    # constructs a link to file
    link = url_for('static', filename=f'uploads/{imageFile.filename}')

    return f'View your file <a href="{link}">here!</a>' 

@app.route('/images/', methods=['GET'])
def get_all_images():
    fileNames = os.listdir(UPLOADS_DIR)
    return render_template('show_all.html', fileNames=fileNames)
