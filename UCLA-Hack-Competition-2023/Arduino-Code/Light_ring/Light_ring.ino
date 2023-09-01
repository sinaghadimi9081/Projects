#include <Adafruit_NeoPixel.h>

#define LED_PIN  A8
#define LED_COUNT 12
#define BUTTON_PIN A6
Adafruit_NeoPixel ring(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);
int lastState = LOW; // the previous state from the input pin
bool isitOn=false;
void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  ring.begin();                       
  ring.setBrightness(80); 
}
void greenLED();
void redLED();
void blueLED();
void RainbowLED(int delaytime);
void yellowLED();
void whiteLED();
void turnoffLED();
//main loop
void loop() {
  //push button
  int currentState = digitalRead(BUTTON_PIN);
  if(currentState == LOW && lastState==HIGH && isitOn==false){
    whiteLED();
    isitOn=true;
  }
  else if (currentState == LOW && lastState==HIGH && isitOn==true){
    isitOn=false;
    turnoffLED();
  }
  Serial.print("isitOn: ");
  Serial.println(isitOn);
  Serial.print("last State: ");
  Serial.println(lastState);
  Serial.print("CurrentState: ");
  Serial.println(currentState);
  Serial.println("___-___-___");
  lastState=currentState;
  delay(1000);
}
void whiteLED(){
  ring.setPixelColor(0, 255, 255, 255);
  ring.setPixelColor(1, 255, 255, 255);
  ring.setPixelColor(2, 255, 255, 255);
  ring.setPixelColor(3, 255, 255, 255);
  ring.setPixelColor(4, 255, 255, 255);
  ring.setPixelColor(5, 255, 255, 255);
  ring.setPixelColor(6, 255, 255, 255);
  ring.setPixelColor(7, 255, 255, 255);
  ring.setPixelColor(8, 255, 255, 255);
  ring.setPixelColor(9, 255, 255, 255);
  ring.setPixelColor(10, 255, 255, 255);
  ring.setPixelColor(11, 255, 255, 255);
  ring.setPixelColor(12, 255, 255, 255); 
  ring.show();
}
void blueLED(){
  ring.setPixelColor(0, 0, 0, 255);
  ring.setPixelColor(1, 0, 0, 255);
  ring.setPixelColor(2, 0, 0, 255);
  ring.setPixelColor(3, 0, 0, 255);
  ring.setPixelColor(4, 0, 0, 255);
  ring.setPixelColor(5, 0, 0, 255);
  ring.setPixelColor(6, 0, 0, 255);
  ring.setPixelColor(7, 0, 0, 255);
  ring.setPixelColor(8, 0, 0, 255);
  ring.setPixelColor(9, 0, 0, 255);
  ring.setPixelColor(10, 0, 0, 255);
  ring.setPixelColor(11, 0, 0, 255);
  ring.setPixelColor(12, 0, 0, 255); 
  ring.show();
}
void yellowLED(){
  ring.setPixelColor(0, 255, 255, 0);
  ring.setPixelColor(1, 255, 255, 0);
  ring.setPixelColor(2, 255, 255, 0);
  ring.setPixelColor(3, 255, 255, 0);
  ring.setPixelColor(4, 255, 255, 0);
  ring.setPixelColor(5, 255, 255, 0);
  ring.setPixelColor(6, 255, 255, 0);
  ring.setPixelColor(7, 255, 255, 0);
  ring.setPixelColor(8, 255, 255, 0);
  ring.setPixelColor(9, 255, 255, 0);
  ring.setPixelColor(10, 255, 255, 0);
  ring.setPixelColor(11, 255, 255, 0);
  ring.setPixelColor(12, 255, 255, 0); 
  ring.show();
}
void redLED(){
  ring.setPixelColor(0, 0, 255, 0);
  ring.setPixelColor(1, 0, 255, 0);
  ring.setPixelColor(2, 0, 255, 0);
  ring.setPixelColor(3, 0, 255, 0);
  ring.setPixelColor(4, 0, 255, 0);
  ring.setPixelColor(5, 0, 255, 0);
  ring.setPixelColor(6, 0, 255, 0);
  ring.setPixelColor(7, 0, 255, 0);
  ring.setPixelColor(8, 0, 255, 0);
  ring.setPixelColor(9, 0, 255, 0);
  ring.setPixelColor(10, 0, 255, 0);
  ring.setPixelColor(11, 0, 255, 0);
  ring.setPixelColor(12, 0, 255, 0); 
  ring.show();
}
void greenLED(){
  ring.setPixelColor(0, 255, 0, 0);
  ring.setPixelColor(1, 255, 0, 0);
  ring.setPixelColor(2, 255, 0, 0);
  ring.setPixelColor(3, 255, 0, 0);
  ring.setPixelColor(4, 255, 0, 0);
  ring.setPixelColor(5, 255, 0, 0);
  ring.setPixelColor(6, 255, 0, 0);
  ring.setPixelColor(7, 255, 0, 0);
  ring.setPixelColor(8, 255, 0, 0);
  ring.setPixelColor(9, 255, 0, 0);
  ring.setPixelColor(10, 255, 0, 0);
  ring.setPixelColor(11, 255, 0, 0);
  ring.setPixelColor(12, 255, 0, 0); 
  ring.show();
}

void RrainbowLED(int delaytime) {
  for(int i=0; i<ring.numPixels(); i++) { 
    int pixelHue = (i * 65536L / ring.numPixels());
    ring.setPixelColor(i, ring.gamma32(ring.ColorHSV(pixelHue)));
  }
  ring.show();
  delayMicroseconds(delaytime);
  
}
void turnoffLED(){
  ring.clear();
  ring.show();
}