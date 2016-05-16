// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// HIH6130
// This code is designed to work with the HIH6130_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Temperature?sku=HIH6130_I2CS#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class HIH6130
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus Bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, HIH6130 I2C address is 0x27(39)
		I2CDevice device = Bus.getDevice(0x27);
		Thread.sleep(500);

		// Read 4 bytes of data
		// humidity msb, humidity lsb, temp msb, temp lsb
		byte[] data = new byte[4];
		device.read(0x00, data, 0, 4);

		// Convert the data to 14-bits
		double humidity = (((data[0] & 0x3F) * 256) + (data[1] & 0xFF)) / 16384.0 * 100.0;
		int temp = ((((data[2] & 0xFF) * 256) + (data[3] & 0xFC)) / 4);
		double cTemp = (temp / 16384.0) * 165.0 - 40.0;
		double fTemp = cTemp * 1.8 + 32;

		// Output data to screen
		System.out.printf("Relative Humidity : %.2f %% RH %n", humidity);
		System.out.printf("Temperature in Celsius : %.2f C %n", cTemp);
		System.out.printf("Temperature in Farhenheit : %.2f F %n", fTemp);
	}	
}
