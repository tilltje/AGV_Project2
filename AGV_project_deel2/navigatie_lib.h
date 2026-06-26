#ifndef NAVIGATIE_LIB_H_INCLUDED
#define NAVIGATIE_LIB_H_INCLUDED

/// DEFINITIES ///
#define HALF_PAD        15.00
#define FACTOR_KEREN    0.8 //0.464285714286
#define VERWEG          30

/// FUNCTIES ///

float percentageSteering_R(int temp);
float percentageSteering_L(int temp);
void padNavigeren(int kant);
void keren(int richting);
void kerenR(void);
void timer_ms(int aantal);
void timer_s(int aantal);

#endif // NAVIGATIE_LIB_H_INCLUDED
