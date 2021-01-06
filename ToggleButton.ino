
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <time.h>
#include "Nextion.h"
#include <SoftwareSerial.h>
#include <Nextion.h>

SoftwareSerial nextion(1, D1);// Nextion TX to pin 2 and RX to pin 3 of Arduino

Nextion NexText(nextion, 9600); //create a Nextion object named myNextion using the nextion serial port @ 9600bps

const int SWITCH_ON = 1;
const int SWITCH_OFF = 0;
const int SWITCH2_ON = 1;
const int SWITCH2_OFF = 0;

byte received_data[4];
byte received2_data[4];
int  switch_pos;
int  switch2_pos;

// Config Firebase
#define FIREBASE_HOST "fish04-5c10d.firebaseio.com"
#define FIREBASE_AUTH "DLABA2V3zni6Uyob0xi6cdGCcAb8bPF3BNyPzl4t"

// Config connect WiFi
#define WIFI_SSID "Rato"
#define WIFI_PASSWORD "28032511"

//LED
#define FOOD D8
#define PUMP D7
#define PUMPOUT D6

//ph
#define SensorPin A0          // the pH meter Analog output is connected with the Arduino’s Analog
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;

//temp
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//ultra
#define trigpin 14  
#define echopin 16 

//time
int timezone = 7 * 3600;
int dst = 0;
const String month_name[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
const String day_name[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//mode
bool AppMode = 0;
bool HmiMode = 0;

// get data Mega
SoftwareSerial NodeSerial(D2, D3);

void setup() {
  
  Serial.begin(115200);
  Serial.begin(9600);
  NodeSerial.begin(57600);
  Serial.setDebugOutput(true);
  NexText.init(); // send the initialization commands for Page 0
  Serial.println("ready");
  
//sensor
  sensors.begin();
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  delay(500);
  
//tools
   pinMode(FOOD,OUTPUT);
   pinMode(PUMP, OUTPUT);
   pinMode(PUMPOUT, OUTPUT);
  
//wifi
  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");

  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

//Firebase

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("device/control/Pump", 0);
  Firebase.setInt("device/control/Food", 0);
  Firebase.setInt("device/control/PumpOUT", 0);

 

}

void loop() {
 int i;
  
      sensor();
      AppMode = Firebase.getInt("device/Mode/AppMode");
      HmiMode = Firebase.getInt("device/Mode/HmiMode");
     
      if(AppMode == 1){
        
      //Time();
      pump();
      
      }
      if(HmiMode == 1){
      switch_control();
      switch2_control();
      pump2();
      }

}


void switch_control() {
     
    int size = Serial.readBytesUntil('\n', received_data, 4);
    // First Byte has the switch position data 
    switch_pos = received_data[0];
    Serial.print("SWITCH:");
    if (switch_pos == SWITCH_ON) {
      Serial.println("ON");
      Firebase.setInt("device/control/Food", 1);
      
    }
    if (switch_pos == SWITCH_OFF) {
      Serial.println("OFF");
      Firebase.setInt("device/control/Food", 0);
      
    }
}
void switch2_control() {
      
    int size = Serial.readBytesUntil('\n', received2_data, 4);
    // First Byte has the switch position data 
    switch2_pos = received2_data[0];
    Serial.print("SWITCH:");

    
    if (switch2_pos == SWITCH2_ON) {
      Serial.println("ON");
      Firebase.setInt("device/control/Pump", 1);
       
    }
    if (switch2_pos == SWITCH2_OFF) {
      Serial.println("OFF");
      Firebase.setInt("device/control/Pump", 0);
       
       
      
    }
}

void pump() {
  digitalWrite(PUMP, Firebase.getInt("device/control/Pump"));
  waterDetectPumpIn();
  digitalWrite(PUMPOUT, Firebase.getInt("device/control/PumpOUT"));
  waterDetectPumpOut();
  digitalWrite(FOOD, Firebase.getInt("device/control/Food"));
  
     
}
void pump2() {
  digitalWrite(PUMP, Firebase.getInt("device/control/Pump"));
  digitalWrite(FOOD, Firebase.getInt("device/control/Food"));
  digitalWrite(PUMPOUT, Firebase.getInt("device/control/PumpOUT"));
     
}

/*
void WaterDetect(){
  int duration, distance;
 digitalWrite(trigpin, HIGH);
 
delayMicroseconds(10);  
digitalWrite(trigpin, LOW);
 
 
duration = pulseIn(echopin,HIGH);
 
distance = ( duration / 2) / 29.1;
Serial.println("cm:"); 
Serial.println(distance);
delay(500);
 
if(  (distance > 10) && (distance <= 20)   ) 
{
  Firebase.setInt("device/control/Pump", 0);
  digitalWrite(PUMP, Firebase.getInt("device/control/Pump"));
  Firebase.setInt("device/control/PumpOUT", 1); 
  digitalWrite(PUMPOUT, Firebase.getInt("device/control/PumpOUT"));

} else
if(  (distance > 200) && (distance <= 220)  ) 
{
  Firebase.setInt("device/control/Pump", 1);
  digitalWrite(PUMP, Firebase.getInt("device/control/Pump"));
  Firebase.setInt("device/control/PumpOUT", 0);  
  digitalWrite(PUMPOUT, Firebase.getInt("device/control/PumpOUT"));
}  else
 
if(  distance < 10 ) 
{
  Firebase.setInt("device/control/Pump", 0);
  digitalWrite(PUMP, Firebase.getInt("device/control/Pump")); 
  Firebase.setInt("device/control/PumpOUT", 0); 
  digitalWrite(PUMPOUT, Firebase.getInt("device/control/PumpOUT"));

} 
}*/

void waterDetectPumpIn(){
  int duration, distance;
 digitalWrite(trigpin, HIGH);
 
delayMicroseconds(10);  
digitalWrite(trigpin, LOW);
 
 
duration = pulseIn(echopin,HIGH);
 
distance = ( duration / 2) / 29.1;
Serial.println("cm:"); 
Serial.println(distance);
delay(500);

  if(  (distance > 10) && (distance <= 20)   ) 
{
  Firebase.setInt("device/control/Pump", 0);
  digitalWrite(PUMP, Firebase.getInt("device/control/Pump"));
}
  }

void waterDetectPumpOut(){
  int duration, distance;
 digitalWrite(trigpin, HIGH);
 
delayMicroseconds(10);  
digitalWrite(trigpin, LOW);
 
 
duration = pulseIn(echopin,HIGH);
 
distance = ( duration / 2) / 29.1;
Serial.println("cm:"); 
Serial.println(distance);
delay(500);

  if(  (distance > 30) && (distance <= 40)   ) 
{
  Firebase.setInt("device/control/PumpOUT", 0);
  digitalWrite(PUMP, Firebase.getInt("device/control/PumpOUT"));
}
  }




 // SENSOR TO FIREBASE
void sensor() {
  
   {
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
   }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  int ph=(int)avgValue*5.0/1024/6; //convert the analog into millivolt
  ph=3.5*ph;                      //convert the millivolt into pH value
  Serial.print("    pH:");  
  Serial.print(ph,2);
  Serial.println(" ");

  int tp = sensors.getTempCByIndex(0);
  sensors.requestTemperatures();
  Serial.print("Water Temp ");
  Serial.print(tp);
  Serial.println(" *C");

  //int tp = NodeSerial.parseInt();
  int tb = NodeSerial.parseInt();
  //float ph = NodeSerial.parseFloat();

  NexText.setComponentText("g0", "Automatic Nursery Tilapia System");
  NexText.setComponentText("temp", String(tp));
  NexText.setComponentText("terbi", String(tb)); 
  NexText.setComponentText("ph", String(ph));



  digitalWrite(PUMP, Firebase.getInt("device/control/Pump"));
  delay(200);
  digitalWrite(FOOD, Firebase.getInt("device/control/Food"));
  delay(200);

  
   Firebase.set("Sensor/Temp",tp);
   Firebase.set("Sensor/Turbidity",tb);
   Firebase.set("Sensor/PH",ph);


  // Pump Auto
  if (tb > 900) {
    Firebase.setInt("device/control/PumpOUT", 1);
    digitalWrite(PUMP, Firebase.getInt("device/control/PumpOUT"));
    waterDetectPumpOut();
    delay(5000);
    Firebase.setInt("device/control/Pump", 1);
    digitalWrite(PUMP, Firebase.getInt("device/control/Pump"));
    waterDetectPumpIn();

  }
 if (ph > 200) {
    Firebase.setInt("device/control/PumpOUT", 1);
    digitalWrite(PUMP, Firebase.getInt("device/control/PumpOUT"));
    waterDetectPumpOut();
    delay(5000);
    Firebase.setInt("device/control/Pump", 1);
    digitalWrite(PUMP, Firebase.getInt("device/control/Pump"));
    waterDetectPumpIn();
  }


  
}

void Time(){
  // AUTO 
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  delay(1000);
  Serial.print(p_tm->tm_hour);
  Serial.print(":");
  Serial.print(p_tm->tm_min);
  Serial.print(":");
  Serial.print(p_tm->tm_sec);

  Serial.print(" / ");
  Serial.print(day_name[(p_tm->tm_wday)]);
  Serial.print("/");
  Serial.print(p_tm->tm_mday);
  Serial.print(" / ");
  Serial.print(month_name[(p_tm->tm_mon)]);
  Serial.print(" / ");
  Serial.print(p_tm->tm_year + 2443);
  Serial.println("");

  delay(500);


  if ((p_tm->tm_hour == 11) && (p_tm->tm_min == 32) && ( p_tm->tm_sec == 00))
  {
    Firebase.setInt("device/control/Food", 1);
    digitalWrite(FOOD, Firebase.getInt("device/control/Food"));
    delay(10000);
    Firebase.setInt("device/control/Food", 0);
    digitalWrite(FOOD, Firebase.getInt("device/control/Food"));
  }
   if ((p_tm->tm_hour == 17) && (p_tm->tm_min == 22) && ( p_tm->tm_sec == 00))
  {
    Firebase.setInt("device/control/Food", 1);
    digitalWrite(FOOD, Firebase.getInt("device/control/Food"));
    delay(10000);
    Firebase.setInt("device/control/Food", 0);
    digitalWrite(FOOD, Firebase.getInt("device/control/Food"));
  }

  }
  
