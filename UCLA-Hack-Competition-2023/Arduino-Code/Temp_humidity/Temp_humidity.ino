#include <AM232X.h>//temp sensor
AM232X AM2320;
int temp=0;
int hum=0;
void humidity_temp_setup(){
  AM2320.wakeUp();
  delay(2000);
}
void setup(){
  Serial.begin(115200);
  humidity_temp_setup();
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
void loop()
{
  // READ DATA
  check_temp_humidity();
  temprature(temp);
  humidity(hum);
  delay(2000);
}
