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
#define WRITE           1
#define READ            0
#define RESET           2

/// FUNCTIONS ///
float percentageSteering_R(int temp);
float percentageSteering_L(int temp);
void padNavigerenNorm(void);
void padNavigerenLinks(void);
void padNavigerenRechts(void);
int lijnInterrupt(int action);
void kerenR(void);


#endif // NAVIGATIE_LIB_H_INCLUDED
