/*
Sensor connected with resistor 1kOm between GND and Analog input
The sensor change it impendance. In full dark it come to large value (>200 kOm),
in full light 200-300 Om (in my practice 200 Om)
*/
#define PHOTO_PIN A0

void setup(){
    Serial.begin(115200);
}


void loop() {
    int value = analogRead(PHOTO_PIN);
    int norm_value = map(value, 0, 1023, 0, 100);
    Serial.print(value);
    Serial.print(' ');
    Serial.println(norm_value);
    delay(500);
}
