 #include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>
#include <Nextion.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>


// Config Firebase
#define FIREBASE_HOST "nurserytilapia-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "PkYbVEoouULXjafgwZTCi579xSnnriPpUk18Mvu6"

// Config connect WiFi
#define WIFI_SSID "Rato"
#define WIFI_PASSWORD "28032511"

//define
#define SensorPin A0
#define ONE_WIRE_BUS 5 //D1
#define trigpin 4      //D2
#define echopin 0      //D3

// ThingSpeak Settings //
char thingSpeakAddress[] = "api.thingspeak.com";
String writeAPIKey = "9I1S2YVB2KSUJ75O";
WiFiClient client;

int f, tb, ph, tp, pi;
int F, H, WtIn, WtOut, WtH;
//mode
bool AutoMode = 0;
bool ManualMode = 0;

SoftwareSerial nextion(3, D5);  // TX RX
Nextion NexText(nextion, 9600); //ชื่อตัวเเปลและความถี่
//temp
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//ph
unsigned long int avgValue; //Store the average value of the sensor feedback
float b;
int buf[10], temp;



void setup()
{
  Serial.begin(115200);
  Serial.begin(9600);
  Serial.setDebugOutput(true);
  NexText.init(); // send the initialization commands for Page 0
  Serial.println("ready");

  //sensor
  sensors.begin();
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  delay(10);

  //wifi
  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(10);
  }
  Serial.println("");

  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  //Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(3000);
}


void loop()
{
  sensor();
  ValueButton();  
  AutoMode = Firebase.getInt("device/Mode/AutoMode");
  ManualMode = Firebase.getInt("device/Mode/ManualMode");
    if (AutoMode == 1)
  {
    Auto();
    waterDetectPumpIn();
    waterDetectPumpOut();
    
    Serial.println("A mode");
  }
  if (ManualMode == 1)
  {
    switch_control();
    Serial.println("M mode");
  }
}
