// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MXC6226XU
// This code is designed to work with the MXC6226XU_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=MXC6226XU_I2CS#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// MXC6226XU I2C address is 0x16(22)
#define Addr 0x16

int xAccl = 0, yAccl = 0;
void setup()
{
    // Set variable
    Particle.variable("i2cdevice", "MXC6226XU");
    Particle.variable("xAccl", xAccl);
    Particle.variable("yAccl", yAccl);
    
    // Initialise I2C communication as MASTER
    Wire.begin();
    // Initialise Serial Communication, set baud rate = 9600
    Serial.begin(9600);
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select detection register
    Wire.write(0x04);
    // Power up
    Wire.write(0x00);
    // Stop I2C Transmission
    Wire.endTransmission();
    delay(300);
}

void loop()
{
    unsigned int data[2];
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select data register
    Wire.write(0x00);
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Request 2 bytes of data
    Wire.requestFrom(Addr, 2);
    
    // Read 2 bytes of data
    // xAccl, yAccl
    if(Wire.available() == 2) 
    {
        data[0] = Wire.read();
        data[1] = Wire.read();
    }
    delay(300);
    
    // Convert the data
    xAccl = data[0];
    if (xAccl > 127)
    {
        xAccl -= 256;
    }
    yAccl = data[1];
    if (yAccl > 127)
    {
        yAccl -= 256;
    }
    
    // Output data to dashboard
    Particle.publish("Acceleration in X-Axis : ", String(xAccl));
    Particle.publish("Acceleration in Y-Axis : ", String(yAccl));
    delay(1000); 
}

