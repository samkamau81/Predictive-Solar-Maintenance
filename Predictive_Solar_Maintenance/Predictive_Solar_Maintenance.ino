#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_AHT10.h>
#include <Adafruit_INA219.h>
#include "communication.h"

#define LED_PIN 2

Adafruit_AHT10 aht;
BH1750 lightMeter;
Adafruit_INA219 ina219;

//int voltageSensorPin = 33;
//int currentSensorPin = 34;
//int lightSensorPin = A2;

// Wi-Fi credentials
const char* ssid = "Mugi";          // Replace with your WiFi SSID
const char* password = "AquaCoin1";  // Replace with your WiFi password

void setup() {
  Serial.begin(115200);
  while (!Serial) {
      delay(1);
  }
  uint32_t currentFrequency;
  //Initialize Sensors

  Wire.begin(22,21);
  aht.begin();
  lightMeter.begin();
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219.setCalibration_16V_400mA();

  pinMode(LED_PIN, OUTPUT);

  // Initialize WiFi
  setupWiFi(ssid, password);
}

void loop() {
  // Read from INA219
 power_values();
  

  // Read Temperature and Humidity
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");


  // Read Light Intensity
  float lightIntensity = lightMeter.readLightLevel();

  // Print data to Serial
  Serial.print(" %, Temperature: ");
  Serial.print(temp.temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.print(" %, Light Intensity: ");
  Serial.print(lightIntensity);
  Serial.println(" lx");

  // Send data to server
  //sendDataToServer(voltage, current, temperature, humidity, lightIntensity);

  delay(2000);  // Delay between readings
}
void power_values(){
 float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");

}

