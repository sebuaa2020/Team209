# coding:utf-8
from flask import Flask, request, render_template, redirect, url_for
application = Flask(__name__, static_url_path='')


@application.route('/about.html', methods=['POST', 'GET'])
def about():
    return render_template('about.html')


if __name__ == "__main__":
    application.run(host='0.0.0.0', port='1234',debug=True)
