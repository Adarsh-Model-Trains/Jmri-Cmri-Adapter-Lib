/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/

#ifndef DiyCtSensor_h
#define DiyCtSensor_h

#include "CustomCtSensor.h"

class DiyCtSensor {

  private:
    int _totalSensor;
    CustomCtSensor * _ctSensorBlocks;

  public:
    DiyCtSensor() {
    }

    void initBlockSensors(int totalSensor);
    void setBlockSensorPins(int blockNo, uint8_t ctSensorPin);
    void setBlockSensorName(int blockNo, String blockName);
    void setDiyOccupancyThreshhold(int blockNo, int occupancyThreshold);
    void setDiyUnOccupancySamples(int blockNo, int unOccupancySamples);
    bool isSensorBlockOccupied(int blockNo);

    ~DiyCtSensor() {
      for (int i = 0; i < _totalSensor; i++) {
        delete &_ctSensorBlocks[i];
      }
      delete[] _ctSensorBlocks;
    }
};
#endif
