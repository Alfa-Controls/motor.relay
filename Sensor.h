/** 
 * File:   Sensor.h
 * Author: Cesar Daltoe Berci
 *
 * Created on October 27, 2021, 9:57 PM
 * Version 1.0
 * Last Review: October 27, 2021, 9:57 PM
 * 
 * @details
 * This file provides methods and variables to control sensors measures.<br>
 * The subject is to protect a electrical motor, providing instantaneous and
 * temporized protections using one or more sensors.
 */

#ifndef SENSOR_H
#define	SENSOR_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdbool.h>
    
    /**
     * @brief
     * Sensor state definition    
     */
    typedef enum {
        MONITORING, /*!< Monitoring the raw values, running in normal mode */
        TEMPORIZED, /*!< Running in temporized fault monitoring */
        TRIP, /*!< Fault trip */
    }SensorState;

    /**
     * @brief
     * Sensor structure definition
     * @details
     * It provide properties and methods to handle with physical sensors used
     * to protect a electrical motor.
     * These sensors have two protective regions: Instantaneous trip and 
     * temporized trip. In instantaneous monitoring, a trip event will be 
     * generated after a sensor raw value get higher than the trigger level. In
     * temporized monitoring, it will wait a specified time after reach the 
     * trigger level before start a trip.<br>
     * This structure methods requires TimeSystem.h to provide the 
     * currentTimeMillis.
     */
    typedef struct SENSOR_TAG {
        SensorState state; /*!< State of the sensor */
        uint16_t triggerInst;/*!< Instantaneous trigger level */
        uint16_t triggerTemp;/*!< Temporized trigger level */
        uint16_t timeLimit;/*!< Time to wait in temporized protection */
        /**
         * @brief
         * Main sensor tasks
         * @details
         * This function should be called frequently to maintain the monitoring 
         * status.
         * @param this: A pointer to this structure
         * @param meassure: The raw value of the sensor
         */
        void (*tasks)(struct SENSOR_TAG * this, uint16_t meassure);
        uint16_t cronometer;/*!< Cronometer utilized to meassure time */
        bool trip;/*!< Trip signal */
    } Sensor;

    /**
     * @details
     * Creates a new sensor object
     * @param ti: Instantaneous trigger level
     * @param tt: Temporized trigger level
     * @param tl: Time to wait in temporized protection
     * @return New sensor object
     */
    Sensor NewSensor(uint16_t ti, uint16_t tt, uint16_t tl);

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_H */

