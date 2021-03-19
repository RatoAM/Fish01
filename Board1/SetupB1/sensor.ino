// SENSOR TO FIREBASE
void sensor()
{

  {
    for (int i = 0; i < 10; i++) //Get 10 sample value from the sensor for smooth the value
    {
      buf[i] = analogRead(SensorPin);
      delay(10);
    }
    for (int i = 0; i < 9; i++) //sort the analog from small to large
    {
      for (int j = i + 1; j < 10; j++)
      {
        if (buf[i] > buf[j])
        {
          temp = buf[i];
          buf[i] = buf[j];
          buf[j] = temp;
        }
      }
    }
  }
  avgValue = 0;
  for (int i = 2; i < 8; i++) //take the average value of 6 center sample
    avgValue += buf[i];
  ph = (int)avgValue * 5.0 / 1024 / 6; //convert the analog into millivolt
  ph = 3.5 * ph;                       //convert the millivolt into pH value

  tp = sensors.getTempCByIndex(0);
  sensors.requestTemperatures();
  Serial.println(tp);

  //tb
  tb = Firebase.getInt("Sensor/Turbidity");
  pi = Firebase.getInt("Sensor/Ratio");

  
  NexText.setComponentText("temp", String(tp));
  NexText.setComponentText("turbi", String(tb));
  NexText.setComponentText("ph", String(ph));
  




  Firebase.set("Sensor/Temp", tp);
  Firebase.set("Sensor/Turbidity", tb);
  Firebase.set("Sensor/PH", ph);
  

  String tpst = (String)tp;
  String tbst = (String)tb;
  String phst = (String)ph;
  String pist = (String)pi;

  String data = "field1=" + tpst + "&field2=" + tbst + "&field3=" + phst + "&field4=" + pist;

  if (client.connect(thingSpeakAddress, 80))
  {
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data.length());
    client.print("\n\n");
    client.print(data);
  }
}
