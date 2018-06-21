from flask import Flask
from flask import request
import json
app = Flask(__name__)

@app.route("/", methods=["POST"])
def hello():
    print(request.get_json())
    return "", 200

app.run(host='0.0.0.0', port="80")