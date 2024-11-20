 #include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// Wi-Fi credentials
const char* ssid = " ";
const char* password = "58620267";

// Google Apps Script Web App URL
const char* serverName = "https://script.google.com/macros/s/AKfycbztrrsGnEYjJ3V0-pjrA31lWgU_PAFGxP5CVWihdzuRJzX3XwobBgLGGW0UyBKSGowlBg/exec";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;  // Send data every 5 seconds

// DHT11 settings
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// MQ135 settings
#define MQ135PIN 34

// TEMT6000 settings
#define TEMTPIN 32

void setup() {
  Serial.begin(115200);

  // Initialize the DHT sensor
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    // Read DHT11 data
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Read MQ135 data
    int gasValue = analogRead(MQ135PIN);

    // Read TEMT6000 data
    int lightValue = analogRead(TEMTPIN);

    // Check if DHT readings failed
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Log sensor readings to Serial Monitor
    Serial.println("Sensor Readings:");
    Serial.printf("Temperature: %.2f °C, Humidity: %.2f %%\n", temperature, humidity);
    Serial.printf("Gas: %d, Light: %d\n", gasValue, lightValue);

    // Send data to Google Sheet if connected to Wi-Fi
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;

      // Prepare the URL with sensor data
      String url = String(serverName) +
                   "?temperature=" + String(temperature) +
                   "&humidity=" + String(humidity) +
                   "&gas=" + String(gasValue) +
                   "&light=" + String(lightValue);

      // Send HTTP GET request
      http.begin(url.c_str());
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        Serial.println("Data sent successfully!");
        String response = http.getString();
        Serial.println(response);
      } else {
        Serial.print("Error sending data: ");
        Serial.println(httpResponseCode);
      }

      // End HTTP connection
      http.end();
    } else {
      Serial.println("Wi-Fi not connected");
    }

    // Update the timer
    lastTime = millis();
  }
}
