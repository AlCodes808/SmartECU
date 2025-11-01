#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include "SensorReader.h"

// Alert bit flags
#define ALERT_NONE           0
#define ALERT_HIGH_SPEED     (1 << 0)  // bit 0: speed > 150
#define ALERT_COLLISION_RISK (1 << 1)  // bit 1: distance < 10
#define ALERT_OVERHEATING    (1 << 2)  // bit 2: temp > 35
#define ALERT_DANGER_COMBO   (1 << 3)  // bit 3: high speed + close distance

typedef struct {
    int alert;  // bit field of active alerts
} ProcessedData;

ProcessedData DataProcessor_Process(SensorData data);

#endif