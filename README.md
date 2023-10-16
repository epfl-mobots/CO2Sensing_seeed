This file was designed in October 2023 to sense CO2 levels within the beehive obersvation modules in Bassenges.
It uses two CO2 sensors and one microcontroller, itself connected to a RPi that logs the data on the EPFL server. Two I2C buses are set up using the seeeduino's I2c pins and the UART pins converted to a I2C bus. Variant.h and variant.cpp were modified to plan for this.

Hardware involved: seeeduino XIAO M0, CO2 sensor SCD30
Libraries required: SparkFun SCD30 Arduino Library