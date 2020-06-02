# coding:utf-8
from flask import Flask, request, render_template, redirect, url_for
application = Flask(__name__, static_url_path='')
import sqlite3


@application.route('/about.html', methods=['POST', 'GET'])
def about():
    return render_template('about.html')


@application.route('/static/about.html', methods=['POST', 'GET'])
def reabout():
    return redirect(url_for("about"))


@application.route('/login.html', methods=['POST', 'GET'])
def login():
    if request.method == "POST":
        user = request.form["User"]
        pwd = request.form["Pwd"]
        conn = sqlite3.connect("register.db", check_same_thread=False)
        c = conn.cursor()
        method = "select * FROM customer where user = '" + user + "'"
        c.execute(method)
        namelist = c.fetchall()
        if len(namelist) == 0:
            return render_template('login.html', warning=1)
        real_pwd = namelist[0][1]
        if real_pwd != pwd:
            return render_template('login.html', warning=2)
        print(user)
        print(pwd)
        return redirect(url_for('welcome'))
    return render_template('login.html', warning=0)


@application.route('/static/login.html', methods=['POST', 'GET'])
def relogin():
    return redirect(url_for("login"))


@application.route('/register.html', methods=['POST', 'GET'])
def register():
    if request.method == "POST":
        user = request.form["User"]
        pwd = request.form["Pwd"]
        pwd2 = request.form["Pwd2"]
        if pwd != pwd2:
            return render_template('register.html', warning=1)
        conn = sqlite3.connect("register.db", check_same_thread=False)
        c = conn.cursor()
        method = "select * FROM customer"
        c.execute(method)
        namelist = c.fetchall()
        for i in list(namelist):
            if i[0] == user:
                return render_template('register.html', warning=2)
        method = "INSERT INTO customer(user, pwd, authority) VALUES('" + user + "', '" + pwd + "', '" + "normal" + "')"
        c.execute(method)
        c.connection.commit()
        return redirect(url_for('login'))
    return render_template('register.html', warning=0)


@application.route('/static/register.html', methods=['POST', 'GET'])
def reregister():
    return redirect(url_for("register"))


@application.route('/change_pwd.html', methods=['POST', 'GET'])
def change_pwd():
    if request.method == "POST":
        user = request.form["User"]
        pwd = request.form["Pwd"]
        pwd2 = request.form["Pwd2"]
        conn = sqlite3.connect("register.db", check_same_thread=False)
        c = conn.cursor()
        method = "select * FROM customer where user = '" + user + "'"
        c.execute(method)
        namelist = c.fetchall()
        if len(namelist) == 0:
            return render_template('change_pwd.html', warning=1)
        real_pwd = namelist[0][1]
        if real_pwd != pwd:
            return render_template('change_pwd.html', warning=2)
        method = "update customer set pwd ='" + pwd2 + "' where user='" + user + "'"
        c.execute(method)
        c.connection.commit()
        return redirect(url_for('login'))
    return render_template('change_pwd.html', warning=0)


@application.route('/static/change_pwd.html', methods=['POST', 'GET'])
def rechange_pwd():
    return redirect(url_for("change_pwd"))


@application.route('/delete.html', methods=['POST', 'GET'])
def delete():
    if request.method == "POST":
        user = request.form["User"]
        pwd = request.form["Pwd"]
        conn = sqlite3.connect("register.db", check_same_thread=False)
        c = conn.cursor()
        method = "select * FROM customer where user = '" + user + "'"
        c.execute(method)
        namelist = c.fetchall()
        if len(namelist) == 0:
            return render_template('delete.html', warning=1)
        real_pwd = namelist[0][1]
        if real_pwd != pwd:
            return render_template('delete.html', warning=2)
        method = "delete from customer where user='" + user + "'"
        c.execute(method)
        c.connection.commit()
        return redirect(url_for('login'))
    return render_template('delete.html', warning=0)


@application.route('/static/delete.html', methods=['POST', 'GET'])
def redelete():
    return redirect(url_for("delete"))


@application.route('/start_up.html', methods=['POST', 'GET'])
def start_up():
    return render_template('start_up.html')


@application.route('/static/start_up.html', methods=['POST', 'GET'])
def restart_up():
    return redirect(url_for("start_up"))


@application.route('/welcome.html', methods=['POST', 'GET'])
def welcome():
    return render_template('welcome.html')


@application.route('/static/welcome.html', methods=['POST', 'GET'])
def rewelcome():
    return redirect(url_for("welcome"))


@application.route('/document.html', methods=['POST', 'GET'])
def document():
    return render_template('document.html')


@application.route('/static/document.html', methods=['POST', 'GET'])
def redocument():
    return redirect(url_for("document"))


@application.route('/learn_more.html', methods=['POST', 'GET'])
def learn_more():
    return render_template('learn_more.html')


@application.route('/static/learn_more.html', methods=['POST', 'GET'])
def relearn_more():
    return redirect(url_for("learn_more"))


@application.route('/byhand.html', methods=['POST', 'GET'])
def byhand():
    if request.method == "POST":
        key = dict(request.form)
        direct = list(key.keys())[0]
        print(direct)
        return render_template('byhand.html')
    return render_template('byhand.html')


@application.route('/static/byhand.html', methods=['POST', 'GET'])
def rebyhand():
    return redirect(url_for("byhand"))


if __name__ == "__main__":
    application.run(host='localhost', port='1234', debug=True)
