# coding:utf-8
from ultralytics import YOLOv10
model_yaml_path = "ultralytics/cfg/models/v10/yolov10n.yaml"
data_yaml_path = 'D:\yolov10-main\data\sar.yaml'
pre_model_name = 'D:\yolov10-main\\best.pt'

if __name__ == '__main__':
    model = YOLOv10(model_yaml_path).load(pre_model_name)
    results = model.train(data=data_yaml_path,
                          epochs=10,
                          batch=16,  # 训练批次，默认16,根据你的GPU情况适当调小
                          workers=64,  # 载入数据的线程数
                          resume=True,  # 断点训练，默认False
                          name='train_v10')
