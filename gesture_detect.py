import cv2
from ultralytics import YOLO
from picamera2 import Picamera2, Preview
import socket 

import time

if __name__ == "__main__":


    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect(('127.0.0.1', 8080)) 


    # model = YOLO("best.pt")
    #  model.export(format="ncnn")  # creates 'yolo11n_ncnn_model'

    # Load the converted ncnn model
    ncnn_model = YOLO("best_ncnn_model", task = "detect")


    # Initialize the Picamera2

    screen_res_w = 640
    screen_res_h = 480

    picam2 = Picamera2()
    picam2.configure(picam2.create_video_configuration(main={"format": 'RGB888', "size": (screen_res_w, screen_res_h)}))
    picam2.start_preview(Preview.QT)
    picam2.start()

    # imgsze = 240

    bbox_colors = (164,120,87)

    while True:

        t_start = time.perf_counter()

        frame = picam2.capture_array()
        if (frame is None):
            print('Unable to read frames from the Picamera. This indicates the camera is disconnected or not working. Exiting program.')
            break

        # Perform inference on the frame using the ncnn model
        results = ncnn_model(frame, True)
        print("Results:", results)

        # Draw bounding boxes and labels on the frame
        for result in results:
            boxes = result.boxes
            for box in boxes:
                x1, y1, x2, y2 = map(int, box.xyxy[0])
                confidence = box.conf[0]

                # 0 - Nothing, 1 - Paper, 2 - Rock, 3 - Scissors
                class_id = int(box.cls[0])
                label = f"{ncnn_model.names[class_id]} {confidence*100:.2f}"

                # Draw bounding box
                cv2.rectangle(frame, (x1, y1), (x2, y2), bbox_colors, 2)

                # Draw label background
                (label_width, label_height), baseline = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.5, 1)
                cv2.rectangle(frame, (x1, y1 - label_height - baseline), (x1 + label_width, y1), bbox_colors, -1)
                cv2.putText(frame, label, (x1, y1 - baseline), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 1)

                if class_id == 1:
                    s.send(class_id )

        # cv2.imshow('YOLO detection results',frame) # Display image

        t_end = time.perf_counter()
        fps = 1 / (t_end - t_start)
        print(f"FPS: {fps:.2f}")

        print("Running...")

    # Release resources and close windows
    picam2.stop_preview()
    picam2.stop()
    cv2.destroyAllWindows()
