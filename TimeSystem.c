#include "TimeSystem.h"


/*Local Variables*/
static void incCurrentTimeMillis(void);

static TimeSystem instance = {
    .incCurrentTimeMillis = incCurrentTimeMillis,
    .currentTimeMillis = 0
};


/*Interface Functions*/

TimeSystem * GetTimeSystemInstance(void) {
    return &instance;
}


static void incCurrentTimeMillis(void){
    instance.currentTimeMillis++;
}