/*
Vibration module Keyes KY-002
*/

#define VIB_PIN 3
#define LED_PIN 13

void setup() {
    pinMode(VIB_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    Serial.begin(115200);
}


void loop() {
    int vib = digitalRead(VIB_PIN);
    Serial.println(vib);

    if (vib) digitalWrite(LED_PIN, HIGH);
    else digitalWrite(LED_PIN, LOW);

    delay(200);
}
