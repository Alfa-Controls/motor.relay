/**
 * File:   TimeSystem.h
 * Author: Cesar Daltoe Berci
 *
 * Created on October 20, 2021, 9:50 PM
 * Last Review: October 20, 2021, 9:50 PM
 * 
 * @details
 * Time system control implementation
 */
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