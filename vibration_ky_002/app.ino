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

    if (vib == LOW) {
        digitalWrite(LED_PIN, HIGH);
        delay(100); // need to see led, because very quick
    } else digitalWrite(LED_PIN, LOW);
}
