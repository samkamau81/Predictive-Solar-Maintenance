// communication.cpp

#include "communication.h"

// Function to set up Wi-Fi
void setupWiFi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi!");
}

// Function to send data to the server
void sendDataToServer(float voltage, float current, float dustDensity, float temperature, float humidity, float lightIntensity) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String serverUrl = "http://your-server-url/api/data"; // Replace with your server URL

    // Create a JSON object to send
    String jsonData = "{";
    jsonData += "\"voltage\":" + String(voltage) + ",";
    jsonData += "\"current\":" + String(current) + ",";
    jsonData += "\"dustDensity\":" + String(dustDensity) + ",";
    jsonData += "\"temperature\":" + String(temperature) + ",";
    jsonData += "\"humidity\":" + String(humidity) + ",";
    jsonData += "\"lightIntensity\":" + String(lightIntensity);
    jsonData += "}";

    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Send the data to the server using POST
    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("Server Response: ");
      Serial.println(response);
    } else {
      Serial.print("Error sending data: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi not connected!");
  }
}
