from flask import (
    abort, Flask, jsonify, redirect, render_template, request,
    session, url_for
)
from flask_sqlalchemy import SQLAlchemy
from werkzeug.utils import secure_filename
import os 

app = Flask(__name__)
app.secret_key = b'REPLACE_ME_x#pi*CO0@^z_beep_beep_boop_boop'

sqlite_uri = 'sqlite:///' + os.path.abspath(os.path.curdir) + '/memes.db'
app.config['SQLALCHEMY_DATABASE_URI'] = sqlite_uri
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)

IMAGE_DIR = 'static/img/uploads'

from models import Post

@app.before_first_request
def app_init():
    try:
        Post.query.all()
    except:
        db.create_all()

@app.route('/')
def index():
    return render_template('app.html')

@app.route('/api/posts/', methods=['GET'])
def get_posts():
    posts = list(map(lambda p: p.serialize(), Post.query.all()))
    return jsonify(posts)

@app.route('/api/posts/', methods=['POST'])
def create_post():
    infile = request.files['imagefile']
    filename = secure_filename(infile.filename)
    filepath = os.path.join(IMAGE_DIR, filename)
    if infile:
        infile.save(filepath)
        newpost = Post(title=request.form['title'], imagepath=filename, votes=0)
        db.session.add(newpost)
        db.session.commit()
        return jsonify(newpost.serialize())
    else:
        return abort(400)


@app.route('/api/posts/<int:postid>/upvote/', methods=['POST'])
def upvote(postid):
    post = Post.query.get(postid)
    post.votes += 1
    db.session.add(post)
    db.session.commit()
    return jsonify(post.serialize())

@app.route('/api/posts/<int:postid>/downvote/', methods=['POST'])
def downvote(postid):
    post = Post.query.get(postid)
    post.votes -= 1
    db.session.add(post)
    db.session.commit()
    return jsonify(post.serialize())


@app.route('/api/make-test/', methods=['POST'])
def make_test_data():
    posts = [
        Post(title='Bad Luck Brian', imagepath='brian.jpeg', votes=0),
        Post(title='Leo Putin', imagepath='leo.jpeg', votes=0),
        Post(title='Success Kid', imagepath='success.png', votes=0),
    ]

    for p in posts:
        db.session.add(p)
    db.session.commit()

    return 'ok'

