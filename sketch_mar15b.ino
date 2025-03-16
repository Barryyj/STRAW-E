#include <WiFi.h>
#include "ESP32Servo.h"

const char* ssid = ">>>";       // Replace with your WiFi network name, like UofT
const char* password = "???";   // Replace with your WiFi password

WiFiServer server(80);

Servo servo1;  // Controls horizontal movement
Servo servo2;  // Controls vertical movement

void performAction(int action) {
    switch (action) {
        case 1:  // Move servo1 right for 1 sec, then left for 1 sec
            servo2.write(95);
            delay(100);
            servo2.write(90);
            delay(1000);
            servo2.write(95);
            delay(2000);
            servo2.write(100);
            delay(1000);
            servo2.write(95);
            break;
        case 2:  // Move servo1 right for 1 sec, then left for 1 sec with wiggling
            servo2.write(95);
            delay(100);
            servo2.write(90);
            delay(1000);
            servo2.write(95);

            // Wiggle servo1 back and forth for 2 seconds
            for (int i = 0; i < 10; i++) {  // Adjust loop count for duration
                servo1.write(60);
                delay(150);
                servo2.write(95);
                delay(150);
                servo1.write(110);
                delay(150);
                servo2.write(95);
                delay(150);
            }

            servo2.write(100);
            delay(1000);
            servo2.write(95);
            break;

        case 3:  // Move both servos to 90 degrees
            servo1.write(92);
            servo2.write(95);
            delay(500);
            break;
        default:
            Serial.println("Invalid action received");
            break;
    }
}

void setup() {
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP()); // Print ESP32's IP address
  server.begin();

  servo1.attach(18);  
  servo2.attach(19);
  
  servo1.write(95);
  servo2.write(95);
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client Connected!");
    String request = client.readStringUntil('\r');
    Serial.println(request);

    if (request.indexOf("POST /set_action") >= 0) {
      while (client.available()) {
        String data = client.readString();
        Serial.println("Received Data: " + data);
        
        int idx = data.indexOf("action");
        if (idx >= 0) {
          int action = data.substring(idx + 8, data.indexOf('}', idx)).toInt();
          Serial.print("Executing action: ");
          Serial.println(action);
          performAction(action);
        }
      }
      
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: application/json");
      client.println();
      client.println("{\"status\": \"success\"}");
    } else {
      client.println("HTTP/1.1 404 Not Found");
      client.println("Content-Type: text/html");
      client.println();
      client.println("404 Not Found");
    }
    delay(100);
    client.stop();
  }
}
