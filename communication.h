// communication.h

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <WiFi.h>
#include <HTTPClient.h>

// Function prototypes
void setupWiFi(const char* ssid, const char* password);
void sendDataToServer(float voltage, float current, float dustDensity, float temperature, float humidity, float lightIntensity);

#endif
