
#define PHOTO_PIN 4
#define LED_PIN 13


void setup(){
    pinMode(PHOTO_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(115200);
}


void loop(){
    int value = digitalRead(PHOTO_PIN);
    Serial.println(value);

    digitalWrite(LED_PIN, value);
    delay(500);
}
