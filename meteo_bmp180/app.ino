#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp180;

void setup()
{
    Serial.begin(115200);

    if (!bmp180.begin()) {
        Serial.println("Could not find a valid BMP180 sensor, check wiring!");
        while (true) delay(100);
    }
}

void loop()
{
    Serial.print("Temperature = ");
    Serial.print(bmp180.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");
    Serial.print(int(bmp180.readPressure() / 133.3224));
    Serial.println(" mm Hg");

    Serial.print("Altitude = ");
    Serial.print(bmp180.readAltitude());
    Serial.println(" meters");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(int(bmp180.readSealevelPressure() / 133.3224));
    Serial.println(" mm Hg");

    Serial.print("Real altitude = ");
    Serial.print(bmp180.readAltitude(101500));
    Serial.println(" meters");

    Serial.println();
    delay(1000);
}
