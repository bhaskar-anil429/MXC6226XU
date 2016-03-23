# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# MXC6226XU
# This code is designed to work with the MXC6226XU_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Accelorometer?sku=MXC6226XU_I2CS#tabs-0-product_tabset-2

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# MXC6226XU address, 0x16(22)
# Select detection register, 0x04(04)
#		0x00(00)	Power up
bus.write_byte_data(0x16, 0x04, 0x00)

time.sleep(0.5)

# MXC6226XU address, 0x16(22)
# Read data back from 0x00(00), 2 bytes
# X-Axis, Y-Axis
data = bus.read_i2c_block_data(0x16, 0x00, 2)

# Convert the data
xAccl = data[0]
if xAccl > 127 :
	xAccl -= 256
yAccl = data[1]
if yAccl > 127 :
	yAccl -= 256

# Output data to screen
print "Acceleration in X-Axis : %d" % xAccl
print "Acceleration in Y-Axis : %d" % yAccl
