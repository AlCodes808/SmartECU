#ifndef RTE_H
#define RTE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SensorReader.h"
#include "DataProcessor.h"

SensorData Rte_Read_SensorData(void);
void Rte_Write_ProcessedData(ProcessedData data);

#endif