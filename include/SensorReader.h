#ifndef SENSOR_READER_H
#define SENSOR_READER_H

typedef struct {
    int speed;
    int distance;
    int temperature;
} SensorData;

SensorData SensorReader_ReadSensor(void);

#endif
