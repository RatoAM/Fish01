void Auto()
{
  // Pump Auto
  if (tb > 900)
  {
    Firebase.setInt("device/control/AutoPumpOUT", 1);
    waterDetectPumpOut();
    Firebase.setInt("device/control/AutoPump", 1);
    waterDetectPumpIn();
  }
  if (ph > 200)
  {
    Firebase.setInt("device/control/AutoPumpOUT", 1);
    waterDetectPumpOut();
    Firebase.setInt("device/control/AutoPump", 1);
    waterDetectPumpIn();
  }
  if (tp < 26)
  {
    Firebase.setInt("device/control/Autoheater", 1);
  }
  if (tp > 26)
  {
    Firebase.setInt("device/control/Autoheater", 0);
  }
}
