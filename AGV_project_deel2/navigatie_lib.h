#ifndef NAVIGATIE_LIB_H_INCLUDED
#define NAVIGATIE_LIB_H_INCLUDED

/// INCLUDES ///
#include <avr/io.h>
#include <util/delay.h>
#include "init.h"
#include "us_sensor_lib.h"
#include "motor_lib.h"


/// DEFINES ///
#define HALF_PAD        15.00
#define FACTOR_KEREN    0.8 //0.464285714286
#define VERWEG          30

/// FUNCTIONS ///
float percentageSteering_R(int temp);
float percentageSteering_L(int temp);
void padNavigerenNorm(void);
void padNavigerenLinks(void);
void padNavigerenRechts(void);
void keren(int richting);
void kerenLKlein(void);
void kerenLGroot(void);
void kerenR(void);


#endif // NAVIGATIE_LIB_H_INCLUDED
