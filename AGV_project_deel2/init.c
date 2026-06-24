#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "communicatie_lib.h"
#include "init.h"
#include "motor_lib.h"
#include "navigatie_lib.h"
#include "rfid_module_lib.h"
#include "us_sensor_lib.h"

///deze interrupt is nieuw!
ISR(INT0_vect) { //module heeft commando geacknowledged
    NEXT_AGV_PORT &= ~(1 << NEXT_AGV);
    LIJN_PORT &= ~(1 << LIJN);
    PORTB &= ~(1 << PB7);
    _delay_ms(500);
    PORTB |= (1 << PB7);
}

ISR(INT4_vect){
    lijnInterrupt(WRITE);
}

void init_rfid_module(void) { // timer voor 2 sec stilstaan
    TCCR4B |= (1 << CS42);
    TCCR4B &= ~(1 << CS41);
    TCCR4B &= ~(1 << CS40);
}

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
void init_lijndetectieIR(void){
    //IR lijndetectie als INPUT configureren
    IR_lijdetectie_DDR &= ~(1 << IR_lijdetectie);

    //IR lijndetectie pull-up aanzetten
    IR_lijdetectie_PORT &= ~(1 << IR_lijdetectie);

    //interrupt
    ///EIMSK |= (1 << INT4); // interrupt 4 (pin 2) aanzetten
    //EICRB |= (1 << ISC41) | (1 << ISC40); // interrupt 4 (pin 2), interrupt op rising edge
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

    // EXTERNE INTERRUPT ACKNOWLEDGE VAN MODULE
    EIMSK |= (1 << INT0); // interrupt 0 (pin 21) aanzetten
    EICRA |= (1 << ISC01) | (1 << ISC00); // interrupt 0 (pin 21), interrupt op rising edge

    // TIMER 3
    TCCR3B = (0 << CS32)|(1 << CS31)|(0 << CS30);
}




void init(void){
    init_rfid_module();
    init_us_sensor();
    init_lijndetectieIR();
    init_h_brug_dual();
    init_communicatie();
    sei();
}
