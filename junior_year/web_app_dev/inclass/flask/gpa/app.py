from flask import Flask, render_template
app = Flask(__name__)

@app.route('/gpa/<float:gpa>/')
def show_honors(gpa):
    return render_template('gpa.html', gpa=gpa)
