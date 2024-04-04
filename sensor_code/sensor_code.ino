#include <DHT.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22 (AM2302)
#define SOIL_MOISTURE_PIN A0 // Analog pin connected to the soil moisture sensor
#define FLOW_SENSOR_PIN 3 // Digital pin connected to the water flow sensor
#define RELAY_PIN 4 // Digital pin connected to the relay module

DHT dht(DHTPIN, DHTTYPE);

const int OpenAirReading = 700;   // Calibration data 1
const int WaterReading = 280;     // Calibration data 2
int MoistureLevel = 0;
int SoilMoisturePercentage = 0;

volatile unsigned long pulseCount = 0; // Variable to count pulses
unsigned long flowRate = 0; // Variable to store the flow rate
unsigned long lastMillis = 0; // Variable to store the last time the flow rate was calculated

void setup() {
 Serial.begin(9600); // Open serial port, set the baud rate to 9600 bps
 dht.begin();
 pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP); // Set the sensor pin as input with pull-up resistor
 attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), countPulse, RISING); // Attach interrupt to the sensor pin
 pinMode(RELAY_PIN, OUTPUT); // Set the relay pin as output
}

void loop() {
 // Read soil moisture
 MoistureLevel = analogRead(SOIL_MOISTURE_PIN); // Read the analog value from the sensor connected to A0
 SoilMoisturePercentage = map(MoistureLevel, OpenAirReading, WaterReading, 0, 100);

 if (SoilMoisturePercentage >= 100) {
    Serial.println("\n Maximum - 100 %");
 } else if (SoilMoisturePercentage <= 0) {
    Serial.println("\n Minimum - 0 %");
 } else if (SoilMoisturePercentage > 0 && SoilMoisturePercentage < 100) {
    Serial.print("Soil Moisture: ");
    Serial.print(SoilMoisturePercentage);
    Serial.println("%");
 }

 // Control relay based on soil moisture level
 if (SoilMoisturePercentage < 600) {
    digitalWrite(RELAY_PIN, HIGH); // Turn on the relay
    Serial.println("Relay turned ON due to low soil moisture.");
 } else {
    digitalWrite(RELAY_PIN, LOW); // Turn off the relay
    Serial.println("Relay turned OFF.");
 }

 // Read DHT22 sensor
 delay(2000); // Wait a few seconds between measurements.
 float h = dht.readHumidity();
 float t = dht.readTemperature();
 float f = dht.readTemperature(true);

 // Check if any reads failed and exit early (to try again).
 if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
 }

 // Compute heat index in Fahrenheit (the default)
 float hif = dht.computeHeatIndex(f, h);
 // Compute heat index in Celsius (isFahreheit = false)
 float hic = dht.computeHeatIndex(t, h, false);

 Serial.print("Humidity: ");
 Serial.print(h);
 Serial.print(" %\t");
 Serial.print("Temperature: ");
 Serial.print(t);
 Serial.print(" *C ");
 Serial.print(f);
 Serial.print(" *F\t");
 Serial.print("Heat index: ");
 Serial.print(hic);
 Serial.print(" *C ");
 Serial.print(hif);
 Serial.println(" *F");

 // Read water flow sensor
 unsigned long currentMillis = millis(); // Get the current time
 if (currentMillis - lastMillis >= 1000) { // Check if a second has passed
    detachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN)); // Temporarily detach the interrupt
    flowRate = pulseCount; // Calculate the flow rate
    pulseCount = 0; // Reset the pulse count
    attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), countPulse, RISING); // Reattach the interrupt
    lastMillis = currentMillis; // Update the last time the flow rate was calculated
    Serial.print("Flow Rate: ");
    Serial.print(flowRate);
    Serial.println(" L/min"); // Print the flow rate
 }

 delay(1000); // Wait for a second before taking the next reading
}

void countPulse() {
 pulseCount++; // Increment the pulse count
}
