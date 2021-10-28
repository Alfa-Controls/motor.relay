/** 
 * File:   Sensor.c
 * Author: Cesar Daltoe Berci
 *
 * Created on October 27, 2021, 9:57 PM
 * Version 1.0
 * Last Review: October 28, 2021, 8:57 AM
 * 
 * @details
 * Sensor control implementation
 */
#include "Sensor.h"

#include "TimeSystem.h"

static TimeSystem * timer;

void sensorTasks(Sensor * this, uint16_t meassure) {
    switch (this->state) {
        case MONITORING:
            if (meassure > this->triggerInst) {
                this->state = TRIP;
                this->trip = true;
                break;
            } else if (meassure > this->triggerTemp) {
                this->state = TEMPORIZED;
                this->cronometer = timer->currentTimeMillis;
                break;
            }
            break;
        case TEMPORIZED:
            if ((timer->currentTimeMillis - this->cronometer) > this->timeLimit) {
                this->state = TRIP;
                this->trip = true;
            } else if (meassure < this->triggerTemp) {
                this->trip = false;
                this->state = MONITORING;
            }
        case TRIP:
            if (meassure < this->triggerTemp) {
                this->trip = false;
                this->state = MONITORING;
            }
    }
}

Sensor NewSensor(uint16_t ti, uint16_t tt, uint16_t tl) {
    timer = GetTimeSystemInstance();
    Sensor ss = {
        .timeLimit = tl,
        .triggerInst = ti,
        .triggerTemp = tt,
        .tasks = sensorTasks,
        .trip = false,
        .state = MONITORING
    };
    return ss;
}
