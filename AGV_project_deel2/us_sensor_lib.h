#ifndef US_SENSOR_LIB_H_INCLUDED
#define US_SENSOR_LIB_H_INCLUDED

///DEFINITIES ///
#define TIMEOUT     10000
#define TICKFACTOR  0.008575
#define OVERFLOW    40000

/// FUNCTIES ///
uint16_t ultrasoonAfstand_R(void);
uint16_t ultrasoonAfstand_L(void);

#endif // US_SENSOR_LIB_H_INCLUDED
