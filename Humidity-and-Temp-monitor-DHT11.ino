#include "DHT.h"

#define DHTPIN A0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int greenPin = 3;
const int yellowPin = 4;
const int redPin = 5;

void setup() {
  Serial.begin(9600);
  Serial.println(F("\nStarting DHT11 sensor"));

  dht.begin();

  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);

  digitalWrite(redPin, HIGH);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(greenPin, HIGH);
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));

    digitalWrite(redPin, HIGH);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(greenPin, HIGH);
    return;
  }

  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);

  if (h >= 40.0 && h <= 60.0) {
    digitalWrite(greenPin, HIGH); // ideal
  } 
  else if ((h >= 30.0 && h < 40.0) || (h > 60.0 && h <= 75.0)) {
    digitalWrite(yellowPin, HIGH); // moderate
  } 
  else {
    digitalWrite(redPin, HIGH); // poor (too dry or too humid)
  }
  
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  |  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C"));

}
