// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// HIH6130
// This code is designed to work with the HIH6130_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Temperature?sku=HIH6130_I2CS#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main()
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, HIH6130 I2C address is 0x27(39)
	ioctl(file, I2C_SLAVE, 0x27);
	sleep(1);

	// Read 4 bytes of data
	// humidity msb, humidity lsb, temp msb, temp lsb
	char data[4] = {0};
	if(read(file, data, 4) != 4)
	{
		printf("Error : Input/Output error \n");
	}
	else
	{
		// Convert the data to 14-bits
		float humidity = ((data[0] & 0x3F) * 256 + data[1]) / 16384.0 * 100.0;
		int temp = ((data[2] * 256 + (data[3] & 0xFC)) / 4);
		float cTemp = (temp / 16384.0) * 165.0 - 40.0;
		float fTemp = cTemp * 1.8 + 32;

		// Output data to screen
		printf("Relative Humidity : %.2f RH \n", humidity);
		printf("Temperature in Celsius : %.2f C \n", cTemp);
		printf("Temperature in Fahrenheit : %.2f F \n", fTemp);
	}
}
