void ManualControl()
{
  Firebase.setInt("device/control/AutoFood", 0);
  Firebase.setInt("device/control/AutoPump", 0);
  Firebase.setInt("device/control/AutoPumpOUT", 0);
  Firebase.setInt("device/control/AutoPumpWait", 0);
  Firebase.setInt("device/control/Autoheater", 0);

  f = Firebase.getInt("device/control/Food");
  if (f == 1)
  {
    myservo.write(360); // สั่งให้ Servo หมุนวนขวา
    delay(500);         // หน่วงเวลา 2000ms
  }
  if (f == 0)
  {
    myservo.writeMicroseconds(1450); // สั่งให้ Servo หยุด
    delay(500);
  }
  digitalWrite(PUMP, Firebase.getInt("device/control/Pump"));
  digitalWrite(PUMPOUT, Firebase.getInt("device/control/PumpOUT"));
  digitalWrite(PUMPWAIT, Firebase.getInt("device/control/PumpWait"));
  digitalWrite(HEATER, Firebase.getInt("device/control/heater"));
}
