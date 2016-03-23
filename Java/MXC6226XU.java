// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MXC6226XU
// This code is designed to work with the MXC6226XU_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=MXC6226XU_I2CS#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class MXC6226XU
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, MXC6226XU I2C address is 0x16(22)
		I2CDevice device = bus.getDevice(0x16);

		// Select detection register
		// Power up
		device.write(0x40, (byte)0x00);
		Thread.sleep(500);

		// Read 2 bytes of data
		// xAccl, yAccl
		byte[] data = new byte[2];
		device.read(0x00, data, 0, 2);

		int xAccl = data[0] & 0xFF;
		if(xAccl > 127)
		{
			xAccl -= 256;
		}

		int yAccl = data[1] & 0xFF;
		if(yAccl > 127)
		{
			yAccl -= 256;
		}

		// Output data to screen
		System.out.printf("Acceleration in X-Axis : %d", xAccl);
		System.out.printf("Acceleration in Y-Axis : %d", yAccl);
	}
}
