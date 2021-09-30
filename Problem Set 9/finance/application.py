import os
from typing import Counter
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    idUser = session["user_id"]

    rows = db.execute("select symbol, name, sum(shares) as shares, price, sum(shares*price) as total from stockUsers where id_user = ? and shares > ? and stockUsers.type = ?  GROUP by symbol, name", idUser, 0, "BUY")

    cashRow = db.execute("SELECT cash FROM users WHERE id = ?", idUser)
    if not cashRow:
        return apology("Error Database User")

    cash = cashRow[0]["cash"]
    # sum of user cash and stocks shares total price
    cashFooter = 0 
    for data in rows:
      cashFooter += data["total"]
    cashFooter += cash
    
    return render_template("index.html", register = rows, cash = cash, cashFooter = cashFooter)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    #opening the page to buy shares
    if request.method == "GET":
        return render_template("buy.html")

    #buying shares, method POST     
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        responseAPI = lookup(symbol)

        if not symbol or not shares:
            return apology("symbol and shares are required", 400)
        
        if not shares.isnumeric() or int(shares) < 0:
            return apology("shares should be a positive number", 400)

        if not responseAPI:
            return apology("Symbol does not exist", 400)

        price = responseAPI["price"]
        name = responseAPI["name"]
        symbol = responseAPI["symbol"]

        if int(shares) < 1 :
            return apology("You can't buy negative shares")

        #checking if the user has enough money
        idUser = session["user_id"]
        rows = db.execute("SELECT cash FROM users WHERE users.id = ?", idUser)
        cash =  rows[0]["cash"]
        total = int(shares) * price 

        if total > cash:
            return apology("you don't have enough money")

        #saving the transaction in database
        date = str(datetime.now())
        rows = db.execute("INSERT INTO stockUsers(symbol, name, shares,history_shares, price, total, type, data, id_user) VALUES(?, ?, ?, ?, ?, ?, ? , ?, ? )",symbol, name, shares, shares, price, total, "BUY", date, idUser )

        #updating cash of user
        remainingMoney = cash - total

        rows = db.execute("UPDATE users SET cash = ? WHERE users.id = ?",remainingMoney, idUser )

        if not rows:
            return apology("DATABASE ERROR",400)
           
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    dataStocks = db.execute("SELECT symbol, history_shares AS shares, price, data FROM stockUsers WHERE id_user = ? ORDER BY data DESC",session["user_id"] )

    return render_template("hystory.html", stocks=dataStocks)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")


    if request.method == "POST":
        symbol = request.form.get("symbol")
        responseAPI = lookup(symbol)
        if not responseAPI:
            return apology("Symbol does not exist")

    name = responseAPI["name"]
    price = usd(float(responseAPI["price"]))
    symbol = responseAPI["symbol"]
    
    return render_template("quote.html", symbol = symbol, price = price, name = name  )


@app.route("/register", methods=["GET", "POST"])
def register():

    if request.method == "POST":
         # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not request.form.get("confirmation"):
            return apology("must Confirm the password", 400)

        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("The password must be the same", 400)

        name = request.form.get("username")
        password = request.form.get("password")
        #hash the password to insert in users
        passwordHash = generate_password_hash(password)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", name)

        # Ensure username exists and password is correct
        if len(rows) >= 1:
            return apology("The user alredy exist", 400)
        
         # Inserting users into table users
        rows = db.execute("INSERT INTO users(username, hash, cash) VALUES(?, ?, ?)", name, passwordHash, 10000)

        return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])


@login_required
def sell():
    """Sell shares of stock"""
    idUser = session["user_id"]
    if request.method == "GET":
        
        #selecting all symbol name from stocks that had been buy
        rows =  db.execute("SELECT DISTINCT stockUsers.symbol FROM stockUsers WHERE stockUsers.id_user = ?  and type = ? and shares > ?", idUser, "BUY", 0 )

        return render_template("sell.html", stocks = rows)

    else:
        symbol = request.form.get("symbol")
        sharesToSell = request.form.get("shares")
        
        if not symbol or not sharesToSell:
            return apology("symbol and number of shares are required",400)
        
        if not sharesToSell.isnumeric() or int(sharesToSell) < 0:
            return apology("shares should be a positive number", 400)


        # Need to return the number of shares of a stock symbol
        data = db.execute("SELECT  SUM (stockUsers.shares) AS totalShares FROM stockUsers WHERE stockUsers.id_user = ? and symbol = ? AND type = ? and shares > ?",idUser, symbol, "BUY",0 )

        #total shares of a given symbol
        totalShares = data[0]["totalShares"]

        if int(sharesToSell) > int(totalShares):
            return apology("can't sell so many shares", 400)

        responseAPI = lookup(symbol)
        price = responseAPI["price"]
        name = responseAPI["name"]

        rows = db.execute("select stockUsers.id_stockes, symbol, name, shares from stockUsers where stockUsers.id_user = ? and symbol = ? AND shares > ?", idUser, symbol, 0)

        #casting to integer the values
        sharesInTable = 0
        sharesToSell = int(sharesToSell)
        totalSharesSold = sharesToSell

        saleMoney = 0
        
        #every sale of a share will decrease the purchase transaction
        # also we calculate the value of sale updating the cash of the user

        for data in rows:
            totalSaleMoney = 0
            sharesInTable = int(data["shares"])

            if sharesInTable < sharesToSell:

                saleMoney = price * sharesInTable   
                totalSaleMoney += saleMoney     
                sharesToSell = sharesToSell - sharesInTable
                sharesInTable = 0
                data["shares"] = sharesInTable

                #update the table stockUsers setting the shares to 0 when selling it
                db.execute("UPDATE stockUsers SET shares = ? WHERE stockUsers.id_stockes = ?",data["shares"], data["id_stockes"] )

                #updating the user cash
                db.execute("UPDATE users SET cash = cash + ? WHERE users.id = ?", saleMoney, idUser)
                #return apology("not run cash", 123)

                #if sold every share 
                if sharesToSell == 0:
                    break
            # one transaction of buy has all shares needed to sell     
            elif sharesInTable >= sharesToSell:
                sharesInTable = sharesInTable - sharesToSell
                data["shares"] = sharesInTable

                db.execute("UPDATE stockUsers SET shares = ? WHERE stockUsers.id_stockes = ?",data["shares"], data["id_stockes"]  )

                saleMoney = price * sharesToSell
                totalSaleMoney += saleMoney 

                 #updating the user cash
                db.execute("UPDATE users SET cash = cash + ? WHERE users.id = ?", saleMoney, idUser)
                break;

        date = str(datetime.now())

        db.execute("INSERT INTO stockUsers(symbol, name, shares, history_shares, price, total, type, data, id_user) VALUES(?, ?, ?, ?, ?, ?, ? , ?, ? )", symbol, name, -totalSharesSold,-totalSharesSold,  price, totalSaleMoney, "SELL", date, idUser )    

        return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

