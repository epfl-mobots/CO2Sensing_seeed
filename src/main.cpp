// Cyril Monette, October 2023

#include <Arduino.h>
#include <Wire.h> // For I2C communication
#include "SparkFun_SCD30_Arduino_Library.h"

# define USE_TWO_SENSORS // Comment this line to use only one sensor

SCD30 airSensor;
SCD30 airSensor1;

uint16_t sensingInterval = 60; // Seconds

// Function to parametrise the sensors
// Parameters: sensingInterval: the interval between measurements in seconds, between 2 and 100 seconds
void parametriseSenors(uint16_t sensingInterval){
    airSensor.setMeasurementInterval(sensingInterval); //Change number of seconds between measurements: 2 to 1800 (30 minutes), stored in non-volatile memory of SCD30
    airSensor1.setMeasurementInterval(sensingInterval); //Change number of seconds between measurements: 2 to 1800 (30 minutes), stored in non-volatile memory of SCD30

    //While the setting is recorded, it is not immediately available to be read.
    delay(200);
    int interval = airSensor.getMeasurementInterval();
    int interval1 = airSensor1.getMeasurementInterval();
    Serial.print("Measurement Intervals: ");
    Serial.println(String(interval) + "   " + String(interval1));

    //My desk is ~400m above sealevel
    airSensor.setAltitudeCompensation(400); //Set altitude of the sensor in m, stored in non-volatile memory of SCD30
    airSensor1.setAltitudeCompensation(400); //Set altitude of the sensor in m, stored in non-volatile memory of SCD30
}

void setup() {
    while(!Serial){
        delay(50);
    }
    delay(4000); // the init of this mcu is annoying, we want to see what happens.
    Serial.begin(9600);
    Serial.println("START");

    Wire.begin();
    delay(50);
    Wire1.begin(); //Start the other wire hardware that may be supported by your platform
    delay(50);
    while(!airSensor.begin(Wire)){ //Pass the Wire port to the .begin() function
        Serial.println("PROBLEM0"); 
        delay(500);
    }
    Serial.println("Will connect to SCD30 0");

    #ifdef USE_TWO_SENSORS
    while(!airSensor1.begin(Wire1)){ //Pass the Wire port to the .begin() function
        Serial.println("PROBLEM1"); 
        delay(500);
    }
    Serial.println("Will connect to SCD30 1");
    #endif

    parametriseSenors(sensingInterval); //Set the sensing interval to 60 seconds
}

void loop(){
    // Take CO2, humidity and temperature measurements every X minutes:

    if(airSensor.dataAvailable()){
        // Sensor 0:
        String output="0, " + String(airSensor.getCO2())+",";
        output=output+String(airSensor.getTemperature())+",";
        output=output+String(airSensor.getHumidity());
        
        // Send data in the following format: sensor number, co2(ppm),temp(C),humidity(%)
        Serial.println(output);
    }
    if(airSensor1.dataAvailable()){
        // Sensor 1:
        String output="1, " + String(airSensor1.getCO2())+",";
        output=output+String(airSensor1.getTemperature())+",";
        output=output+String(airSensor1.getHumidity());
        
        // Send data in the following format: sensor number, co2(ppm),temp(C),humidity(%)
        Serial.println(output);
    }
    delay(0.75*sensingInterval*1000);
}