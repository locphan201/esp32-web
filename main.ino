#include <Arduino.h>
#include <WiFi.h>
#include "MotorControl.h"
#include "WebHandler.h"

// Wi-Fi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASS";

void setup() {
    Serial.begin(115200);
    
    // Connect to Wi-Fi
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    // Wait until connected
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Initialize motors
    initMotors();

    // Initialize web server
    initWebServer();
}

void loop() {
    // Handle any incoming clients
    server.handleClient();
}
