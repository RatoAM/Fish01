#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <time.h>
#include <Servo.h>
#include <TridentTD_LineNotify.h>

// Config Firebase
#define FIREBASE_HOST "nurserytilapia-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "PkYbVEoouULXjafgwZTCi579xSnnriPpUk18Mvu6"

// Config connect WiFi
#define WIFI_SSID "Rato"  
#define WIFI_PASSWORD "28032511"
#define LINE_TOKEN "q5aKSvMPTGjwSYJK19B9UEI5vv8jmyj82DQk8uiJnBN"
//define
#define PUMP D7
#define PUMPOUT D2
#define PUMPWAIT D3
#define HEATER D4

//Food
Servo myservo;
int f, ht, P1, P2, P3, P4;
int sensorPin = A0;
//status
bool food1 = true;
bool pump1 = false;
bool pump2 = true;
bool heater = true;
bool status1 = true;
bool status2 = true;
bool status3 = true;
bool status4 = true;
bool status5 = true;

//time
int timezone = 7 * 3600;
int dst = 0;
//const String month_name[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
//const String day_name[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//mode
bool AutoMode = 0;
bool ManualMode = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("ready");
  Serial.println(LINE.getVersion());

  //TB
  pinMode(A0, INPUT);

  //tools
  pinMode(PUMP, OUTPUT);
  pinMode(PUMPOUT, OUTPUT);
  pinMode(PUMPWAIT, OUTPUT);
  pinMode(HEATER, OUTPUT);

  //Food
  myservo.attach(14); //D5

  //wifi
  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for time");
  while (!time(nullptr))
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");

  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  //Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);
}

void loop()
{
  Turbi();
  AutoTime();
  AutoMode = Firebase.getInt("device/Mode/AutoMode");
  ManualMode = Firebase.getInt("device/Mode/ManualMode");

  if (AutoMode == 1)
  {

    AutoControl();
    Line();
    Serial.println("A mode");
  }
  if (ManualMode == 1)
  {
    ManualControl();
    Serial.println("M mode");
  }
}

void Turbi()
{
  int sensorValue = analogRead(sensorPin);
  int turbidity = map(sensorValue, 0, 640, 100, 0);
  Firebase.set("Sensor/Turbidity", turbidity);
  Serial.println(turbidity);
}
