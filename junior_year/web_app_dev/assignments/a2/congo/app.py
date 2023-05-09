from flask import (
    abort, Flask, jsonify, redirect, render_template, request,
    session, url_for
)
import os 

app = Flask(__name__)
app.secret_key = b'laskjdhfakljsdiajsdkfansvioewlkm'


@app.route('/')
def index():
    return redirect(url_for('browse'))

@app.route('/browse/', methods=['GET'])
def browse():
    return render_template('browse.html')

@app.route('/cart/', methods=['GET', 'POST'])
def cart():
    if 'cart' not in session:
        session['cart'] = { }

    if request.method == 'GET':
        print(session['cart'])
        return render_template(
            'cart.html', 
            cart=session['cart']
        )

    elif request.method == 'POST':
        if 'cart' not in session:
            session['cart'] = { }    # make an empty cart

        # Get item and quantity
        item = request.form['item']
        quantity = int(request.form['quantity'])


        if item in session['cart']:
            session['cart'][item] += quantity
        else:
            session['cart'][item] = quantity

        session.modified = True   # We need this so flask updates the session cookie

        return render_template(
            'browse.html', 
            message=f'{item.capitalize()} added.'
        )

#------------------------------------------------------------------------------
@app.route('/cart/delete/', methods=['POST'])
def delete():
    if request.method == 'POST':
        # Get item and quantity
        item = request.form['item']

        del session['cart'][item]

        session.modified = True   # We need this so flask updates the session cookie

        return render_template(
            'cart.html', 
            message=f'{item.capitalize()} removed.',
            cart=session['cart']
        )
#------------------------------------------------------------------------------

@app.route('/checkout/', methods=['GET', 'POST'])
def checkout():

    if 'cart' not in session:
        session['cart'] = { }

    if request.method == 'GET':
        return render_template(
            'checkout.html',
            cart=session['cart']
        )

    elif request.method == 'POST':
        # Request email, credit card, and cart.
        email = request.form['email']
        credit_card = request.form['credit_card']
        cart = session['cart']

        # Format order
        order = f'Email: {email} \nCredit Card: {credit_card} \n'
        
        for item in cart:
            order += f'{item.capitalize()} : {cart[item]} \n'

        order += '\n'

        with open('orders.txt', 'a') as file:
            file.write(order)

        # Empty Cart
        session['cart'] = {}

        return render_template(
            'confirmation.html',
        )


@app.route('/orders/', methods=['GET'])
def orders():
    if (os.path.exists('orders.txt')):
        with open('orders.txt', 'r') as file:
            # make a list of all lines in orders
            orders = file.readlines()

        return render_template(

            'orders.html',
            orders=orders
        )

    else:
        return render_template(
            'orders.html',
        )

