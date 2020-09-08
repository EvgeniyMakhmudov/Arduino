#include <Stepper.h>

#define POT_PIN A0
#define STEPS_AMOUNT 64


Stepper myStepper(STEPS_AMOUNT, 8,9,10,11);


void setup() {
    myStepper.setSpeed(10);
    pinMode(POT_PIN, INPUT);
    Serial.begin(115200);
}


void loop() {
    int value = analogRead(POT_PIN);
    int mV = map(value, 0, 1023, 0, 3300);
    int step = map(mV, 0, 3300, 0, STEPS_AMOUNT - 1);

    Serial.print("Step = ");
    Serial.println(step);
    myStepper.step(step);
    delay(2000);
}
