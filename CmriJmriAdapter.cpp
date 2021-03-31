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


void CmriJmriAdapter::activateCmriSensors(int jmriSensorsStartAddress, int sensorsCount) {
  _jmriSensorsStartAddress = jmriSensorsStartAddress;
  if (_sensorsCount > 0) {
    _sensorsCount = sensorsCount;
    ctSensor.initCtSensor(sensorsCount);
  }
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

  if (_sensorsCount != 0) {
    for (int i = _jmriSensorsStartAddress; i < _sensorsCount; i++) {
      _cmri->set_bit(i, ctSensor.isSensorActive(i));
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
