#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>



// communication.h

#ifndef COMMUNICATION_H
#define COMMUNICATION_H


// Function prototypes
void setupWiFi();
void sendDataToServer(float voltage, float current, float dustDensity, float temperature, float humidity, float lightIntensity);

#endif
