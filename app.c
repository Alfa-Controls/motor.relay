#include "app.h"
#include "TimeSystem.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/adc.h"
#include "mcc_generated_files/pin_manager.h"

#define L_TEMPORIZED 300
#define L_INSTAT 800
#define ACTUATOR_TIME 400

typedef enum {
    NOT_INIT,
    MONITOR,
    TEMPORIZ,
    START_PULSE,
    WAITING_PULSE,
} States;

static States state = NOT_INIT;
TimeSystem * timer;
unsigned long long cronometer;

uint16_t adcResult;

static void adc_read() {
    adcResult = (uint16_t) ADC_GetConversionResult();
    ADC_StartConversion();
}

void tasks() {

    switch (state) {
        case NOT_INIT:
            timer = GetTimeSystemInstance();
            TMR1_SetInterruptHandler(timer->incCurrentTimeMillis);
            ADC_StartConversion();
            ADC_SetInterruptHandler(adc_read);
            state = MONITOR;
            break;
        case MONITOR:
            if (adcResult > L_INSTAT) {
                state = START_PULSE;
                break;
            }
            if (adcResult > L_TEMPORIZED) {
                cronometer = timer->currentTimeMillis;
                state = TEMPORIZ;
            }

            break;
        case TEMPORIZ:
            if (timer->currentTimeMillis - cronometer > ACTUATOR_TIME)
                state = START_PULSE;
            else if (adcResult < L_TEMPORIZED)
                state = MONITOR;
            if (adcResult > L_INSTAT) {
                state = START_PULSE;
                break;
            }
            break;
        case START_PULSE:
            cronometer = timer->currentTimeMillis;
            RELAY_SetHigh();
            state = WAITING_PULSE;
            break;
        case WAITING_PULSE:
            if (timer->currentTimeMillis - cronometer > 500) {
                RELAY_SetLow();
                state = MONITOR;
            }





    }
}
