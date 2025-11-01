#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

#include "SensorReader.h"
#include "DataProcessor.h"

void DataLogger_Init(void);
void DataLogger_Log(SensorData sensor, ProcessedData processed);
void DataLogger_Close(void);

#endif