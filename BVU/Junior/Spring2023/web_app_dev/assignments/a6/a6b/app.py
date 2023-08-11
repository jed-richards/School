from flask import (
    abort, Flask, jsonify, redirect, render_template, request,
    session, url_for
)
from flask_sqlalchemy import SQLAlchemy
import os 
from pathlib import Path
from werkzeug.utils import secure_filename

IMAGE_DIR = 'static/img/profilephotos'
POST_DIR = 'static/img/posts'

app = Flask(__name__)
app.secret_key = b'REPLACE_ME_x#pi*CO0@^z_beep_beep_boop_boop'

sqlite_uri = 'sqlite:///' + os.path.abspath(os.path.curdir) + '/test.db'
app.config['SQLALCHEMY_DATABASE_URI'] = sqlite_uri
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)

from models import Post, Profile, Like


# Get active profile
def get_user():
    if 'user' in session:
        return session['user']
    return None


# We made this for easy access of posts based on a profile id
def get_posts_by_id(profile_id):
    posts = Post.query.filter_by(profile_id=profile_id).all()
    posts = list(map(lambda p: p.serialize(), posts))
    return posts


# Query database for a profile with username and password
# If there is, save the serialized user (table) in the session
def authenticate_login(username, password):
    user = Profile.query.filter_by(username=username, password=password).first()
    if user:
        session['user'] = user.serialize()
        return True
    return False


# Query database to see if username exists
def username_taken(username):
    return Profile.query.filter_by(username=username).first()


# the stuff that is NOT secure
#FIXME: POST /profile/ is not secure but GET /profile/ is secure
#       maybe need to look at request.methods too
#def is_secure_route(request):
#    return request.path not in [
#            '/login/',
#            '/logout/',
#            '/profile/new/',
#            '/profile/',
#        ] and \
#        not request.path.startswith('/static/')

def is_secure_route(request):
    if (
        (request.path.startswith('/api/posts/')) or 
        (request.path == '/profile/' and request.method == "GET") or
        (request.path in ['/main/']) 
        #(request.path.startswith('/static/'))
    ):
        return True
    else:
        return False


# This initializes our app.
@app.before_first_request
def app_init():
    imgdir = Path(IMAGE_DIR)
    if not imgdir.exists():
        imgdir.mkdir(parents=True)
    try:
        Profile.query.all()
    except:
        db.create_all()


# Before each request, if trying to access a secure route, redirect to login_form
@app.before_request
def login_redirect():
    if get_user() == None and is_secure_route(request):
        return redirect(url_for('login_form'))


# redirect to main
@app.route('/', methods=['GET'])
def index():
    return redirect(url_for('main'))


# render main and pass user to the page
@app.route('/main/', methods=['GET'])
def main():
    return render_template('main.html', user=get_user())


# redirect to login_form
@app.route('/login/', methods=['GET'])
def login_form(messages=[]):
    return render_template('login_form.html', messages=messages)


# get login_form data and try to login
@app.route('/login/', methods=['POST'])
def login():
    if authenticate_login(request.form['username'], request.form['password']):
        return redirect(url_for('main'))
    else:
        return render_template('login_form.html', \
                messages=['Invalid username/password combination'])


# if there is an active user, remove them from session and render login_form
@app.route('/logout/')
def logout():
    if 'user' in session:
        del session['user']
        return render_template('login_form.html', \
            messages=['Logged out. Thanks for visiting this site.'])
    return redirect(url_for('login'))


# render create profile form
@app.route('/profile/new/', methods=['GET'])
def create_profile_form():
    return render_template('create_profile_form.html')


# get create_profile_form data and try to create a profile
@app.route('/profile/', methods=['POST'])
def create_profile():
    username = request.form['username']
    password = request.form['password']
    email = request.form['email']
    infile = request.files['image']

    if not infile:
        return render_template('create_profile_form.html', messages=['Invalid Image'])
        
    filename = secure_filename(infile.filename)

    if filename == "":
        return render_template('create_profile_form.html', messages=['Invalid Image'])

    filename = username + "_" + filename
    filepath = os.path.join(IMAGE_DIR, filename)

    if username_taken(username):
        return render_template('create_profile_form.html', messages=['Username Already Taken'])

    if username == "":
        return render_template('create_profile_form.html', messages=['Invalid Username'])

    if password == "":
        return render_template('create_profile_form.html', messages=['Invalid Password'])

    if email == "":
        return render_template('create_profile_form.html', messages=['Invalid Email'])
    
    if infile:
        infile.save(filepath)
        user = Profile(
            username=username,
            password=password,
            email=email,
            photofn=filepath,
            posts=[],
        )
        db.session.add(user)
        db.session.commit()
        return redirect(url_for('login'))
    else:
        return abort(400)


#display profile page based on id
@app.route('/profile/<int:profile_id>/', methods=['GET'])
def get_profile_by_id(profile_id):
    user = Profile.query.get(profile_id)

    if user:
        user = user.serialize()
        posts = get_posts_by_id(profile_id)
        return render_template('profile.html', user=user, posts=posts, active_user=get_user())

    #else that user doesn't exist, so send back to active user's page
    return redirect(url_for('get_profile'))


#display currently logged in profile page
@app.route('/profile/', methods=['GET'])
def get_profile():
    user = get_user()
    posts = get_posts_by_id(user['id'])
    return render_template('profile.html', user=user, posts=posts, active_user=user)


#retrieves a JSON array of PROFILE_ID's posts,
#if PROFILE_ID is invalid this should return []
@app.route('/api/posts/', methods=['GET'])
def get_posts():
    if "profile_id" in request.args:
        profile_id = request.args.get('profile_id')
        user = Profile.query.get(profile_id)
        if user:
            user = user.serialize()
        else:
            return []
    else:
        user = get_user()

    posts = get_posts_by_id(user['id'])
    return jsonify(posts)


#retrieves a JSON Post object and creates post
@app.route('/api/posts/', methods=['POST'])
def create_post():
    user = get_user()
    content = request.form['content']

    if content != "":
        newpost = Post(
            content=content,
            profile_id=user['id'],
            likes=[],
        )
        db.session.add(newpost)
        db.session.commit()
        newpost = newpost.serialize()
        return jsonify(newpost)
    else:
        return abort(400, description="Invaild post.")


#retrieves a JSON object representing a post
@app.route('/api/posts/<int:post_id>/', methods=['GET'])
def get_post_by_post_id(post_id):
    post = Post.query.get(post_id)
    if post:
        return jsonify(post.serialize())
    else:
        return abort(400, description=f"A post with post_id: {post_id}, does not exist.")


#if active user has not liked post then create a like object and add it to database
@app.route('/api/posts/<int:post_id>/like/', methods=['POST'])
def like_post(post_id):
    user = get_user()
    post = Post.query.get(post_id)
    if user['id'] not in post.liked_by():
        like = Like(profile_id=user['id'], post_id=post_id)
        db.session.add(like)
        db.session.commit()

    return jsonify(post.serialize())


#if active user has liked post before then delete that like from the database
@app.route('/api/posts/<int:post_id>/unlike/', methods=['POST'])
def unlike_post(post_id):
    user = get_user()
    post = Post.query.get(post_id)
    if user['id'] in post.liked_by():
       like = Like.query.filter_by(profile_id=user['id'], post_id=post_id).first()
       db.session.delete(like)
       db.session.commit()

    return jsonify(post.serialize())


#retreieves a JSON array of the Profiles who have liked the specified post_id
@app.route('/api/posts/<int:post_id>/likes/', methods=['GET'])
def get_likes_of_post(post_id):
    post = Post.query.get(post_id)
    profile_ids = post.liked_by()
    profiles = list(
        map(lambda p_id: Profile.query.get(p_id).serialize(), profile_ids)
    )
    return jsonify(profiles)
