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
#include "DiyCtSensor.h"
#include "IrBlockSensors.h"

class CmriJmriAdapter {


  private:

    int _jmriSignalStartAddress;
    int _signalCount;
    int _jmriTurnoutStartAddress;
    int _turnoutCount;
    int _jmriLightStartAddress;
    int _lightCount;
    int _jmriCtSensorsStartAddress;
    int _ctSensorsCount;
    int _jmriDiyCtSensorsStartAddress;
    int _diyCtSensorsCount;
    int _jmriIrSensorsStartAddress;
    int _irSensorsCount;
    CMRI * _cmri;
    CtSensor ctSensor;
    DiyCtSensor diyCtSensor;
    IrBlockSensors irSensors;
    Pca9685Board pca9685Board;

  public:

    CmriJmriAdapter() {
      _jmriSignalStartAddress = -1;
      _signalCount = 0;
      _jmriTurnoutStartAddress = -1;
      _turnoutCount = 0;
      _jmriLightStartAddress = -1;
      _lightCount = 0;
      _jmriCtSensorsStartAddress = -1;
      _ctSensorsCount = 0;
      _jmriDiyCtSensorsStartAddress = -1;
      _diyCtSensorsCount = 0;
      _jmriIrSensorsStartAddress = -1;
      _irSensorsCount = 0;
    }

    void initCmriJmriAdapter(int cmriAddresss = 0,
                             int inputs = 24,
                             int outputs = 48,
                             int cmriBoadRate = 9600);

    void activateCmriTurnout(int jmriTurnoutStartAddress, int turnoutCount = 0);

    void setTurnoutRange(int turnoutNo, int openRange, int closeRange);

    void setTurnoutFrequency(int turnoutFrequency);

    void setLightFrequency(int frequency);

    void activateCmriSignal(int jmriSignalStartAddress, int signalCount = 0);

    void activateCmriLight(int jmriLightStartAddress, int lightCount = 0);

    void activateCmriCtSensors(int jmriCtSensorsStartAddress, int ctSensorsCount = 0);

    void setCtSensorPin(int sensorNo, int pinNo);

    void activateCmriIrSensors(int jmriIrSensorsStartAddress, int irSensorsCount = 0);

    void setIrSensorPin(int sensorNo, int pinNo);

    void activateCmriDiyCtSensors(int jmriDiyCtSensorsStartAddress, int diyCtSensorsCount = 0);

    void setDiyCtSensorPin(int sensorNo, uint8_t pinNo);

    void setDiyCtOccupancyThreshhold(int blockNo, int occupancyThreshold);

    void setDiyCtUnOccupancySamples(int blockNo, int unOccupancySamples);

    void processJmri();

    ~CmriJmriAdapter() {
    }
};

#endif
