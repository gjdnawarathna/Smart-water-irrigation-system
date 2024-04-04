#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "9CjA1u-PxNwNIkCIlMII6PyUr2K_QCl0";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "janith";
char pass[] = "janith123";

void setup()
{
 // Debug console
 Serial.begin(9600);

 Blynk.begin(auth, ssid, pass);
}

void loop()
{
 Blynk.run();

 // Read data from Arduino Mega over serial
 if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    int index = data.indexOf(":");
    if (index != -1) {
      String key = data.substring(0, index);
      String value = data.substring(index + 1);
      if (key == "soilMoisture") {
        Blynk.virtualWrite(V1, value.toInt());
      } else if (key == "humidity") {
        Blynk.virtualWrite(V2, value.toFloat());
      } else if (key == "temperature") {
        Blynk.virtualWrite(V3, value.toFloat());
      } else if (key == "flowRate") {
        Blynk.virtualWrite(V4, value.toInt());
      }
    }
 }
}
