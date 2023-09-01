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
Ultrasonic_me ultrasonic1(echoPin,pingPin);
void setup() {
  Serial.begin(9600); // Starting Serial Terminal
  ultrasonic1.setup();
}
long duration=0, inch=0, cm=0;
void loop() {
  ultrasonic1.ultrasonic(duration, cm, inch);
  Serial.print(inch);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(500);
}


