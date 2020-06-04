/*
Use 4 botton touch panel TTP224 for control for lasers Keyes Q37
*/

#define TOUCH_ONE_PIN 4
#define TOUCH_TWO_PIN 5
#define LASER_ONE_PIN 8
#define LASER_TWO_PIN 9

void setup() {
    pinMode(TOUCH_ONE_PIN, INPUT);
    pinMode(TOUCH_TWO_PIN, INPUT);
    pinMode(LASER_ONE_PIN, OUTPUT);
    pinMode(LASER_TWO_PIN, OUTPUT);

    Serial.begin(115200);
}


void loop() {
    int button_1 = digitalRead(TOUCH_ONE_PIN);
    if (button_1) digitalWrite(LASER_ONE_PIN, HIGH);
    else digitalWrite(LASER_ONE_PIN, LOW);

    int button_2 = digitalRead(TOUCH_TWO_PIN);
    if (button_2) digitalWrite(LASER_TWO_PIN, HIGH);
    else digitalWrite(LASER_TWO_PIN, LOW);
}
