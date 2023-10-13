from SmartWheel import AI

#source = 0 --> webcam otherwise put the path of the file
mytest = AI(yolo_path='../Yolo-Weights/yolov8n.pt',source=0,showing=True,class_range = ["car","person"])
mytest.start_capturing()

mytest.start_capturing()
