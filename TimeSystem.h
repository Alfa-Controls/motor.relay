/* 
 * File:   TimeSystem.h
 * Author: cesar
 *
 * Created on October 20, 2021, 9:50 PM
 */

#ifndef TIMESYSTEM_H
#define	TIMESYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * Time System structure definitions
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
     * @brief
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

