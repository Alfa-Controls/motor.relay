/**
 * File:   app.h
 * Author: Cesar Daltoe Berci
 *
 * Created on October 20, 2021, 10:00 PM
 * Last Review: October 20, 2021, 10:00 PM
 * 
 * @details
 * Application control implementation.<br>
 * This file is the unique application file that has access to the hardware 
 * functions. It should be used as an interface layer, keeping all the rest of
 * the project isolated from the hardware.
 */
#include "app.h"
#include "TimeSystem.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/adc.h"
#include "mcc_generated_files/pin_manager.h"
#include "Sensor.h"
#include "ADCReader.h"

#include <stdbool.h>

/*Definitions*/
#define LIMIT_TEMP_TEMPORIZED 300 /*!< Limit for temporized temperature */
#define LIMIT_TEMP_INST 800 /*!< Limit for instantaneous temperature */
#define TEMPORIZED_TIME 400 /*< !< Time limit for temporized region [ms] */
#define PULSE_PERIOD 500 /*!< Trip pulse period */
#define DEAD_TIME 500 /*!< Time to wait after send a trip pulse */
#define LIMIT_CURRENT_INST 800 /*!< Limit for instantaneous current */
#define LIMIT_CURRENT_TEMPORIZED 600 /*!< Limit for temporized current */

/*Local definitions*/

/**
 * Main system states
 */
typedef enum {
    NOT_INIT, /*!< Not initiated */
    MONITOR, /*!< Monitoring sensors */
    START_PULSE, /*!< Starting trigger pulse */
    WAITING_PULSE, /*!< Waiting for trigger pulse */
    WAITING_DEAD_TIME, /*!< Wainting for dead time */
} States;


/*Local variables*/
static States state = NOT_INIT; /*!< Main system state */
static TimeSystem * timer; /*!< Time meassure */
static uint16_t cronometer; /*!< Variable to hold start time */
static bool isReadingTemp = true; /*!< State control for adc driver */
Sensor temperatureSensor;/*!< Temperature Sensor */
Sensor ampSensor;/*!< Current Sensor */
ADCReader * adc;/*!< ADC Reader object */

/*Interface Functions*/

/**
 * @brief
 * Main system tasks
 * @details
 * This function controls the main system state.
 * @param
 * None
 */
void tasks(void) {
    switch (state) {
        case NOT_INIT:
            timer = GetTimeSystemInstance();
            TMR1_SetInterruptHandler(timer->incCurrentTimeMillis);
            temperatureSensor = NewSensor(LIMIT_TEMP_INST, LIMIT_TEMP_TEMPORIZED, TEMPORIZED_TIME);
            ampSensor = NewSensor(LIMIT_CURRENT_INST, LIMIT_CURRENT_TEMPORIZED, TEMPORIZED_TIME);
            adc = GetADCReaderInstance((uint16_t(*)(void)) ADC_GetConversionResult,
                   (void (*)(uint8_t)) ADC_SelectChannel,
                    ADC_StartConversion, 
                    (uint8_t) TEMP, (uint8_t) CURRENT
            );
            ADC_SetInterruptHandler(adc->read);
            adc->init();
            state = MONITOR;
            break;
        case MONITOR:
            temperatureSensor.tasks(&temperatureSensor, adc->temperature);
            ampSensor.tasks(&ampSensor, adc->current);
            if (ampSensor.trip || temperatureSensor.trip)
                state = START_PULSE;
            break;
        case START_PULSE:
            cronometer = timer->currentTimeMillis;
            RELAY_SetHigh();
            state = WAITING_PULSE;
            break;
        case WAITING_PULSE:
            if ((timer->currentTimeMillis - cronometer) > PULSE_PERIOD) {
                RELAY_SetLow();
                state = WAITING_DEAD_TIME;
                cronometer = timer->currentTimeMillis;
            }
            break;
        case WAITING_DEAD_TIME:
            if ((timer->currentTimeMillis - cronometer) > DEAD_TIME) {
                RELAY_SetLow();
                state = MONITOR;
            }
            break;
    }

}
