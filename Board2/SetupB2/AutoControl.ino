void AutoControl()
{
  Firebase.setInt("device/control/Food", 0);
  Firebase.setInt("device/control/Pump", 0);
  Firebase.setInt("device/control/PumpOUT", 0);
  Firebase.setInt("device/control/PumpWait", 0);
  Firebase.setInt("device/control/heater", 0);

  f = Firebase.getInt("device/control/AutoFood");
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
  digitalWrite(PUMP, Firebase.getInt("device/control/AutoPump"));
  digitalWrite(PUMPOUT, Firebase.getInt("device/control/AutoPumpOUT"));
  digitalWrite(PUMPWAIT, Firebase.getInt("device/control/AutoPumpWait"));
  digitalWrite(HEATER, Firebase.getInt("device/control/Autoheater"));
}
