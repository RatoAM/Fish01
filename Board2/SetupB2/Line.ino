void Line()
{
  f = Firebase.getInt("device/control/AutoFood");
  P1 = Firebase.getInt("device/control/AutoPump");
  P2 = Firebase.getInt("device/control/AutoPumpOUT");
  P3 = Firebase.getInt("device/control/AutoPumpWait");
  P4 = Firebase.getInt("device/control/Autoheater");
  if (f == 1)
  {
    status1 = true;
    lineFood();
  }
  if (P1 == 1)
  {
    status2 = true;
    linePumpIn();
  }
  if (P2 == 1)
  {
    status3 = true;
    linePumpOut();
  }
  if (P3 == 1)
  {
    status3 = true;
    linePumpWait();
  }
  if (P4 == 1)
  {
    status3 = true;
    lineHeater();
  }
}

void lineFood()
{
  while (status1 == true)
  {
    LINE.notify("Food On");
    status1 = false;
  }
}

void linePumpIn()
{
  while (status2 == true)
  {
    LINE.notify("PumpIn On");
    status2 = false;
  }
}

void linePumpOut()
{
  while (status3 == true)
  {
    LINE.notify("PumpOut On");
    status3 = false;
  }
}

void linePumpWait()
{
  while (status4 == true)
  {
    LINE.notify("PumpOut On");
    status4 = false;
  }
}

void lineHeater()
{
  while (status5 == true)
  {
    LINE.notify("Heater On");
    status5 = false;
  }
}
