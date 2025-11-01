#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include "Rte.h"
#include "DataLogger.h"

// ANSI color codes
#define COLOR_GREEN  "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_RED    "\033[0;31m"
#define COLOR_CYAN   "\033[0;36m"
#define COLOR_RESET  "\033[0m"

volatile sig_atomic_t keep_running = 1;

// Statistics tracking
typedef struct {
    int total_readings;
    int total_alerts;
    int speed_max;
    int speed_min;
    long speed_sum;
    int temp_max;
    int temp_min;
    long temp_sum;
    int dist_min;
} Statistics;

Statistics stats = {0, 0, 0, 200, 0, 0, 100, 0, 100};

void signal_handler(int sig) {
    (void)sig;
    keep_running = 0;
}

void update_statistics(SensorData sensor, ProcessedData processed) {
    stats.total_readings++;
    
    if (processed.alert != ALERT_NONE) {
        stats.total_alerts++;
    }
    
    // Speed stats
    if (sensor.speed > stats.speed_max) stats.speed_max = sensor.speed;
    if (sensor.speed < stats.speed_min) stats.speed_min = sensor.speed;
    stats.speed_sum += sensor.speed;
    
    // Temperature stats
    if (sensor.temperature > stats.temp_max) stats.temp_max = sensor.temperature;
    if (sensor.temperature < stats.temp_min) stats.temp_min = sensor.temperature;
    stats.temp_sum += sensor.temperature;
    
    // Distance stats
    if (sensor.distance < stats.dist_min) stats.dist_min = sensor.distance;
}

void print_statistics(void) {
    if (stats.total_readings == 0) return;
    
    int avg_speed = (int)(stats.speed_sum / stats.total_readings);
    int avg_temp = (int)(stats.temp_sum / stats.total_readings);
    float alert_rate = (stats.total_alerts * 100.0f) / stats.total_readings;
    
    printf("\n%s========================================", COLOR_CYAN);
    printf("\n           SESSION STATISTICS           ");
    printf("\n========================================%s\n", COLOR_RESET);
    printf("Total Readings:  %d\n", stats.total_readings);
    printf("Total Alerts:    %d (%.1f%%)\n", stats.total_alerts, alert_rate);
    printf("\nSpeed:  Min=%d  Max=%d  Avg=%d km/h\n", 
           stats.speed_min, stats.speed_max, avg_speed);
    printf("Temp:   Min=%d  Max=%d  Avg=%d C\n", 
           stats.temp_min, stats.temp_max, avg_temp);
    printf("Closest Distance: %d m\n", stats.dist_min);
    printf("%s========================================%s\n\n", COLOR_CYAN, COLOR_RESET);
}

SensorData Rte_Read_SensorData(void) {
    return SensorReader_ReadSensor();
}

void Rte_Write_ProcessedData(ProcessedData data) {
    if (data.alert == ALERT_NONE) {
        printf("%s[OK] Status: NORMAL%s\n", COLOR_GREEN, COLOR_RESET);
    } else {
        int alert_count = 0;
        if (data.alert & ALERT_HIGH_SPEED) alert_count++;
        if (data.alert & ALERT_COLLISION_RISK) alert_count++;
        if (data.alert & ALERT_OVERHEATING) alert_count++;
        if (data.alert & ALERT_DANGER_COMBO) alert_count++;
        
        const char* color = (alert_count >= 3 || (data.alert & ALERT_DANGER_COMBO)) 
                            ? COLOR_RED : COLOR_YELLOW;
        const char* severity = (alert_count >= 3 || (data.alert & ALERT_DANGER_COMBO)) 
                               ? "[!!!] " : "[!] ";
        
        printf("%s%sALERTS: ", color, severity);
        
        if (data.alert & ALERT_HIGH_SPEED) {
            printf("[HIGH SPEED] ");
        }
        if (data.alert & ALERT_COLLISION_RISK) {
            printf("[COLLISION RISK] ");
        }
        if (data.alert & ALERT_OVERHEATING) {
            printf("[OVERHEATING] ");
        }
        if (data.alert & ALERT_DANGER_COMBO) {
            printf("[*** CRITICAL DANGER ***] ");
        }
        printf("%s\n", COLOR_RESET);
    }
}

int main(void) {
    srand((unsigned int)time(NULL));
    signal(SIGINT, signal_handler);
    
    DataLogger_Init();
    
    printf("\n========================================\n");
    printf("   AUTOSAR Vehicle Safety Monitor\n");
    printf("========================================\n");
    printf("Logging to: vehicle_data_log.csv\n");
    printf("Press Ctrl+C to stop...\n\n");

    while (keep_running) {
        SensorData sensor = Rte_Read_SensorData();
        ProcessedData pd = DataProcessor_Process(sensor);
        
        update_statistics(sensor, pd);
        DataLogger_Log(sensor, pd);
        
        printf("Speed:%3d km/h  Dist:%3d m  Temp:%2d C  -->  ",
               sensor.speed, sensor.distance, sensor.temperature);
        Rte_Write_ProcessedData(pd);
        
        sleep(1);
    }
    
    printf("\nShutting down...\n");
    DataLogger_Close();
    print_statistics();
    printf("Data logged to vehicle_data_log.csv\n");
    
    return 0;
}
