//oled libraries
#include <string.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
//pushbutton
int inputpin=4;
int lastState =LOW;
int currentSensor=0;
bool isitOn=false;
//main setup
void setup() {
  Serial.begin(9600);
  pinMode(inputpin,INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}
void oledDisplayString(int textsize,int x, int y,class String message);
void oledDisplayValue(int textsize,int x, int y,int value );
void loop()
{
  display.fillRect(0,0,128,64,SSD1306_WHITE);//always on top of the loop
  int currentState = digitalRead(inputpin);
  if(currentState == LOW && lastState==HIGH && isitOn==false){
    isitOn=true;
    currentSensor++;
  }
  else if (currentState == LOW && lastState==HIGH && isitOn==true){
    isitOn=false;
    currentSensor++;
  }
  if (currentSensor==1){
    oledDisplayString(2,0,0,"sensor1");
  }
  else if (currentSensor==2){
    oledDisplayString(2,0,0,"sensor2");
  }
  lastState=currentState;
  if (currentSensor>2){
    currentSensor=0;
  }
  Serial.print("isitOn: ");
  Serial.println(isitOn);
  Serial.print("last State: ");
  Serial.println(lastState);
  Serial.print("CurrentState: ");
  Serial.println(currentState);
  Serial.print("current Sensor: ");
  Serial.println(currentSensor);
  Serial.println("___-___-___");
  lastState=currentState;
  display.display();//always at the buttom of loop
  delay(500);

}
//oled display function that will take text size, x and y cordination and the message
void oledDisplayString(int textsize,int x, int y,class String message ){
  display.setTextColor(BLACK);
  display.setTextSize(textsize);
  display.setCursor(x,y);
  display.print(message);
}
void oledDisplayValue(int textsize,int x, int y,int value ){
  display.setTextColor(BLACK);
  display.setTextSize(textsize);
  display.setCursor(x,y);
  display.print(value);
}
