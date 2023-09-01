#include "HackPublisher.h"

const char *ssid = "ASUS-F8";
const char *password = "K33pi7$@f3%";

HackPublisher publisher("hackers");  // publisher instance for team "hackers"
int temp = 0;  // variable that holds the temperature

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  while (!Serial) continue;

  // Connect to wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Initialize publisher
  publisher.begin();
}

void loop() {
  // store value for ultrasonic sensor
  publisher.store("temp", temp);        // store value for temp      // store value for meow
  Serial.println(temp);
  publisher.send();                     // send stored data to website

  delay(1000);
  temp++;
}
