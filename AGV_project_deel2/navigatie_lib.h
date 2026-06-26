#ifndef NAVIGATIE_LIB_H_INCLUDED
#define NAVIGATIE_LIB_H_INCLUDED

/// DEFINITIES ///
#define HALF_PAD        15.00
#define VERWEG          30

/// FUNCTIES ///

float percentageSteering_R(int temp);
float percentageSteering_L(int temp);
void padNavigeren(int kant);
void kerenR(void);
void timer_ms(int aantal);
void timer_s(int aantal);

#endif // NAVIGATIE_LIB_H_INCLUDED
