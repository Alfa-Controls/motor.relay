/**
 * File:   ADCReader.h
 * Author: Cesar Daltoe Berci
 *
 * Created on October 28, 2021, 6:49 AM
 * Version 1.0
 * Last review on October 28, 2021, 08:37 AM
 * 
 * @brief
 * ADC Interface
 * 
 * @details
 * This is the ADC abstraction and interfacing file. It will provide a structure
 * and methods to handle with the adc hardware using continuous acquisition.
 */

#ifndef ADCREADER_H
#define	ADCREADER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>

    /**
     * Analog driver state definition
     */
    typedef enum {
        ADC_READING_TEMP, /*!< Reading temperature sensor */
        ADC_READING_CURRENT, /*!< Reading current sensor */
    }ADCState;

    /**
     *@brief
     *  ADC Reader structure
     * @details
     * This structure defines the properties and functions used to read the adc
     * driver. It was implemented to read two variables: Temperature and Sensor.
     * All parameters are adjustable, including the analog channels and driver
     * functions.
     * The ADC Reader is a singleton object and should be created only once by
     * the GetADCReaderInstance function.
     */
    typedef struct {
        uint16_t temperature; /*!< Raw temperature value */
        uint16_t current; /*!< Raw current value */
        /**
         * @brief
         * ADC Read Function
         * @details
         * This is a callback function for the adc driver interrupt. It will
         * read the current conversion value, set a new conversion channel and
         * start a new conversion.
         * The process starts a new conversion immediately after read the 
         * driver, than it is a continuous acquisition  process with the faster 
         * acquisition  frequency possible for the device.
         */
        void (*read)(void); 
        /**
         * @brief
         * Init function
         * @details
         * This function should be called once, after ADC Reader configuration.
         * It will start the continuous  acquisition process.
         */
        void (*init)(void);
        ADCState state; /*!< ADC State */
        /**
         * @brief
         * Interface function: getResult
         * @details
         * This function is the adc get result function, and is configurated 
         * on GetADCReaderInstance.
         */
        uint16_t (*getResult)(void); 
        /**
         * @brief
         * Interface function: setChannel
         * @details
         * This function is the adc set channel function, and is configurated 
         * on GetADCReaderInstance.
         */
        void (*setChannel)(uint8_t channel);
        /**
         * @brief
         * Interface function: startConversion
         * @details
         * This function is the adc start conversion function, and is 
         * configurated on GetADCReaderInstance.
         */
        void (*startConversion)(void);
        uint8_t tempChannel; /*!< ADC Temperature Channel */
        uint8_t ampChannel; /*!< ADC Current Channel */
    }ADCReader;

    /**
     * @brief
     * Get the adc reader unique instance
     * @details
     * This method is part of the implementation of a Singleton like pattern.<br>
     * Should be only one instance of the ADC reader on the project, created
     * with this function.<br>
     * The ADC Read object is a abstraction used to interface the main program
     * with the hardware routines used to access the adc driver.
     * @param getResult Hardware function to read ADC conversion result
     * @param setChannel Hardware function to set ADC conversion channel
     * @param start Hardware function to start ADC conversion
     * @param teC ADC channel to read temperature
     * @param amC ADC channel to read current
     * @return ADC Reader object
     */
    ADCReader * GetADCReaderInstance(uint16_t (*getResult)(void), void (*setChannel)(uint8_t channel),  void (*start)(void), uint8_t teC, uint8_t amC);
    

#ifdef	__cplusplus
}
#endif

#endif	/* ADCREADER_H */

