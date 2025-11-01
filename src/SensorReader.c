#include "SensorReader.h"
#include <stdlib.h>
#include <time.h>

SensorData SensorReader_ReadSensor(void) {
    SensorData data;
    data.speed = rand() % 200;          // km/h
    data.distance = rand() % 100;       // meters
    data.temperature = 20 + rand() % 15; // °C
    return data;
}
