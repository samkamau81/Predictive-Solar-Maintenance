import streamlit as st
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import joblib
import time
from datetime import datetime

# Load the pre-trained model
model = joblib.load('solar_predictor.pkl')

# Create a placeholder for real-time data
st.title("Real-Time Sensor Data Monitoring & Anomaly Detection")

# Initialize an empty DataFrame to store incoming data
data_df = pd.DataFrame(columns=['timestamp', 'voltage', 'current', 'dustDensity', 'temperature', 'humidity', 'lightIntensity', 'prediction'])

# Function to simulate incoming sensor data and predict anomaly
def get_sensor_data():
    """Simulate getting sensor data and predicting failure"""
    voltage = np.random.uniform(10, 50)  # Simulated data
    current = np.random.uniform(0, 10)
    dustDensity = np.random.uniform(0, 500)
    temperature = np.random.uniform(15, 40)
    humidity = np.random.uniform(30, 80)
    lightIntensity = np.random.uniform(200, 1000)

    now = datetime.now()
    day = now.day
    month = now.month
    hours = now.hour
    minutes = now.minute

    # Create input for the ML model (7 features)
    power = voltage * current
    sensor_values = np.array([[power, temperature, lightIntensity, day, month, hours, minutes]])

    # Predict potential anomaly
    prediction = model.predict(sensor_values)[0]

    # Capture the timestamp of the data
    timestamp = now.strftime("%Y-%m-%d %H:%M:%S")

    return timestamp, voltage, current, dustDensity, temperature, humidity, lightIntensity, prediction

# Plotting function that updates the same graph
def plot_sensor_data(df):
    """Function to plot sensor data, clearing the plot each time"""
    plt.clf()  # Clear the current figure

    # Plot Voltage, Current, and other sensor data over time
    plt.plot(df['timestamp'], df['voltage'], label='Voltage', color='blue')
    plt.plot(df['timestamp'], df['current'], label='Current', color='green')
    plt.plot(df['timestamp'], df['dustDensity'], label='Dust Density', color='red')
    plt.plot(df['timestamp'], df['temperature'], label='Temperature', color='orange')
    plt.plot(df['timestamp'], df['lightIntensity'], label='Light Intensity', color='purple')

    # Highlight anomalies
    anomalies = df[df['prediction'] == 1]
    if not anomalies.empty:
        plt.scatter(anomalies['timestamp'], anomalies['voltage'], color='red', label='Anomaly', s=100, zorder=5)

    plt.xlabel("Time")
    plt.ylabel("Sensor Values")
    plt.xticks(rotation=45)
    plt.legend()
    plt.tight_layout()

    # Display the plot in Streamlit
    st.pyplot(plt)

# Create containers for real-time updates
with st.container():
    data_container = st.empty()  # For text display of the latest data
    plot_container = st.empty()  # For plotting sensor data

# Main loop to simulate incoming sensor data
while True:
    # Get simulated sensor data and anomaly prediction
    timestamp, voltage, current, dustDensity, temperature, humidity, lightIntensity, prediction = get_sensor_data()
    
    # Append new data to the DataFrame
    new_data = {'timestamp': timestamp, 'voltage': voltage, 'current': current, 'dustDensity': dustDensity,
                'temperature': temperature, 'humidity': humidity, 'lightIntensity': lightIntensity, 'prediction': prediction}
    
    # Use pd.concat instead of append (append is deprecated)
    new_data_df = pd.DataFrame([new_data])
    data_df = pd.concat([data_df, new_data_df], ignore_index=True)
        
    # Convert 'timestamp' to datetime for better plotting
    data_df['timestamp'] = pd.to_datetime(data_df['timestamp'])

    # Display the latest data point and anomaly status
    anomaly_status = "Anomaly Detected!" if prediction == 1 else "Normal"
    anomaly_color = "red" if prediction == 1 else "green"
    
    with data_container:
        st.markdown(f"**Latest Data Point:**\n"
                    f"- Timestamp: {timestamp}\n"
                    f"- Voltage: {voltage:.2f} V\n"
                    f"- Current: {current:.2f} A\n"
                    f"- Dust Density: {dustDensity:.2f} µg/m³\n"
                    f"- Temperature: {temperature:.2f} °C\n"
                    f"- Humidity: {humidity:.2f} %\n"
                    f"- Light Intensity: {lightIntensity:.2f} lux\n"
                    f"- Status: <span style='color:{anomaly_color}'>{anomaly_status}</span>", 
                    unsafe_allow_html=True)

    # Plot the real-time data
    with plot_container:
        plot_sensor_data(data_df)
    
    # Refresh every 2 seconds
    time.sleep(2)
