#include "DataLogger.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

static FILE* log_file = NULL;

void DataLogger_Init(void) {
    log_file = fopen("vehicle_data_log.csv", "a");
    if (log_file != NULL) {
        // Check if file is empty (new file)
        fseek(log_file, 0, SEEK_END);
        if (ftell(log_file) == 0) {
            // Write header
            fprintf(log_file, "Timestamp,Speed_kmh,Distance_m,Temperature_C,Alert_Code,Alert_Description\n");
        }
        fseek(log_file, 0, SEEK_END);
    }
}

void DataLogger_Log(SensorData sensor, ProcessedData processed) {
    if (log_file == NULL) return;
    
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char timestamp[64];
    snprintf(timestamp, sizeof(timestamp), "%04d-%02d-%02d %02d:%02d:%02d",
             t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
             t->tm_hour, t->tm_min, t->tm_sec);
    
    char alert_desc[256] = "OK";
    if (processed.alert != ALERT_NONE) {
        alert_desc[0] = '\0';
        if (processed.alert & ALERT_HIGH_SPEED) {
            strcat(alert_desc, "HIGH_SPEED;");
        }
        if (processed.alert & ALERT_COLLISION_RISK) {
            strcat(alert_desc, "COLLISION_RISK;");
        }
        if (processed.alert & ALERT_OVERHEATING) {
            strcat(alert_desc, "OVERHEATING;");
        }
        if (processed.alert & ALERT_DANGER_COMBO) {
            strcat(alert_desc, "CRITICAL_DANGER;");
        }
    }
    
    fprintf(log_file, "%s,%d,%d,%d,%d,%s\n",
            timestamp, sensor.speed, sensor.distance, sensor.temperature,
            processed.alert, alert_desc);
    fflush(log_file);
}

void DataLogger_Close(void) {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
}