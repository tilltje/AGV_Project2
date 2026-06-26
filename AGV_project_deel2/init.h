#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED


// ULTRASOON //
#define ULTRASOON_ECHO_R                PC7
#define ULTRASOON_ECHO_R_DDR            DDRC
#define ULTRASOON_ECHO_R_PIN            PINC

#define ULTRASOON_TRIGGER_R             PC6
#define ULTRASOON_TRIGGER_R_DDR         DDRC
#define ULTRASOON_TRIGGER_R_PORT        PORTC

#define ULTRASOON_ECHO_L                PA6
#define ULTRASOON_ECHO_L_DDR            DDRA
#define ULTRASOON_ECHO_L_PIN            PINA

#define ULTRASOON_TRIGGER_L             PA7
#define ULTRASOON_TRIGGER_L_DDR         DDRA
#define ULTRASOON_TRIGGER_L_PORT        PORTA

// H-BRUG //
#define PWM_R                           PL5
#define PWM_R_DDR                       DDRL
#define PWM_R_PORT                      PORTL

#define PWM_L                           PL3
#define PWM_L_DDR                       DDRL
#define PWM_L_PORT                      PORTL

#define PWM_IN_1                        PL6
#define PWM_IN_1_DDR                    DDRL
#define PWM_IN_1_PORT                   PORTL

#define PWM_IN_2                        PL4
#define PWM_IN_2_DDR                    DDRL
#define PWM_IN_2_PORT                   PORTL

#define PWM_IN_3                        PL2
#define PWM_IN_3_DDR                    DDRL
#define PWM_IN_3_PORT                   PORTL

#define PWM_IN_4                        PL0
#define PWM_IN_4_DDR                    DDRL
#define PWM_IN_4_PORT                   PORTL

// OVERIG //
#define TOP_VALUE                       40000UL
#define RESET_VALUE_TIMER1              59286UL

#define TRUE                            1
#define FALSE                           0

// COMMUNICATIE //
#define MODNUMMER                       PG0      // Arduino Pin 41
#define MODNUMMER_DDR                   DDRG
#define MODNUMMER_PORT                  PORTG
#define MODNUMMER_PIN                   PING

#define NEXT_MOD                        PG1      // Arduino Pin 40
#define NEXT_MOD_DDR                    DDRG
#define NEXT_MOD_PORT                   PORTG
#define NEXT_MOD_PIN                    PING

#define ACK_AGV                         PG2      // Arduino Pin 39
#define ACK_AGV_DDR                     DDRG
#define ACK_AGV_PORT                    PORTG

#define LIJN                            PD7      // Arduino Pin 38
#define LIJN_DDR                        DDRD
#define LIJN_PORT                       PORTD

#define NEXT_AGV                        PC0      // Arduino Pin 37
#define NEXT_AGV_DDR                    DDRC
#define NEXT_AGV_PORT                   PORTC

#define ACK_MOD                         PD0      //Arduino Pin 21 (externe interrupt)
#define ACK_MOD_DDR                     DDRD
#define ACK_MOD_PORT                    PORTD
#define ACK_MOD_PIN                     PIND

// FUNCTIES //
void timer_ms(int aantal);
void timer_s(int aantal);
void init_ultrasoon_sensor(void);
void init_h_brug_dual(void);
void init_timer_PWM(void);
void init_communicatie(void);
void init_lijndetectie(void);
void init_function(void);

#endif // INIT_H_INCLUDED
