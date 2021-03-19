void AutoTime()
{
  // AUTO
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
  time_t now = time(nullptr);
  struct tm *p_tm = localtime(&now);
  delay(30);

  if ((p_tm->tm_hour == 6) && (p_tm->tm_min == 00) && (p_tm->tm_sec == 00)) //ครั้งที่ 1
  {
    Firebase.setInt("device/control/AutoFood", 1);
    delay(10000);
    Firebase.setInt("device/control/AutoFood", 0);
  }
  if ((p_tm->tm_hour == 8) && (p_tm->tm_min == 00) && (p_tm->tm_sec == 00)) //ครั้งที่ 2
  {
    Firebase.setInt("device/control/AutoFood", 1);
    delay(10000);
    Firebase.setInt("device/control/AutoFood", 0);
  }
  if ((p_tm->tm_hour == 10) && (p_tm->tm_min == 00) && (p_tm->tm_sec == 00)) //ครั้งที่ 3
  {
    Firebase.setInt("device/control/AutoFood", 1);
    delay(10000);
    Firebase.setInt("device/control/AutoFood", 0);
  }
  if ((p_tm->tm_hour == 12) && (p_tm->tm_min == 00) && (p_tm->tm_sec == 00)) //ครั้งที่ 4
  {
    Firebase.setInt("device/control/AutoFood", 1);
    delay(10000);
    Firebase.setInt("device/control/AutoFood", 0);
  }
  if ((p_tm->tm_hour == 14) && (p_tm->tm_min == 00) && (p_tm->tm_sec == 00)) //ครั้งที่ 5
  {
    Firebase.setInt("device/control/AutoFood", 1);
    delay(10000);
    Firebase.setInt("device/control/AutoFood", 0);
  }
  if ((p_tm->tm_hour == 16) && (p_tm->tm_min == 00) && (p_tm->tm_sec == 00)) //ครั้งที่ 6
  {
    Firebase.setInt("device/control/AutoFood", 1);
    delay(10000);
    Firebase.setInt("device/control/AutoFood", 0);
  }
}
