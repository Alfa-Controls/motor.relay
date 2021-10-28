/**
 * \mainpage Motor Relay
 * Author: Cesar Daltoe Berci
 *<br>
 * Created on October 20, 2021, 10:00 PM
 * Last Review: October 28, 2021, 09:00 AM
 * 
 * \section intro_sec Introduction
 * 
 * This project is motor protection system. It will read some sensors and 
 * create trip signals to stop the motor, based on two different protection 
 * regions: instantaneous and Temporized.
 * 
 * \section Methodology
 * 
 * The project uses the MCC to create the first hardware access layer. This 
 * layer is isolated from the rest of the project by the application control
 * (app.h/app.c files).<br>
 * In the application control, the hardware layer are used to provide data to 
 * the abstraction and business layers. In this approach only the app.c file has
 * access to hardware and business, keeping all project encapsulated with
 * well defined responsibilities for every file.
 * 
 * \section Application Modules:
 * 
 * \subsection app
 * 
 * The application controller.
 * 
 * \subsection TimeSystem
 * 
 * The time control system, resposible to maintain the current time milliseconds
 * variable.
 * 
 * \subsection Sensor
 * 
 * Sensor controllers. This module have its own state machine to verify the 
 * protection regions and generate trip signal, if necessary. <br>
 * This module have a dependency to the Time System.
 * 
 * \subsection ADCReader
 * 
 * This is a abstraction layer to ADC conversion. It will read continously the
 * adc configurated channels, maintaining the read result variables updated.
 * 
 */

#ifndef APP_H
#define	APP_H

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * @brief
     * Main system tasks
     * @details
     * It should be called frequently in the main system loop, to maintain the
     * application state machine.
     */
    void tasks(void);

#ifdef	__cplusplus
}
#endif

#endif	/* APP_H */

