#include "communication.h"

char ssid[]   = "Kamaus";        // Your network SSID
const char* password = "G@t0t000";    // Your network password

void setupWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi!");
  Serial.println(WiFi.localIP());  // Print the local IP address
}

void sendDataToServer(float voltage, float current, float dustDensity, float temperature, float humidity, float lightIntensity) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    const char* serverName = "http://192.168.100.6:9000/upload"; // Replace with your server IP

    // Create a JSON object to send
    String jsonData = "{";
    jsonData += "\"voltage\":" + String(voltage) + ",";
    jsonData += "\"current\":" + String(current) + ",";
    jsonData += "\"dustDensity\":" + String(dustDensity) + ",";
    jsonData += "\"temperature\":" + String(temperature) + ",";
    jsonData += "\"humidity\":" + String(humidity) + ",";
    jsonData += "\"lightIntensity\":" + String(lightIntensity);
    jsonData += "}";

    // Debugging
    Serial.println("Sending data: " + jsonData);

    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");

    // Set timeout
    http.setTimeout(5000); // 5 seconds timeout

    // Send the data to the server using POST
    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("Server Response: ");
      Serial.println(response);
    } else {
      Serial.print("Error sending data: ");
      Serial.println(httpResponseCode);  // Debugging error codes
    }

    http.end();
  } else {
    Serial.println("WiFi not connected!");
  }
}
