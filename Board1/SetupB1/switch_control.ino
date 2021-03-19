void switch_control()
{
  String indata = Serial.readStringUntil('#');
  if (indata.indexOf("Fon") > -1)
  {
    Firebase.setInt("device/control/Food", 1);
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
  }
  else if (indata.indexOf("Foff") > -1)
  {
    Firebase.setInt("device/control/Food", 0);
    Firebase.setInt("device/control/AutoFood", 0);
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
  }
  if (indata.indexOf("Hon") > -1)
  {
    Firebase.setInt("device/control/heater", 1);
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
  }
  else if (indata.indexOf("Hoff") > -1)
  {
    Firebase.setInt("device/control/heater", 0);
    Firebase.setInt("device/control/Autoheater", 0);
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
  }
  if (indata.indexOf("Pon") > -1)
  {
    Firebase.setInt("device/control/Pump", 1);
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
  }
  else if (indata.indexOf("Poff") > -1)
  {
    Firebase.setInt("device/control/Pump", 0);
    Firebase.setInt("device/control/AutoPump", 0);
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
  }
  if (indata.indexOf("P2on") > -1)
  {
    Firebase.setInt("device/control/PumpOUT", 1);
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
  }
  else if (indata.indexOf("P2off") > -1)
  {
    Firebase.setInt("device/control/PumpOUT", 0);
    Firebase.setInt("device/control/AutoPumpOUT", 0);
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
  }
  if (indata.indexOf("P3on") > -1)
  {
    Firebase.setInt("device/control/PumpWait", 1);
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
  }
  else if (indata.indexOf("P3off") > -1)
  {
    Firebase.setInt("device/control/PumpWait", 0);
    Firebase.setInt("device/control/AutoPumpWait", 0);
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
  }
  else if (indata.indexOf("Auto") > -1)
  {
    Firebase.setInt("device/Mode/AutoMode", 1);
    Firebase.setInt("device/Mode/ManualMode", 0);
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
  }
  else if (indata.indexOf("Man") > -1)
  {
    Firebase.setInt("device/Mode/AutoMode", 0);
    Firebase.setInt("device/Mode/ManualMode", 1);
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
  }
}
