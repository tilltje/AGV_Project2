#ifndef US_SENSOR_LIB_H_INCLUDED
#define US_SENSOR_LIB_H_INCLUDED
/// INCLUDES ///
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "init.h"

/// DEFINES ///
#define TIMEOUT     10000
#define TICKFACTOR  0.008575
#define OVERFLOW    40000

/// FUNCTIONS ///
uint16_t ultrasoonAfstand_R_VOORUIT(void);
uint16_t ultrasoonAfstand_L_VOORUIT(void);
uint16_t ultrasoonAfstand_R_ACHTERUIT(void);
uint16_t ultrasoonAfstand_L_ACHTERUIT(void);

#endif // US_SENSOR_LIB_H_INCLUDED
