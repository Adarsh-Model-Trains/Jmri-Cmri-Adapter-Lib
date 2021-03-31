/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/
#ifndef CmriJmriAdapter_h
#define CmriJmriAdapter_h

#include <Arduino.h>
#include "CMRI.h"
#include "CtSensor.h"
#include "Pca9685Board.h"

class CmriJmriAdapter {


  private:

    int _jmriSignalStartAddress;
    int _signalCount;
    int _jmriTurnoutStartAddress;
    int _turnoutCount;
    int _jmriLightStartAddress;
    int _lightCount;
    int _jmriSensorsStartAddress;
    int _sensorsCount;
    CMRI * _cmri;
    CtSensor ctSensor;
    Pca9685Board pca9685Board;

  public:

    CmriJmriAdapter() {
      _jmriSignalStartAddress = -1;
      _signalCount = 0;
      _jmriTurnoutStartAddress = -1;
      _turnoutCount = 0;
      _jmriLightStartAddress = -1;
      _lightCount = 0;
      _jmriSensorsStartAddress = -1;
      _sensorsCount = 0;
    }

    void initCmriJmriAdapter(int cmriAddresss = 0,
                             int inputs = 24,
                             int outputs = 48,
                             int cmriBoadRate = 9600);

    void activateCmriTurnout(int jmriTurnoutStartAddress, int turnoutCount = 0);

    void setTurnoutRange(int turnoutNo, int openRange, int closeRange);


    void activateCmriSignal(int jmriSignalStartAddress, int signalCount = 0);


    void activateCmriLight(int jmriLightStartAddress, int lightCount = 0);

    void activateCmriSensors(int jmriSensorsStartAddress, int sensorsCount = 0);

    void setCtSensorPin(int sensorNo, int pinNo);

    void processJmri();

    ~CmriJmriAdapter() {
    }
};

#endif
