/*
Sensor connected with resistor 4.7kOm between Vcc and Digital input pin.
*/

#include <OneWire.h>

OneWire ds(9);


void setup(){
    Serial.begin(115200);
}


void loop() {
    byte data[2];

    ds.reset();
    ds.write(0xCC);
    ds.write(0x44);

    delay(750);

    ds.reset();
    ds.write(0xCC);
    ds.write(0xBE);

    data[0] = ds.read();
    data[1] = ds.read();

    int temp = (data[1]<< 8)+data[0];
    temp = temp>>4;
    Serial.print("Dallas: ");
    Serial.println(temp);
}
