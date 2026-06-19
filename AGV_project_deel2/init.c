#include "init.h"

void init_us_sensor(void){
    //ULTRASOON Echo als INPUT configureren
    US_ECHO_R_VOOR_DDR &= ~(1 << US_ECHO_R_VOOR);
    US_ECHO_L_VOOR_DDR &= ~(1 << US_ECHO_L_VOOR);
    US_ECHO_R_ACHTER_DDR &= ~(1 << US_ECHO_R_ACHTER);
    US_ECHO_L_ACHTER_DDR &= ~(1 << US_ECHO_L_ACHTER);

    //ULTRASOON Trigger als OUTPUT configureren
    US_TRIG_R_VOOR_DDR |= (1 << US_TRIG_R_VOOR);
    US_TRIG_L_VOOR_DDR |= (1 << US_TRIG_L_VOOR);
    US_TRIG_R_ACHTER_DDR |= (1 << US_TRIG_R_ACHTER);
    US_TRIG_L_ACHTER_DDR |= (1 << US_TRIG_L_ACHTER);

    //ULTRASOON Echo laagzetten
    US_TRIG_R_VOOR_PORT &= ~(1 << US_ECHO_R_VOOR);
    US_TRIG_L_VOOR_PORT &= ~(1 << US_ECHO_L_VOOR);
    US_TRIG_R_ACHTER_PORT &= ~(1 << US_ECHO_R_ACHTER);
    US_TRIG_L_ACHTER_PORT &= ~(1 << US_ECHO_L_ACHTER);
}

void init_h_brug_dual(void){
    //PWM als output configureren
    PWM_R_DDR |= (1 << PWM_R);
    PWM_L_DDR |= (1 << PWM_L);

    //PWM laagzetten
    PWM_R_PORT &= ~(1 << PWM_R);
    PWM_L_PORT &= ~(1 << PWM_L);

    //IN als output
    PWM_IN_1_DDR |= (1 << PWM_IN_1); // IN 1 --> motor A = rechts
    PWM_IN_2_DDR |= (1 << PWM_IN_2); // IN 2 --> motor A = rechts
    PWM_IN_3_DDR |= (1 << PWM_IN_3); // IN 3 --> motor B = links
    PWM_IN_4_DDR |= (1 << PWM_IN_4); // IN 4 --> motor B = links

    //IN laagzetten
    PWM_IN_1_PORT &= ~(1 << PWM_IN_1); // IN 1 --> motor A = rechts
    PWM_IN_2_PORT &= ~(1 << PWM_IN_2); // IN 2 --> motor A = rechts
    PWM_IN_3_PORT &= ~(1 << PWM_IN_3); // IN 3 --> motor B = links
    PWM_IN_4_PORT &= ~(1 << PWM_IN_4); // IN 4 --> motor B = links
}

void init_communicatie(void){
    // MODULE (INPUT)
    MODNUMMER_DDR &= ~(1 << MODNUMMER);
    NEXT_MOD_DDR &= ~(1 << NEXT_MOD);
    ACK_MOD_DDR &= ~(1 << ACK_MOD);

    // AGV (OUTPUT)
    NEXT_AGV_DDR |= (1 << NEXT_AGV);
    ACK_AGV_DDR |= (1 << ACK_AGV);
    LIJN_DDR |= (1 << LIJN);

    // Laagzetten
    NEXT_AGV_PORT &= ~(1 << NEXT_AGV);
    ACK_AGV_PORT &= ~(1 << ACK_AGV);
    LIJN_PORT &= ~(1 << LIJN);

    // PULL-UP AAN
    MODNUMMER_PORT &= ~(1 << MODNUMMER);
    NEXT_MOD_PORT &= ~(1 << MODNUMMER);
    ACK_MOD_PORT &= ~(1 << ACK_MOD);
}


void init(void){
    init_us_sensor();
    init_h_brug_dual();
    init_communicatie();
}
