# 1 "Sensor.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.40/packs/Microchip/PIC12-16F1xxx_DFP/1.2.63/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "Sensor.c" 2
# 12 "Sensor.c"
# 1 "./Sensor.h" 1
# 21 "./Sensor.h"
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c99\\stdint.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c99\\musl_xc8.h" 1 3
# 4 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c99\\stdint.h" 2 3
# 22 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 127 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long uintptr_t;
# 142 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long intptr_t;
# 158 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c99\\bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef __int24 int24_t;




typedef long int32_t;





typedef long long int64_t;
# 188 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef __uint24 uint24_t;




typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 229 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 22 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c99\\stdint.h" 2 3


typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 139 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c99\\bits/stdint.h" 1 3
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 139 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c99\\stdint.h" 2 3
# 21 "./Sensor.h" 2

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c99\\stdbool.h" 1 3
# 22 "./Sensor.h" 2






    typedef enum {
        MONITORING,
        TEMPORIZED,
        TRIP,
    }SensorState;
# 48 "./Sensor.h"
    typedef struct SENSOR_TAG {
        SensorState state;
        uint16_t triggerInst;
        uint16_t triggerTemp;
        uint16_t timeLimit;
# 62 "./Sensor.h"
        void (*tasks)(struct SENSOR_TAG * this, uint16_t meassure);
        uint16_t cronometer;
        _Bool trip;
    } Sensor;
# 75 "./Sensor.h"
    Sensor NewSensor(uint16_t ti, uint16_t tt, uint16_t tl);
# 12 "Sensor.c" 2


# 1 "./TimeSystem.h" 1
# 29 "./TimeSystem.h"
    typedef struct {





        unsigned long long currentTimeMillis;



        void (*incCurrentTimeMillis)(void);
    }TimeSystem;
# 54 "./TimeSystem.h"
    TimeSystem * GetTimeSystemInstance(void);
# 14 "Sensor.c" 2


static TimeSystem * timer;

void sensorTasks(Sensor * this, uint16_t meassure) {
    switch (this->state) {
        case MONITORING:
            if (meassure > this->triggerInst) {
                this->state = TRIP;
                this->trip = 1;
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
                this->trip = 1;
            } else if (meassure < this->triggerTemp) {
                this->trip = 0;
                this->state = MONITORING;
            }
        case TRIP:
            if (meassure < this->triggerTemp) {
                this->trip = 0;
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
        .trip = 0,
        .state = MONITORING
    };
    return ss;
}
