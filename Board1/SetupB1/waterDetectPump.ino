void waterDetectPumpIn()
{
  int duration, distance;
  digitalWrite(trigpin, HIGH);

  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  duration = pulseIn(echopin, HIGH);

  distance = (duration / 2) / 29.1;

  if ((distance > 10) && (distance <= 20))
  {
    Firebase.setInt("device/control/AutoPump", 0);
  }
}

void waterDetectPumpOut()
{
  int duration, distance;
  digitalWrite(trigpin, HIGH);

  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  duration = pulseIn(echopin, HIGH);

  distance = (duration / 2) / 29.1;

  if ((distance > 30) && (distance <= 40))
  {
    Firebase.setInt("device/control/AutoPumpOUT", 0);
  }
}
