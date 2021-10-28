/**
 * File:   ADCReader.c
 * Author: Cesar Daltoe Berci
 *
 * Created on October 28, 2021, 6:49 AM
 * Version 1.0
 * Last review on October 28, 2021, 08:37 AM
 * 
 * @brief
 * Implementation of ADC Reader 
 */
#include "ADCReader.h"
#include "mcc_generated_files/adc.h"

static void read(void);
static void init(void);

static ADCReader self = {
    .read = read,
    .init = init,
};

ADCReader * GetADCReaderInstance(uint16_t(*getResult)(void), void (*setChannel)(uint8_t channel), void (*start)(void), uint8_t teC, uint8_t amC) {
    self.ampChannel = amC;
    self.tempChannel = teC;
    self.setChannel = setChannel;
    self.getResult = getResult;
    return &self;
}

static void read(void) {
    switch (self.state) {
        case ADC_READING_TEMP:
            self.temperature = self.getResult();
            self.setChannel(self.ampChannel);
            self.state = ADC_READING_CURRENT;
            break;
        case ADC_READING_CURRENT:
            self.current = self.getResult();
            self.setChannel(self.tempChannel);
            self.state = ADC_READING_TEMP;
            break;
    }
    self.startConversion();
}

static void init(void) {
    self.setChannel(self.tempChannel);
    self.state = ADC_READING_TEMP;
    self.startConversion();
}