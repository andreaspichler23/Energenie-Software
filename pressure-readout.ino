const int sensorPin = A0;
int x = 0;
int y = 1;
int z = 2;
int a = 3;
int b = 4 ;
int c = 5;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  int sensorVal = analogRead(sensorPin);
 // Serial.print("Sensor Value: ");
 // Serial.print(sensorVal);

  float voltage = (sensorVal/1024.0)*5;
  //Serial.print(", Volts: ");
  //Serial.print(voltage);

  float pressure = pow(10,2*voltage-10.5);
  Serial.print(", Pressure: ");
  Serial.print(pressure,12);

  Serial.println(" ");
  delay(10000); // ms
  

}
