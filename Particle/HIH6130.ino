// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// HIH6130
// This code is designed to work with the HIH6130_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Temperature?sku=HIH6130_I2CS#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// HIH6130 I2C address is 0x27(39)
#define Addr 0x27

float cTemp = 0.0, fTemp = 0.0, humidity = 0.0;
int temp = 0;

void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "HIH6130");
  Particle.variable("humidity", humidity);
  Particle.variable("cTemp", cTemp);

  // Initialise I2C communication
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(9600);
  delay(300);
}

void loop()
{
  unsigned int data[4];

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 4 bytes of data
  Wire.requestFrom(Addr, 4);

  // Read 4 bytes of data
  // humidity msb, humidity lsb, temp msb, temp lsb
  if (Wire.available() == 4)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
  }

  // Convert the data to 14-bits
  humidity = (((data[0] & 0x3F) * 256) + data[1]) / 16384.0 * 100.0;
  temp = (((data[2] * 256) + (data[3] & 0xFC)) / 4);
  cTemp = (temp / 16384.0) * 165.0 - 40.0;
  fTemp = cTemp * 1.8 + 32;

  // Output data to dashboard
  Particle.publish("Relative Humidity : ", String(humidity));
  Particle.publish("Temperature in Celsius : ", String(cTemp));
  Particle.publish("Temperature in Fahrenheit : ", String(fTemp));
  delay(1000);
}

