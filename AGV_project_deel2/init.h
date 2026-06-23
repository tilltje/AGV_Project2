#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

/// INCLUDE ///
#include <avr/io.h>
#include <util/delay.h>


/// ULTRASOON ///
// VOOR //
#define US_ECHO_L_VOOR             PA6      // Arduino pin 28
#define US_ECHO_L_VOOR_DDR         DDRA
#define US_ECHO_L_VOOR_PIN         PINA

#define US_TRIG_L_VOOR             PA7      // Arduino pin 29
#define US_TRIG_L_VOOR_DDR         DDRA
#define US_TRIG_L_VOOR_PORT        PORTA

#define US_ECHO_R_VOOR             PC7      // Arduino pin 30
#define US_ECHO_R_VOOR_DDR         DDRC
#define US_ECHO_R_VOOR_PIN         PINC

#define US_TRIG_R_VOOR             PC6      // Arduino pin 31
#define US_TRIG_R_VOOR_DDR         DDRC
#define US_TRIG_R_VOOR_PORT        PORTC

// ACHTER //
#define US_ECHO_L_ACHTER           PC5      // Arduino pin 32
#define US_ECHO_L_ACHTER_DDR       DDRC
#define US_ECHO_L_ACHTER_PIN       PINC

#define US_TRIG_L_ACHTER           PC4      // Arduino pin 33
#define US_TRIG_L_ACHTER_DDR       DDRC
#define US_TRIG_L_ACHTER_PORT      PORTC

#define US_ECHO_R_ACHTER           PC3      // Arduino pin 34
#define US_ECHO_R_ACHTER_DDR       DDRC
#define US_ECHO_R_ACHTER_PIN       PINC

#define US_TRIG_R_ACHTER           PC2      // Arduino pin 35
#define US_TRIG_R_ACHTER_DDR       DDRC
#define US_TRIG_R_ACHTER_PORT      PORTC

/// IR LIJNDETECTIE ///
#define IR_lijdetectie             PE4      // Arduino pin 2
#define IR_lijdetectie_DDR         DDRE
#define IR_lijdetectie_PORT        PORTE
#define IR_lijdetectie_PIN         PINE

/// H-BRUG ///
#define PWM_R                      PL5      // Arduino pin 44
#define PWM_R_DDR                  DDRL
#define PWM_R_PORT                 PORTL

#define PWM_L                      PL3      // Arduino pin 46
#define PWM_L_DDR                  DDRL
#define PWM_L_PORT                 PORTL

#define PWM_IN_1                   PL6      // Arduino pin 43
#define PWM_IN_1_DDR               DDRL
#define PWM_IN_1_PORT              PORTL

#define PWM_IN_2                   PL4      // Arduino pin 45
#define PWM_IN_2_DDR               DDRL
#define PWM_IN_2_PORT              PORTL

#define PWM_IN_3                   PL2      // Arduino pin 47
#define PWM_IN_3_DDR               DDRL
#define PWM_IN_3_PORT              PORTL

#define PWM_IN_4                   PL0      // Arduino pin 49
#define PWM_IN_4_DDR               DDRL
#define PWM_IN_4_PORT              PORTL

/// COMMUNICATIEPINNEN ///
#define MODNUMMER                  PG0      // Arduino Pin 41
#define MODNUMMER_DDR              DDRG
#define MODNUMMER_PORT             PORTG
#define MODNUMMER_PIN              PING

#define NEXT_MOD                   PG1      // Arduino Pin 40
#define NEXT_MOD_DDR               DDRG
#define NEXT_MOD_PORT              PORTG
#define NEXT_MOD_PIN               PING

#define ACK_AGV                    PG2      // Arduino Pin 39
#define ACK_AGV_DDR                DDRG
#define ACK_AGV_PORT               PORTG
//#define ACK_AGV_PIN                PING

#define LIJN                       PD7      // Arduino Pin 38
#define LIJN_DDR                   DDRD
#define LIJN_PORT                  PORTD

#define NEXT_AGV                   PC0      // Arduino Pin 37
#define NEXT_AGV_DDR               DDRC
#define NEXT_AGV_PORT              PORTC

#define ACK_MOD                    PD0      //Arduino Pin 21 (externe interrupt)
#define ACK_MOD_DDR                DDRD
#define ACK_MOD_PORT               PORTD
#define ACK_MOD_PIN                PIND

/// OVERIG ///
#define TRUE 1
#define FALSE 0


/// FUNCTIONS ///
void init_rfid_module(void);
void init_us_sensor(void);
void init_lijndetectieIR(void);
void init_h_brug_dual(void);
void init_communicatie(void);
void init(void);

#endif // INIT_H_INCLUDED
