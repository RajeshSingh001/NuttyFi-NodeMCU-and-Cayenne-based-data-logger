#include "CayenneDefines.h"
#include "CayenneWiFi.h"
#include "CayenneWiFiClient.h"
#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#define RELAY_PIN 14 // RELAY PIN

const int sensorPin= A0; //sensor pin connected to analog pin A0
float liquid_level;
int liquid_percentage;
int top_level = 512; //calibrate the top level of sensor
int bottom_level = 3; //calibrate the bottom level of sensor

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "756nk8bzng"; // Insert your token here

char ssid[] = "ESPServer_RAJ"; // Insert your SSID here
char pwd[] = "RAJ@12345"; // Insert your SSID password here

void setup() {
  Serial.begin(115200);
  Cayenne.begin(token, ssid, pwd);
  pinMode(sensorPin, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop()
{
  liquid_level = analogRead(sensorPin);
 // liquid_percentage = ((liquid_level-bottom_level)/top_level)*100;
  Serial.println(liquid_level);
  delay(100);
  Cayenne.run();
}

CAYENNE_OUT(V10)
{
    int liquid_percentage=15;
    Cayenne.virtualWrite(V10, liquid_percentage);
}

CAYENNE_IN(V1)
{
  // get value sent from dashboard
  int currentValue = getValue.asInt(); // 0 to 1

   if (currentValue == 0)
   {
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }
}
