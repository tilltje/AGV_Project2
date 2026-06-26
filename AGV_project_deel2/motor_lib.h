#ifndef MOTOR_LIB_H_INCLUDED
#define MOTOR_LIB_H_INCLUDED

/// DEFINITIES ///
#define PWM TOP_VALUE*1

/// ENUM ///
enum richting {RECHTS, LINKS};
enum motor_actie {VOORUIT, ACHTERUIT, REMMEN};

/// FUNCTIES ///
void motor_R(float factor);
void motor_L(float factor);
void motor_config(int mode, int kant);


#endif // MOTOR_LIB_H_INCLUDED
