from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir
from datetime import datetime

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    
    if request.method == "GET":
        # query database for users data
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session['user_id'])
            
        # query databese for users portfolio
        stocks = db.execute("SELECT symbol, SUM(shares) AS shares FROM portfolio WHERE user = :user_id GROUP BY symbol ORDER BY symbol", user_id=session['user_id'])
        
        total = 0
        
        for row in stocks:
            # creates a dict for each symbols we have in portfolio
            quotes = lookup(row['symbol'])
            
            # append a variables to stocks
            row['name'] = quotes['name']
            row['price'] = usd(quotes['price'])
            row['value'] = usd(row['shares'] * quotes['price'])
            total += row['shares'] * quotes['price']
        
        # redirect user to home page
        return render_template("index.html", stock=stocks, cash=usd(cash[0]['cash']), total=usd(total + cash[0]['cash']))
    
    else:
        # redirect user to home page
        return render_template("index")

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide a stock symbol")
        
        # create a dict for the symbol we are looking for
        quotes = lookup(request.form.get("symbol"))
        if quotes == None:
            return apology("invalid stock symbol")
        # get number of shares to buy
        shares = int(request.form.get("shares"))
        if not shares:
            return apology("indicate amount of shares")
        
        if shares < 0:
            return apology("Number of shares mut be positive")
            
        # add stock to user's portfolio
        cash = db.execute("SELECT cash FROM users WHERE id = :user", user=session['user_id'])
        if cash[0]['cash'] > shares*quotes['price']:
            result=db.execute("INSERT INTO portfolio (user, symbol, shares, price, date) VALUES(:user, :symbol, :share, :price, :date)", user=session['user_id'], symbol=quotes['symbol'], share=shares, price=(shares*quotes['price']), date=datetime.now().isoformat())
            if not result:
                return apology("503 error")
            db.execute("UPDATE users SET cash = cash - :price WHERE id = :user", price=shares*quotes['price'], user=session['user_id'])

        else:
            return apology("You run out of cash")
        
        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    
    if request.method == "GET":
        # query database for users data
        history = db.execute("SELECT * FROM portfolio WHERE user = :user_id", user_id=session['user_id'])
        
        for row in history:
            row['price']=usd(row['price']/row['shares'])
        
        # redirect user to home page
        return render_template("history.html", stocks=history)
    
    else:
        # redirect user to home page
        return render_template("history")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return render_template("index.html")

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("stock"):
            return apology("must provide a stock name")
        
        # create a dict for the symbol we are looking for
        quotes = lookup(request.form.get("stock"))
        if quotes == None:
            return apology("invalid stock name")
        
        # redirect user to home page
        return render_template("stock.html", name=quotes['name'], price=quotes['price'], symbol=quotes['symbol'])

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # ensure password confirmation was submitted
        elif not request.form.get("confirmation") == request.form.get("password"):
            return apology("password confirmation", "failed")

        # insert into database a username and hashed password
        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hashed)", username=request.form.get("username"), hashed=pwd_context.encrypt(request.form.get("password")))
        if not result:
            return apology("Invalid username", "Try other username")

        # query database for username's id
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # logged in automatically
        session["user_id"] = rows[0]["id"]
        
        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide a stock symbol")
        
        # create a dict for the symbol we are looking for
        quotes = lookup(request.form.get("symbol"))
        if quotes == None:
            return apology("invalid stock symbol")
        # get number of shares to buy
        shares = int(request.form.get("shares"))
        if shares < 0:
            return apology("Number of shares mut be positive")
            
        # add stock to user's portfolio
        cash = db.execute("SELECT cash FROM users WHERE id = :user", user=session['user_id'])
        
        share=db.execute("SELECT SUM(shares) AS shares FROM portfolio WHERE user = :id AND symbol = :symbol", id=session['user_id'], symbol=quotes['symbol'])

        if share[0]['shares'] < shares:
            return apology("too much shares")

        result=db.execute("INSERT INTO portfolio (user, symbol, shares, price, date) VALUES(:user, :symbol, :share, :price, :date)", user=session['user_id'], symbol=quotes['symbol'], share=shares*-1, price=(shares*quotes['price']*-1), date=datetime.now().isoformat())
        if not result:
            return apology("503 error")
        db.execute("UPDATE users SET cash = cash + :price WHERE id = :user", price=shares*quotes['price'], user=session['user_id'])
        
        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("sell.html")
