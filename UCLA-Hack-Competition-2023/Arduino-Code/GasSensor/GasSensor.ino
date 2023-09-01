//defining pins for the inputs and outputs
const int gaspin;//any pin
int gasRead = 0;
void setup()
{
  Serial.begin(9600);
}
void gassensor(int gaspin,int & gasRead){
  gasRead  = analogRead(gaspin);
  Serial.println(gasRead);
}
void loop()
{
  gassensor(gasRead);
  delay(100);
}
