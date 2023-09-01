// ledpins and creating neopixel object "ring"
#include <Adafruit_NeoPixel.h>
#define LED_PIN  A8
#define LED_COUNT 12
Adafruit_NeoPixel ring(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);
//oled libraries
#include <string.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//wifi
#include "HackPublisher.h"
const char *ssid = "ASUS-F8";
const char *password = "K33pi7$@f3%";
HackPublisher publisher("ClawPatrol");  
//ultrasonic Pins
const int pingPin = 32; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 14; // Echo Pin of Ultrasonic Sensor
class Ultrasonic_me{
  private:
  int p_echo;
  int p_trig;
  public:
  Ultrasonic_me(int echo, int trig):p_echo(echo),p_trig(trig){}
  int get_echo(){
    return p_echo;
  }
  int get_trig(){
    return p_trig;
  }
  void setup(){
    pinMode(get_trig(),OUTPUT);
    pinMode(get_echo(),INPUT);
  }
  long microsecondsToInches(long microseconds) {
    return microseconds / 74 / 2;
  }

  long microsecondsToCentimeters(long microseconds) {
    return microseconds / 29 / 2;
  } 
  void ultrasonic(long &duration, long & cm, long & inch){
    digitalWrite(get_trig(), LOW);
    delayMicroseconds(2);
    digitalWrite(get_trig(), HIGH);
    delayMicroseconds(10);
    digitalWrite(get_trig(), LOW);
    duration = pulseIn(get_echo(), HIGH);
    inch = microsecondsToInches(duration);
    cm = microsecondsToCentimeters(duration);
  }
};
//pushbutton
int inputpin=4;
int lastState =LOW;
int currentSensor=1;
bool isitOn=false;
//gas sensor
const int gaspin = A9;//any pin
int gasRead = 0;
//temp sensor
#include <AM232X.h>//temp sensor
AM232X AM2320;
int temp=0;
int hum=0;
//objects
Ultrasonic_me ultrasonic1(echoPin,pingPin);//making ultrasonic object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)


//main setup
void setup() {
  Serial.begin(115200);
  //wifi setup
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  publisher.begin();
  //display setup
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //pushbutton setup
  pinMode(inputpin,INPUT_PULLUP);
  //led ring setup
  ring.begin();                       
  ring.setBrightness(80); 
  //ultrasonic setup
  ultrasonic1.setup();
  //temp-humidity setup
  void humidity_temp_setup();
  //buzzer setup
  //pinMode(buzzpin,OUTPUT);
}
//variables and functions
void greenLED();
void redLED();
void blueLED();
void RainbowLED(int delaytime);
void yellowLED();
void whiteLED();
void turnoffLED();
void oledDisplayString(int textsize,int x, int y,class String message);
void oledDisplayValue(int textsize,int x, int y,int value );
void gassensor(int gaspin,int & gasRead);
void check_temp_humidity();
void humidity(int & humidity);
void temprature(int & temp);
void humidity_temp_setup();
long duration=0, inch=0, cm=0;//ultrasonic readings

//main loop
void loop() {
  display.fillRect(0,0,128,64,SSD1306_WHITE);//always on top of the loop
  ultrasonic1.ultrasonic(duration, cm, inch);
  gassensor(gaspin,gasRead);
  check_temp_humidity();
  temprature(temp);
  humidity(hum);
  //web storing
  publisher.store("temp", temp);
  publisher.store("hum", hum);
  publisher.store("gasRead", gasRead);
  publisher.store("cm", cm);
  int currentState = digitalRead(inputpin);
  if(currentState == LOW && lastState==HIGH && isitOn==false){
    currentSensor++;
    isitOn=true;
  }
  else if (currentState == LOW && lastState==HIGH && isitOn==true){
    isitOn=false;
    currentSensor++;
  }
  if (currentSensor==1){
    if(cm<25){
      turnoffLED();
      RainbowLED(1);
      oledDisplayValue(2,20,45,cm);
      oledDisplayString(2,20,20,"Too Close");
    }
    else if(cm>=25 && cm<=100){
      turnoffLED();
      oledDisplayValue(2,20,45,cm);
      oledDisplayString(2,3,20,"HI BRUIN");
      redLED();
    }
    else if(cm>100){
      turnoffLED();
      oledDisplayValue(2,20,45,cm);
      oledDisplayString(2,20,20,"No Object");
      blueLED();
    }
    oledDisplayString(2,20,1,"RESCUE");
  }
  else if (currentSensor==2){
    turnoffLED();
      if(gasRead>2300){
        oledDisplayString(2,20,20,"TOXIC");
        oledDisplayValue(2,20,45,gasRead);
        redLED();
      }
      else if (gasRead<=2300 && gasRead>=500){
        oledDisplayString(2,20,20,"MODERATE");
        oledDisplayValue(2,20,45,gasRead);
        yellowLED();
      }
      else{
        oledDisplayString(2,20,20,"safe");
        oledDisplayValue(2,20,45,gasRead);
        greenLED();
      }
    oledDisplayString(2,20,1,"GAS SENS");
  }
  else if(currentSensor==3){
    if (temp>=32 && hum<45){
      oledDisplayString(2,20,20,"it is fire");
      oledDisplayValue(2,20,45,temp);
    }
    else{
      oledDisplayString(2,20,20,"safe");
      oledDisplayValue(2,20,45,temp);
    }
    oledDisplayString(2,2,1,"FIRE SENS");
  }
  else if(currentSensor==4){
    oledDisplayString(2,1,20,"LIGHT ON");
    whiteLED();
  }
  if (currentSensor>4){
    currentSensor=1;
  }
  lastState=currentState;
  publisher.send();//wifi
  display.display();//display
  delay(500);
}


//LED COLORS
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

void RainbowLED(int delaytime) {
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
//gas sensor function
void gassensor(int gaspin,int & gasRead){
  gasRead  = analogRead(gaspin);
  Serial.println(gasRead);
}
//humidty sensor
void humidity_temp_setup(){
  AM2320.wakeUp();
  delay(2000);
}
void temprature(int & temp){
  temp=AM2320.getTemperature();
  Serial.print("Temperature:\t");
  Serial.println(temp, 1);
}
void humidity(int & humidity){
  hum = AM2320.getHumidity();
  Serial.print("   Humidity:\t");
  Serial.println(humidity, 1);
}
void check_temp_humidity(){
  if (! AM2320.begin() )
  {
    Serial.println("Sensor not found");
    while (1);
  }
}
//buzzer song
//buzzer pin
//int buzzpin=13;
//just for fun
// class Notes{
//   private:
//   int p_note;
//   public:
//   Notes(int note):p_note(note){}
//   float get_pnote(){
//     return p_note;
//   }
//   float oct1(){
//     return (1/get_pnote()*1000000)/2;// 1/hz = sec *1000 
//   }
//   float oct2(){
//     return (1/get_pnote()*1000000)/4;
//   }
//   float oct3(){
//     return (1/get_pnote()*1000000)/8;
//   }
//   float oct4(){
//     return (1/get_pnote()*1000000)/16;
//   }
//   float oct5(){
//     return (1/get_pnote()*1000000)/36;
//   }
// };
// void forloop(int time, float note){
//   for( int i=0; i<time; i=1+i){
//     digitalWrite(buzzpin,1);
//     delayMicroseconds(note);
//     digitalWrite(buzzpin,0);
//     delayMicroseconds(note);
//   }
//notes
// Notes A(55);
// Notes B(61.74);
// Notes C(65.41);
// Notes D(73.42);
// Notes E(82.41);
// Notes F2(87.31);
// Notes G(98);
// void forloop(int time, float note);
// void jinglebell();
// void jinglebell(){ use my note class and note function to play jingle bells
//   forloop(500,E.oct5());
//   forloop(500,E.oct5());
//   forloop(1000,E.oct5());
//   //
//   forloop(500,E.oct5());
//   forloop(500,E.oct5());
//   forloop(1000,E.oct5());
//   //
//   forloop(500,E.oct5());
//   forloop(500,G.oct5());
//   forloop(500,C.oct5());
//   forloop(500,D.oct5());
//   //
//   forloop(1200,E.oct5());
//   //
//   forloop(500,F2.oct5());
//   forloop(500,F2.oct5());
//   forloop(500,F2.oct5());
//   forloop(500,F2.oct5());
//   //
//   forloop(500,F2.oct5());
//   forloop(500,E.oct5());
//   forloop(500,E.oct5());
//   forloop(500,E.oct5());
//   //
//   forloop(500,E.oct5());
//   forloop(500,D.oct5());
//   forloop(500,D.oct5());
//   forloop(500,E.oct5());
//   //
//   forloop(1000,D.oct5());
//   forloop(1000,G.oct5());
//   //
//   forloop(500,E.oct5());
//   forloop(500,E.oct5());
//   forloop(1000,E.oct5());
//   //
//   forloop(500,E.oct5());
//   forloop(500,E.oct5());
//   forloop(1000,E.oct5());
//   //
//   forloop(500,E.oct5());
//   forloop(500,G.oct5());
//   forloop(500,C.oct5());
//   forloop(500,D.oct5());
//   //
//   forloop(1200,E.oct5());
//   //
//   forloop(500,F2.oct5());
//   forloop(500,F2.oct5());
//   forloop(500,F2.oct5());
//   forloop(500,F2.oct5());
//   //
//   forloop(500,F2.oct5());
//   forloop(500,E.oct5());
//   forloop(500,E.oct5());
//   forloop(500,E.oct5());
//   //
//   forloop(500,G.oct5());
//   forloop(500,G.oct5());
//   forloop(500,F2.oct5());
//   forloop(500,D.oct5());
//   //
//   forloop(1200,C.oct5());
// }


