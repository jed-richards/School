# Set up the DB using the following commands:
# $ python
# > from app import db
# > db.create_all()
# > from models import User
# > admin = User(username='admin', email='admin@example.com')
# > db.session.add(admin)
# > db.session.commit()
# > User.query.all()

from app import db                                                        

# Example class
class User(db.Model):
    # Here we have to use db.Column to make a column
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    email = db.Column(db.String(120), unique=False, nullable=False)

    def __repr__(self):
        return '<User %r>' % self.username

# Creates a user with params being request.form
def add_user(params):
    newuser = User(username=params['username'], email=params['email'])
    db.session.add(newuser)
    db.session.commit()
    return newuser

def get_user(the_id):
    return User.query.get(the_id)

def get_users():
    return User.query.all()

def del_user(the_id):
    user = User.query.get(the_id)
    username = user.username
    db.session.delete(user)
    db.session.commit()
    return username

