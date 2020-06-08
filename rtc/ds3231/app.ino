#include <Wire.h>
#include "Sodaq_DS3231.h"

char weekDay[][4] = {"", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

#define SYNC_PIN 2

void setup ()
{
    Serial.begin(115200);
    Wire.begin();
    rtc.begin();

    pinMode(SYNC_PIN, INPUT);
}

uint32_t old_ts;

void printCurrent() {
    DateTime now = rtc.now(); //get the current date-time
    uint32_t ts = now.getEpoch();

    if (old_ts == 0 || old_ts != ts) {
        old_ts = ts;
        Serial.print(now.year(), DEC);
        Serial.print('/');
        Serial.print(now.month(), DEC);
        Serial.print('/');
        Serial.print(now.date(), DEC);
        Serial.print(' ');
        Serial.print(now.hour(), DEC);
        Serial.print(':');
        Serial.print(now.minute(), DEC);
        Serial.print(':');
        Serial.print(now.second(), DEC);
        Serial.print(' ');
        Serial.print(weekDay[now.dayOfWeek()]);
        Serial.println();
        Serial.print("Seconds since Unix Epoch: ");
        Serial.print(ts, DEC);
        Serial.println();
        Serial.print("Internal temperature:");
        Serial.println(rtc.getTemperature());
    }
    delay(100);
}


void sync() {
    Serial.println("Begin sync");
    DateTime dt = DateTime(20, 6, 9, 1, 0, 40, 3);  // Su=1
    rtc.setDateTime(dt);
    Serial.println("Sync datetime");
}


void loop() {
    printCurrent();

    int value = digitalRead(SYNC_PIN);
    if (value == HIGH) {
        sync();
        delay(1000);
    }
}
