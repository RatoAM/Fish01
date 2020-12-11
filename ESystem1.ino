#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>
#include <time.h>

// Config Firebase
#define FIREBASE_HOST "fish04-5c10d.firebaseio.com"
#define FIREBASE_AUTH "DLABA2V3zni6Uyob0xi6cdGCcAb8bPF3BNyPzl4t"

// Config connect WiFi
#define WIFI_SSID "Rato"
#define WIFI_PASSWORD "28032511"

//LED
#define LED_PIN D8
#define LED2_PIN D7

//time
int timezone = 7 * 3600;
int dst = 0;
const String month_name[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
const String day_name[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// get data Mega
SoftwareSerial NodeSerial(D2, D3);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  NodeSerial.begin(57600);

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

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);


  Firebase.setInt("device/control/Pump", 0);
  Firebase.setInt("device/control/Food", 0);




}

void loop() {
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

  delay(1000);
  pump();
  sensor();

  if ((p_tm->tm_hour == 17) && (p_tm->tm_min == 20) && ( p_tm->tm_sec == 00))
  {
    digitalWrite(LED2_PIN, HIGH);
    delay(10000);
    digitalWrite(LED2_PIN, LOW);
  }
   if ((p_tm->tm_hour == 17) && (p_tm->tm_min == 22) && ( p_tm->tm_sec == 00))
  {
    digitalWrite(LED2_PIN, HIGH);
    delay(10000);
    digitalWrite(LED2_PIN, LOW);
  }






}

// SENSOR TO FIREBASE

void sensor() {
  // Read temp & Humidity for DHT22
  int tb = NodeSerial.parseInt();
  float tp = NodeSerial.parseFloat();

  if (isnan(tp) || isnan(tb)) {
    Serial.println("Failed to read from sensor!");
    delay(500);
    return;
  }

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["temperature"] = tp;
  root["turbidity"] = tb;

  String name = Firebase.push("logSensor", root);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logSensor failed:");
    Serial.println(Firebase.error());
    return;
  }
  Serial.print("pushed: /logSensor/");
  Serial.println(name);
  digitalWrite(LED_PIN, Firebase.getInt("device/control/Pump"));
  delay(200);
  digitalWrite(LED2_PIN, Firebase.getInt("device/control/Food"));
  delay(200);


  // Pump Auto
  if (tb > 600) {
    digitalWrite(LED_PIN, 1);
    delay(10000);
    digitalWrite(LED_PIN, 0);
  }
  /*if(ph > 150){digitalWrite(LED_PIN, Firebase.getInt("device/led_control/Pump", 1));
    delay(200);}*/




}

// MANNUAL

void pump() {
  digitalWrite(LED_PIN, Firebase.getInt("device/control/Pump"));
  delay(200);
  digitalWrite(LED2_PIN, Firebase.getInt("device/control/Food"));
  delay(200);

}
