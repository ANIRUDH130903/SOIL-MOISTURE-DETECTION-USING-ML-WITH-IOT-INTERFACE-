import serial  # For reading data from the sensor via serial
from sklearn.linear_model import LogisticRegression
import numpy as np
import time

# Sample dataset (used to train the logistic regression model)
X = np.array([[1004], [1003], [1002], [1001], [990], [980], [970], [960], [950], [940],[935], [930],[925],[920],[915], [910], [920], [819], [830]])
y = np.array([0,0,0,0,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2])  # 0: Dry, 1: Medium, 2: Wet

# Train the logistic regression model
model = LogisticRegression(multi_class='ovr')
model.fit(X, y)

# Function to classify soil moisture based on sensor value
def classify_soil_moisture(sensor_value):
    prediction = model.predict([[sensor_value]])[0]
    if prediction == 0:
        return "Dry"
    elif prediction == 1:
        return "Medium"
    else:
        return "Wet"

# Setup the serial connection (adjust COM port and baud rate as needed)
ser = serial.Serial('COM9', 9600, timeout=1)  # Replace 'COM3' with your port
time.sleep(1)  # Give some time to establish the connection

print("Reading live data from the soil moisture sensor...")

try:
    while True:
        if ser.in_waiting > 0:
            # Read the sensor data as a line
            sensor_data = ser.readline().strip()

            if sensor_data.isdigit():  # Ensure the sensor data is a valid number
                sensor_value = int(sensor_data)
                # Classify the soil moisture
                condition = classify_soil_moisture(sensor_value)
                print(f"Sensor value: {sensor_value} -> Soil condition: {condition}")
                
            time.sleep(1)  # Delay between readings
except KeyboardInterrupt:
    print("Stopping...")
finally:
    ser.close()