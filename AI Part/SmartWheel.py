import cv2
import cvzone
from ultralytics import YOLO
import math


class AI:
    classNames = ["person", "bicycle", "car", "motorbike", "aeroplane", "bus", "train", "truck", "boat",
                  "traffic light", "fire hydrant", "stop sign", "parking meter", "bench", "bird", "cat",
                  "dog", "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe", "backpack", "umbrella",
                  "handbag", "tie", "suitcase", "frisbee", "skis", "snowboard", "sports ball", "kite", "baseball bat",
                  "baseball glove", "skateboard", "surfboard", "tennis racket", "bottle", "wine glass", "cup",
                  "fork", "knife", "spoon", "bowl", "banana", "apple", "sandwich", "orange", "broccoli",
                  "carrot", "hot dog", "pizza", "donut", "cake", "chair", "sofa", "pottedplant", "bed",
                  "diningtable", "toilet", "tvmonitor", "laptop", "mouse", "remote", "keyboard", "cell phone",
                  "microwave", "oven", "toaster", "sink", "refrigerator", "book", "clock", "vase", "scissors",
                  "teddy bear", "hair drier", "toothbrush"
                  ]

    def __init__(self, yolo_path = '../Yolo-Weights/yolov8n.pt', source = 0, showing = False,class_range = ["car"]):
        self.model = YOLO(yolo_path)
        self.cap = cv2.VideoCapture(source)
        self.showing = showing
        self.class_range = class_range

    def def_source(self,source = 0):
        self.cap = cv2.VideoCapture(source)

    def start_capturing(self,hold = False):
        while True:
            success, img = self.cap.read()
            results = self.model(img, stream=True)
            for r in results:
                boxes = r.boxes
                for box in boxes:
                    if ( (self.classNames[int(box.cls[0])] in self.class_range) and (box.conf[0] > 0.5)) :
                        x1, y1, x2, y2 = box.xyxy[0]
                        x1, y1, x2, y2 = int(x1), int(y1), int(x2), int(y2)
                        cvzone.cornerRect(img, (x1, y1, x2 - x1, y2 - y1), l=10, t=2)
                        cvzone.putTextRect(img,f'conf = {math.ceil(box.conf[0] * 100)} class = {self.classNames[int(box.cls[0])]} y1 - y0   ={abs((y1 - y2))}',(x1, y1), 0.7, thickness=1, border=1)
                        print(box)

            if(self.showing == True):
                cv2.imshow(" Image ", img)
                if(hold == True):
                    cv2.waitKey(0)  # refresh rate
                else:
                    cv2.waitKey(1)  # refresh rate

    def crop_img(self,x1,x2,y1,y2):
        #To Do
        pass

    def search_car(self):
        car_counter = 0
        success, img = self.cap.read()
        results = self.model(img, stream=True)
        for r in results:
            boxes = r.boxes
            for box in boxes:
                if ((int(box.cls[0]) == 2) and (box.conf[0] > 0.5)):
                    car_counter +=1
        return car_counter
