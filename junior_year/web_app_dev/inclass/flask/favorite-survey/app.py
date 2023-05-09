from flask import (
    abort, Flask, jsonify, redirect, render_template, request,
    session, url_for
)
import os

app = Flask(__name__)

@app.route('/favorite-form/', methods=['GET'])
def favorite_form():
    return render_template('favorite.html')

@app.route('/favorite/', methods=['POST'])
def process_form():
    full_name = request.form.get('full_name')
    person_type = request.form.get('person_type')
    favorite_person = request.form.get('favorite_person')

    with open('results.txt', 'a') as outfile:
        outfile.write(f'{full_name},{person_type},{favorite_person}\n')

    return render_template('success.html', name=full_name)
