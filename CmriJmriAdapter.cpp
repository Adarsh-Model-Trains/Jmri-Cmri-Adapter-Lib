/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/

#include "Auto485.h"
#include "CmriJmriAdapter.h"

#define  DE_PIN 2
Auto485 bus(DE_PIN);

void CmriJmriAdapter::initCmriJmriAdapter(int cmriAddresss,
    int inputs, int outputs, int cmriBoadRate) {
  bus.begin(cmriBoadRate, SERIAL_8N2); // open RS485 bus at 9600bps
  CMRI cmri(cmriAddresss, inputs, outputs, bus);
  _cmri = &cmri;
  int NO_OF_SERVO_BOARDS = _turnoutCount / 8;
  int NO_OF_LIGHT_BOARDS = (_signalCount + _lightCount) / 8;
  pca9685Board.initPca9685Boards(NO_OF_SERVO_BOARDS, NO_OF_LIGHT_BOARDS);
  Serial.begin(115200);
}

void CmriJmriAdapter::activateCmriSignal(int jmriSignalStartAddress, int signalCount) {
  _jmriSignalStartAddress = jmriSignalStartAddress;
  _signalCount = signalCount;
}

void CmriJmriAdapter::activateCmriTurnout(int jmriTurnoutStartAddress, int turnoutCount) {
  _jmriTurnoutStartAddress = jmriTurnoutStartAddress;
  _turnoutCount = turnoutCount;
}

void CmriJmriAdapter:: setTurnoutRange(int turnoutNo, int openRange, int closeRange) {
  pca9685Board.setSwitchRange(turnoutNo, openRange, closeRange);
}


void CmriJmriAdapter::activateCmriLight(int lightStartAddress, int lightCount) {
  _jmriLightStartAddress = lightStartAddress;
  _lightCount = lightCount;
}


void CmriJmriAdapter::activateCmriCtSensors(int jmriCtSensorsStartAddress, int ctSensorsCount) {
  _jmriCtSensorsStartAddress = jmriCtSensorsStartAddress;
  if (ctSensorsCount > 0) {
    _ctSensorsCount = ctSensorsCount;
    ctSensor.initCtSensor(_ctSensorsCount);
  }
}


void CmriJmriAdapter::activateCmriIrSensors(int jmriIrSensorsStartAddress, int irSensorsCount) {
  _jmriIrSensorsStartAddress = jmriIrSensorsStartAddress;
  if (irSensorsCount > 0) {
    _irSensorsCount = irSensorsCount;
    irSensors.initBlockSensors(irSensorsCount);
  }
}

void CmriJmriAdapter::setIrSensorPin(int sensorNo, int pinNo) {
}

void CmriJmriAdapter::activateCmriDiyCtSensors(int jmriDiyCtSensorsStartAddress, int diyCtSensorsCount = 0) {
  _jmriDiyCtSensorsStartAddress = jmriDiyCtSensorsStartAddress;
  if (diyCtSensorsCount > 0) {
    _diyCtSensorsCount = diyCtSensorsCount;
    diyCtSensor.initBlockSensors(diyCtSensorsCount);
  }
}

void CmriJmriAdapter::setDiyCtOccupancyThreshhold(int blockNo, int occupancyThreshold) {
  diyCtSensor.setDiyOccupancyThreshhold(blockNo, occupancyThreshold);
}

void CmriJmriAdapter::setDiyCtUnOccupancySamples(int blockNo, int unOccupancySamples) {
  diyCtSensor.setDiyUnOccupancySamples(blockNo, unOccupancySamples);
}

void CmriJmriAdapter::setDiyCtSensorPin(int sensorNo, uint8_t pinNo) {
  diyCtSensor.setBlockSensorPins(sensorNo, pinNo);
}

void CmriJmriAdapter::setCtSensorPin(int sensorNo, int pinNo) {
  ctSensor.setSensorPin(sensorNo, pinNo);
}


void CmriJmriAdapter::setTurnoutFrequency(int turnoutFrequency) {
  pca9685Board.setFrequencyTurnout(turnoutFrequency);
}

void CmriJmriAdapter::setLightFrequency(int frequency) {
  pca9685Board.setFrequencyLight(frequency);
}

void CmriJmriAdapter::processJmri() {
  _cmri->process();

  if (_ctSensorsCount != 0) {
    for (int i = _jmriCtSensorsStartAddress; i < _ctSensorsCount; i++) {
      _cmri->set_bit(i, ctSensor.isSensorActive(i));
    }
  }

  if (_diyCtSensorsCount != 0) {
    for (int i = _jmriDiyCtSensorsStartAddress; i < _diyCtSensorsCount; i++) {
      _cmri->set_bit(i, diyCtSensor.isSensorBlockOccupied(i));
    }
  }


  if (_signalCount != 0 ) {
    int totalJmriSignalAddress = _jmriSignalStartAddress + _signalCount;
    for (int i = _jmriSignalStartAddress; i < totalJmriSignalAddress; i++) {
      //todo conect to the respective implemenation
      int x =  _cmri->get_bit(i);
      if (x == 1) {
        pca9685Board.switchOn(i);
      } else {
        pca9685Board.switchOff(i);
      }
    }
  }

  if (_turnoutCount != 0) {
    int totalJmriTurnoutAddress = _jmriTurnoutStartAddress + _turnoutCount;
    for (int i = _jmriTurnoutStartAddress; i < totalJmriTurnoutAddress; i++) {
      //todo conect to the respective implemenation
      int x = _cmri->get_bit(i);
      if (x == 1) {
        pca9685Board.throwSwitch(i);
      } else {
        pca9685Board.closeSwitch(i);
      }
    }
  }

  if (_lightCount != 0) {
    int totalJmriLightAddress = _jmriLightStartAddress + _lightCount;
    for (int i = _jmriLightStartAddress; i < totalJmriLightAddress; i++) {
      //todo conect to the respective implemenation
      int x =  _cmri->get_bit(i);
      if (x == 1) {
        pca9685Board.switchOn(i);
      } else {
        pca9685Board.switchOff(i);
      }
    }
  }
}
