
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/
#include "CmriJmriAdapter.h"

#define CMRI_ADDR 0
#define CMRI_INPUT 24
#define CMRI_OUTPUT 48

#define TURNOUT_START_ADDRESS 0
#define TURNOUT_COUNT 5

#define SIGNAL_START_ADDRESS 10
#define SIGNAL_COUNT 3

#define LIGHT_START_ADDRESS 15
#define LIGHT_COUNT 5

#define SENSOR_START_ADDRESS 0
#define SENSOR_COUNT 5

#define CMRI_BOADRATE 9600

CmriJmriAdapter jmriCmriAdapter;

void setup() {

  jmriCmriAdapter.activateCmriTurnout(TURNOUT_START_ADDRESS, TURNOUT_COUNT);
  jmriCmriAdapter.activateCmriSignal(SIGNAL_START_ADDRESS, SIGNAL_COUNT);
  jmriCmriAdapter.activateCmriLight(LIGHT_START_ADDRESS, LIGHT_COUNT);
  jmriCmriAdapter.activateCmriSensors(SENSOR_START_ADDRESS, SENSOR_COUNT);
  jmriCmriAdapter.setCtSensorPin(1, 13);
  jmriCmriAdapter.setCtSensorPin(2, 12);
  jmriCmriAdapter.setCtSensorPin(3, 11);
  jmriCmriAdapter.setCtSensorPin(4, 10);
  jmriCmriAdapter.setCtSensorPin(5, 9);
  jmriCmriAdapter.initCmriJmriAdapter(CMRI_ADDR, CMRI_INPUT, CMRI_OUTPUT, CMRI_BOADRATE);
}

void loop() {
  jmriCmriAdapter.processJmri();
  delay(500);
}
