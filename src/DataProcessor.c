#include "DataProcessor.h"

ProcessedData DataProcessor_Process(SensorData data) {
    ProcessedData pd;
    pd.alert = ALERT_NONE;
    
    // Check high speed
    if (data.speed > 150) {
        pd.alert |= ALERT_HIGH_SPEED;
    }
    
    // Check collision risk
    if (data.distance < 10) {
        pd.alert |= ALERT_COLLISION_RISK;
    }
    
    // Check overheating
    if (data.temperature > 35) {
        pd.alert |= ALERT_OVERHEATING;
    }
    
    // Check dangerous combination
    if (data.speed > 100 && data.distance < 20) {
        pd.alert |= ALERT_DANGER_COMBO;
    }
    
    return pd;
}