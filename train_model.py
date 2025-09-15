# It is highly recommended to run this script in a virtual environment.
# pip install ultralytics

from ultralytics import YOLO
import os



if __name__ == "__main__":

    dataset_yaml_path = '/home/varunkumar/yolo_rpi/dataset/data.yaml'
    model_name = 'yolo11n.pt'
    epochs = 20
    image_size = 640
    batch_size = 1  # Use -1 for auto batch size based on GPU memory
    device_to_use = 'cpu' # The device to use for training. '0' for the first GPU, '1' for the second, etc. 'cpu' for CPU.

    # Start the training process
    print(f"Model {model_name} loaded successfully.")
    print("Starting training with the following parameters:")
    print(f"  Dataset config: {dataset_yaml_path}")
    print(f"  Epochs: {epochs}")
    print(f"  Image size: {image_size}")
    print(f"  Batch size: {batch_size}")


    # Load the YOLOv11 model
    model = YOLO(model_name)

    # Train the model
    try:
        results = model.train(
            data=dataset_yaml_path,
            epochs=epochs,
            imgsz=image_size,
            batch=batch_size,
        )
        print("Training completed successfully!")
        
        # Evaluate the model on the validation set
        print("Running final validation...")
        metrics = model.val()
        print("Validation metrics:")
        print(metrics)

        # Export the model to NCNN format
        model.export(format="ncnn")  # creates 'yolo11n_ncnn_model'

        # Run inference
        # ncnn_model = YOLO("yolo11n_ncnn_model")
        # results = ncnn_model("https://ultralytics.com/images/bus.jpg")



    except Exception as e:
        print(f"An error occurred during training: {e}")
