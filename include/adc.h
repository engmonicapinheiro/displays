#ifndef __ADC_H
#define __ADC_H

#include <stdint.h>

void AdcInit(void);
void AdcStartConversion(void);
uint32_t AdcRead(void);


#endif  //ADC_H