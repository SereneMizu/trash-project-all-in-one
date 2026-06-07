import os

for i in range(1, 10):
    x = open(f"D:\yolov10-main\data\labels\\{i}.txt")
    file = x.readline()
    print(f"第{i}张图片"+file, end='')

