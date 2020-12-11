
#include <SoftwareSerial.h>
SoftwareSerial UnoSerial(3, 2);// RX | TX
#include <OneWire.h>
#include <DallasTemperature.h>
int LED = 13;
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup()
{

  pinMode(A0, INPUT);
  pinMode(3, INPUT);
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  UnoSerial.begin(57600);
  UnoSerial.begin(57600);

  sensors.begin();

}
void loop() {
  float tp = sensors.getTempCByIndex(0);
  int tb = analogRead(A0);
  sensors.requestTemperatures();


  Serial.print("Water Temp ");
  Serial.print(tp, 1);
  Serial.println(" *C");
//ส่งค่า tem
  UnoSerial.print(tp);
  UnoSerial.print("\n");
  delay(2000);
  Serial.print("Turbi ");
  Serial.print(tb, 1);
  Serial.print(" NTU ");
//ส่งค่า terbi
  UnoSerial.print(tb);
  UnoSerial.print("\n");

  




}
