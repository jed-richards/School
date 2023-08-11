
from app import db                                                        

class Post(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    title = db.Column(db.String())
    imagepath = db.Column(db.String())
    votes = db.Column(db.Integer)

    def serialize(self):
        return {
            'id': self.id,
            'title': self.title,
            'imagepath': self.imagepath,
            'votes': self.votes,
        }

    def __repr__(self):
        return 'Post'+str(serialize(self))

