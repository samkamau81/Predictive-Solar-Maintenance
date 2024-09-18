#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_AHT10.h>
#include "communication.h"

#define LED_PIN 2

Adafruit_AHT10 aht;
BH1750 lightMeter;

int voltageSensorPin = 33;
int currentSensorPin = 34;
//int lightSensorPin = A2;

// Wi-Fi credentials
const char* ssid = "Sams9plus";          // Replace with your WiFi SSID
const char* password = "Samuel1234";  // Replace with your WiFi password

void setup() {
  Serial.begin(115200);
  Wire.begin(22,21);
  aht.begin();
  lightMeter.begin();
  pinMode(LED_PIN, OUTPUT);

  // Initialize WiFi
  setupWiFi(ssid, password);
}

void loop() {
  // Read Voltage
  int voltageValue = analogRead(voltageSensorPin);
  float voltage = (voltageValue / 1023.0) * 5.0 * (21.5 / 5.0);  // Adjust based on voltage divider

  // Read Current
  int currentValue = analogRead(currentSensorPin);
  float current = (currentValue / 1023.0) * 5.0 * 0.67;  // Adjust based on sensor specs

  // Read Dust Density
  digitalWrite(LED_PIN, LOW);  // Turn on the LED
  delayMicroseconds(280);  // Wait for sensor stabilization
  rPin);
  delayMicroseconds(40);  // Delay to avoid spikes
  digitalWrite(LED_PIN, HIGH);  // Turn off the LED
  

  // Read Temperature and Humidity
  float temperature = aht.readTemperature();
  float humidity = aht.readHumidity();

  // Read Light Intensity
  float lightIntensity = lightMeter.readLightLevel();

  // Print data to Serial
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print(" V, Current: ");
  Serial.print(current);
   Serial.print(" %, Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Light Intensity: ");
  Serial.print(lightIntensity);
  Serial.println(" lx");

  // Send data to server
  sendDataToServer(voltage, current, temperature, humidity, lightIntensity);

  delay(2000);  // Delay between readings
}
