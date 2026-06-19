#ifndef MOTOR_LIB_H_INCLUDED
#define MOTOR_LIB_H_INCLUDED

/// INCLUDES ///
#include <avr/io.h>
#include <util/delay.h>
#include "init.h"
#include "us_sensor_lib.h"

/// DEFINES ///
#define TOP_VALUE                   40000UL
#define RESET_VALUE_TIMER1          59286UL

#define PWM TOP_VALUE*0.5

/// FUNCTIONS ///
void motor_R(float factor);
void motor_L(float factor);
void motor_config(int mode, int kant);

enum richting {RECHTS, LINKS};
enum motor_actie {VOORUIT, ACHTERUIT, REMMEN};


#endif // MOTOR_LIB_H_INCLUDED
