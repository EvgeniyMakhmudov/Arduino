/*
LED simulate heartbeat. If distance small, heart beat is quick.
If distance far the heart beat is slow.
*/

#include <HCSR04.h>

int TRIG_PIN = 8;
int ECHO_PIN = 9;
int LED_PIN = 13;

UltraSonicDistanceSensor distanceSensor(TRIG_PIN, ECHO_PIN);

void setup()
{
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    pinMode(LED_PIN, OUTPUT);

    Serial.begin(115200);
}


int convertCmToHz(int distance) {
    if (distance < 10)
        return 120;
    else if (distance > 120)
        return 60;
    else
        return map(distance, 10, 120, 120, 60);
}

void makeHeartBeat(int hz){
    float d = 60.0 / hz;
    int beat = int(100 * d);
    int sleep = int(1000 * d);

    digitalWrite(LED_PIN, HIGH);
    delay(beat);
    digitalWrite(LED_PIN, LOW);
    delay(beat);
    digitalWrite(LED_PIN, HIGH);
    delay(beat);
    digitalWrite(LED_PIN, LOW);

    Serial.print(sleep);
    Serial.print(", ");
    Serial.println(beat);

    delay(sleep);
}


void loop()
{
    int distance =int(distanceSensor.measureDistanceCm());
    int hz = convertCmToHz(distance);
    Serial.print(distance);
    Serial.print(", ");
    Serial.print(hz);
    Serial.print(", ");

    makeHeartBeat(hz);

    Serial.flush();
}
