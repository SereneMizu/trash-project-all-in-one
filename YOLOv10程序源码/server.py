import os

from flask import Flask, request
from ultralytics import YOLOv10
import json
app = Flask(__name__)


@app.route("/detect", methods=['POST'])
def detect():
    if 'file' not in request.files:
        return '666', 400
    file = request.files['file']
    filename = 'file.jpg'
    file.save(filename)
    model = YOLOv10("./best.pt")
    result = model(filename)
    os.remove('file.jpg')
    x = result[0].tojson()
    s = json.loads(x)

    print(s)
    if len(s):
        if s[0]["name"] == "Other":
            res = "0"
        elif s[0]["name"] == "Recyclable":
            res = "1"
        elif s[0]["name"] == "Hazardous":
            res = "3"
        elif s[0]["name"] == "Food":
            res = "2"
    else:
        res = "-1";
    return res, 200


if __name__ == '__main__':
    app.run(host='0.0.0.0',port=5000)
