from ultralytics import YOLOv10
import json

model = YOLOv10("best.pt")

results = model.predict("D:\yolov10-main\\20241016-180808.jpg")

x = results[0].tojson()
s = json.loads(x)
print(s)
print(s[0]["name"])

