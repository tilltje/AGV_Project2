/// INCLUDES ///
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include "init.h"
#include "motor_lib.h"
#include "navigatie_lib.h"
#include "rfid_module_lib.h"
#include "us_sensor_lib.h"

/// FUNCTIES ///

volatile int lijnDetectie = 0;

//lijndetectie, bij de tweede lijn die de AGV tegenkomt moet hij een stukje terugrijden en vervolgens stilstaan.
ISR(INT4_vect){
   if(lijnDetectie==1){
        //motoren even uit
        motor_L(0.0);
        motor_R(0.0);
        timer_ms(50);

        //motoren instellen om achteruit te rijden
        motor_config(ACHTERUIT,LINKS);
        motor_config(ACHTERUIT,RECHTS);
        timer_ms(500);

        // een stukje achteruit rijden
        motor_L(0.75);
        motor_R(0.75);
        timer_ms(500);
        while(1){
            motor_L(0.0);
            motor_R(0.0);
        }
   }
   else{lijnDetectie = 1;}
}

//2 seconden stoppen bij pakket, vindt plaats als module ACK_MOD hoog maakt
ISR(INT0_vect) {
    //Stilstaan
    motor_L(0.0);
    motor_R(0.0);
    timer_s(2);
}

// Timer voor aantal milliseconden wachten
// 16 MHz/64 = 250.000 bits per sec -> 250 bits per ms
// (2^8-1)-250 = 5
void timer_ms(int aantal){
    TCNT2 = 5;
    TCCR2A = 0;
    TCCR2B = (0 << CS22)|(1 << CS21) | (1 << CS20); // Prescaler 64
    int count = 0;
    int timer_klaar = FALSE;

    while(timer_klaar == FALSE) {
        if (TIFR2 & (1 << TOV2)) // Timer loopt af, 1 ms voorbij
        {
            if (++count >= aantal) // Gewenst aantal ms is voorbij
            {
                TIFR2 = (1 << TOV2);
                timer_klaar = TRUE;
            }
            TIFR2 = (1 << TOV2); // flag verwijderen
            TCNT2 = 6;
        }
    }
}

// Timer voor aantal seconden wachten
// 16 MHz/256 = 62500 bits per sec
// (2^16-1)-62500=3035
void timer_s(int aantal){
    TCNT4 = 3035;
    TCCR4A |= 0;
    TCCR4B |= (1 << CS42)|(0 << CS41) | (0 << CS40); // Prescaler 256
    int count = 0;
    int timer_klaar = FALSE;

    while(timer_klaar == FALSE) {
        if (TIFR4 & (1 << TOV4)) // Timer loopt af, 1 sec voorbij
        {
            if (++count >= aantal) // Gewenst aantal seconden is voorbij
            {
                TIFR4 = (1 << TOV4);
                timer_klaar = TRUE;
            }
            TIFR4 = (1 << TOV4); // Flag verwijderen
            TCNT4 = 3035;
        }
    }
}

// Initialisatie ultrasone sensor
void init_ultrasoon_sensor(void)
{
    //ULTRASOON Echo als INPUT configureren
    ULTRASOON_ECHO_R_DDR &= ~(1 << ULTRASOON_ECHO_R);
    ULTRASOON_ECHO_L_DDR &= ~(1 << ULTRASOON_ECHO_L);

    //ULTRASOON Trigger als OUTPUT configureren
    ULTRASOON_TRIGGER_R_DDR |= (1 << ULTRASOON_TRIGGER_R);
    ULTRASOON_TRIGGER_L_DDR |= (1 << ULTRASOON_TRIGGER_L);

    //ULTRASOON Echo laagzetten
    ULTRASOON_TRIGGER_R_PORT &= ~(1 << ULTRASOON_ECHO_R);
    ULTRASOON_TRIGGER_L_PORT &= ~(1 << ULTRASOON_ECHO_L);
}

// Initialisatie H-brug
void init_h_brug_dual(void)
{
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

// Initialisatie PWM timer
void init_timer_PWM(void)
{
    ICR5 = TOP_VALUE;
    TCCR5A = (1 << WGM51) | (0 << WGM50) | (1 << COM5A1) | (0 << COM5A0) | (1 << COM5C1) | (0 << COM5C0);
    TCCR5B = (1 << WGM53) | (1 << WGM52) | (0 << CS52) | (1 << CS51) | (0 << CS50);
}

// Initialisatie communicatie
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

    // EXTERNE INTERRUPT VOOR PAKKETDETECTIE
    EIMSK |= (1 << INT0); // interrupt 0 (pin 21) aanzetten
    EICRA |= (1 << ISC01) | (1 << ISC00); // interrupt op rising edge
}

void init_lijndetectie(void) { // externe interrupt, wordt pas aangezet na bocht
    EICRB |= (1 << ISC41);
    EICRB |= (1 << ISC40);
}

// Initialisatie
void init_function(void)
{
    init_ultrasoon_sensor();
    init_h_brug_dual();
    init_timer_PWM();
    init_communicatie();
    init_lijndetectie();
    sei();
}
