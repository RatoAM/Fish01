
#include <SoftwareSerial.h>
SoftwareSerial UnoSerial(3, 2);// RX | TX
int sensorPin = A0;

void setup()
{

  pinMode(A0, INPUT);
  pinMode(3, INPUT);
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  

  UnoSerial.begin(57600);

   

}
void loop() {

  int sensorValue = analogRead(sensorPin);
  int turbidity = map(sensorValue, 0,640, 100, 0);
  delay(100);
  

  Serial.print("Turbi ");
  Serial.print(turbidity);
  if (turbidity < 20) {
    Serial.println(" its CLEAR ");

  }
  if ((turbidity > 10) && (turbidity < 50)) {
   Serial.println(" its CLOUDY ");
  
  }
  if (turbidity > 50) {
    Serial.println(" its DIRTY ");
  }
  delay(1000);
  

//ส่งค่า terbi
  UnoSerial.print(turbidity);
  UnoSerial.print("\n");


   

}
