# 1 "TimeSystem.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.40/packs/Microchip/PIC12-16F1xxx_DFP/1.2.63/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "TimeSystem.c" 2
# 1 "./TimeSystem.h" 1
# 18 "./TimeSystem.h"
    typedef struct {





        unsigned long long currentTimeMillis;



        void (*incCurrentTimeMillis)(void);
    }TimeSystem;
# 43 "./TimeSystem.h"
    TimeSystem * GetTimeSystemInstance(void);
# 1 "TimeSystem.c" 2




static void incCurrentTimeMillis(void);

static TimeSystem instance = {
    .incCurrentTimeMillis = incCurrentTimeMillis,
    .currentTimeMillis = 0
};




TimeSystem * GetTimeSystemInstance(void) {
    return &instance;
}


static void incCurrentTimeMillis(void){
    instance.currentTimeMillis++;
}
