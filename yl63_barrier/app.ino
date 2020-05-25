/*
Use YL63 sensor to signall when barrier finded.
*/

#define YL63_PIN 7
#define LED_PIN 13

bool led_on = false;

void setup(){
    pinMode(YL63_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(115200);
}


void loop(){
    int barrier = digitalRead(YL63_PIN);
    if (!barrier) led_on = !led_on;

    if (led_on) {
        digitalWrite(LED_PIN, HIGH);
    }
    else {
        digitalWrite(LED_PIN, LOW);
    }

    Serial.print(barrier);
    Serial.print(", ");
    Serial.println(led_on);
    delay(500);
}
