/**
 * File:   TimeSystem.h
 * Author: Cesar Daltoe Berci
 *
 * Created on October 20, 2021, 9:50 PM
 * Last Review: October 20, 2021, 9:50 PM
 * 
 * @details
 * Basic time handler utility.<br>
 * This file provide a time counter method using a current time milliseconds
 * variable, that should be updated by a hardware timer.
 */

#ifndef TIMESYSTEM_H
#define	TIMESYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * @brief
     * Time System structure definitions
     * @detail
     * This structure defines the properties and behaviors of the
     * time control system.
     * It also provides a variable with the current time in milliseconds
     */
    typedef struct {
        /**
         * Current System Time in milliseconds.
         * This variable has read only purpose, the user
         * should never write in currentTimeMillis.
         */
        unsigned long long currentTimeMillis;
        /**
         * Function to update the internal time counter.
         */
        void (*incCurrentTimeMillis)(void);
    }TimeSystem;

    /**
     * @summary
     * Getter for TimeSystem instance
     * @details
     * Time System has only one instance that can be
     * get through this method.
     * 
     * @return instance
     * @param void
     * @code
     * TimeSystem* timer = GetTimeSystemInstance();
     */
    TimeSystem * GetTimeSystemInstance(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMESYSTEM_H */

