#include <Wire.h>
#include <BH1750.h>
//#include <Adafruit_AHT10.h>
#include "communication.h"

#define LED_PIN 2

//Adafruit_AHT10 aht;
//BH1750 lightMeter;

int voltageSensorPin = 33;
int currentSensorPin = 34;

void setup() {
  Serial.begin(115200);
  Wire.begin(22,21);
  //aht.begin();
  //lightMeter.begin();
  pinMode(LED_PIN, OUTPUT);

  // Initialize WiFi
  setupWiFi();
}

void loop() {
  
  // Read Voltage
  int voltageValue = analogRead(voltageSensorPin);
  float voltage = (voltageValue / 4095.0) * 5.0 * (21.5 / 5.0);  // Adjust based on voltage divider (ESP32 has 12-bit ADC)

  // Read Current
  int currentValue = analogRead(currentSensorPin);
  float current = (currentValue / 4095.0) * 5.0 * 0.67;  // Adjust based on sensor specs

  // Read Temperature and Humidity
  float temperature = 20.1;
  float humidity = 22.0;

  // Read Light Intensity
  float lightIntensity = 34;//lightMeter.readLightLevel()

  // Simulated Dust Density (you'll need to replace this with actual sensor logic)
  float dustDensity = 10;  //analogRead(A0) Simulate reading dust density

  // Print data to Serial
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print(" V, Current: ");
  Serial.print(current);
  Serial.print(" A, Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Light Intensity: ");
  Serial.print(lightIntensity);
  Serial.print(" lx, Dust Density: ");
  Serial.println(dustDensity);

  // Send data to server
  sendDataToServer(voltage, current, dustDensity, temperature, humidity, lightIntensity);

  delay(2000);  // Delay between readings
}
