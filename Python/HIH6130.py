# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# HIH6130
# This code is designed to work with the HIH6130_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Temperature?sku=HIH6130_I2CS#tabs-0-product_tabset-2

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

bus.write_quick(0x27)
time.sleep(0.1)

# HIH6130 address, 0x27(39)
# Read data back from 0x00(00), 4 bytes
# humidity MSB, humidity LSB, temp MSB, temp LSB
data = bus.read_i2c_block_data(0x27, 0x00, 4)

# Convert the data to 14-bits
humidity = ((((data[0] & 0x3F) * 256) + data[1]) * 100.0) / 16383.0
temp = (((data[2] & 0xFF) * 256) + (data[3] & 0xFC)) / 4
cTemp = (temp / 16384.0) * 165.0 - 40.0
fTemp = cTemp * 1.8 + 32

# Output data to screen
print "Relative Humidity : %.2f %%" %humidity
print "Temperature in Celsius : %.2f C" %cTemp
print "Temperature in Fahrenheit : %.2f F" %fTemp
