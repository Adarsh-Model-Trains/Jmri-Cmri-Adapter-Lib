/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/


#ifndef CustomCtSensor_h
#define CustomCtSensor_h

#include "BlockState.h"

class CustomCtSensor {

  private:
    String _blockName;
    uint8_t _blockSensorPin;
    long _sensorAverageReading;
    int _sensorSamplesCount;
    int _occupancyThreshold;
    int _unOccupancySamples;
    int _unOccupancyCount;
    int _sensorReadingTempVal;
    int _sensorTotalReading;
    int _index;

    BLOCK_STATES _stateCurrent = UNOCCUPIED;
    void init();

    void calculateBlockOccupancy();
    void occupiedBlock();
    void unOccupiedBlock();

  public:
    CustomCtSensor() {
      init();
    }
    void setName(String blockName);
    void setBlockSensorPin(uint8_t blockSensorPin);
    void setOccupancyThreshhold(int occupancyThreshold);
    void setUnOccupancySamples(int unOccupancySamples);
    bool isBlockOccupied();

    ~CustomCtSensor() {

    }
};

#endif
