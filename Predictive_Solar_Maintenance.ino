#include <Wire.h>
#include <BH1750.h>
#include <DHT11.h>
#include "communication.h"

#define DHTPIN 3
#define DHTTYPE DHT22
#define LED_PIN 2

DHT11 dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;

int voltageSensorPin = A0;
int currentSensorPin = A1;
int dustSensorPin = A2;

// Wi-Fi credentials
const char* ssid = "your-SSID";          // Replace with your WiFi SSID
const char* password = "your-PASSWORD";  // Replace with your WiFi password

void setup() {
  Serial.begin(115200);
  dht.begin();
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
  int dustValue = analogRead(dustSensorPin);
  delayMicroseconds(40);  // Delay to avoid spikes
  digitalWrite(LED_PIN, HIGH);  // Turn off the LED
  float dustDensity = (dustValue / 1023.0) * 100.0;  // Example conversion to percentage

  // Read Temperature and Humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read Light Intensity
  float lightIntensity = lightMeter.readLightLevel();

  // Print data to Serial
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print(" V, Current: ");
  Serial.print(current);
  Serial.print(" A, Dust Density: ");
  Serial.print(dustDensity);
  Serial.print(" %, Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Light Intensity: ");
  Serial.print(lightIntensity);
  Serial.println(" lx");

  // Send data to server
  sendDataToServer(voltage, current, dustDensity, temperature, humidity, lightIntensity);

  delay(2000);  // Delay between readings
}
