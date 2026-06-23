#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "communicatie_lib.h"
#include "init.h"
#include "motor_lib.h"
#include "navigatie_lib.h"
#include "rfid_module_lib.h"
#include "us_sensor_lib.h"



void init_test(void){

    DDRB |= (1 << PB7);
    DDRB |= (1 << PB6);

    PORTB |= (1 << PB7); // uit
    PORTB |= (1 << PB6); // uit

//    DDRB |= (1 << PB5);
//    DDRB |= (1 << PB4);

    DDRF &= ~(1 << PF1);
    DDRF &= ~(1 << PF2);
    DDRF &= ~(1 << PF3);
}


void test(void){

    //static int pressed = 0;
    static int released = 1;

    if (((PINF & (1 << PF1)) != 0)&& released == 0)   // Schakkel check S2 Losgelaten
    {
        PORTB |= (1 << PB7);
        PORTB |= (1 << PB6);      // Led Groen off
        _delay_ms(30);
        released = 1;
    }

    if (((PINF & (1 << PF1)) == 0) && released == 1)   // Schakel check s2 Ingedrukt
    {
        PORTB &= ~(1 << PB7);
        PORTB &= ~(1 << PB6);       // Led Groen on
        _delay_ms(100);
        released = 0;
    }
}

void test_versturen(void){
    int released = 1;
    if (((PINF & (1 << PF1)) == 0) && released == 1){
        NEXT_AGV_PORT |= (1 << NEXT_AGV);
        released = 0;
    }
    else{released = 1;}
}


void test_ontvang(void){
    if (((NEXT_MOD_PIN & (1 << NEXT_MOD)) != 0)){
          PORTB &= ~(1 << PB7);
          _delay_ms(500);
          acknowledge_agv();
    }
    else{PORTB |= (1 << PB7);}
}
