#!/bin/bash

python3 <<INPUT
from app import db, app
with app.app_context():
    db.create_all()
INPUT
