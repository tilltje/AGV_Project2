#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "communicatie_lib.h"
#include "init.h"
#include "motor_lib.h"
#include "navigatie_lib.h"
#include "rfid_module_lib.h"
#include "us_sensor_lib.h"


void acknowledge_agv(void) {
    ACK_AGV_PORT |= (1 << ACK_AGV);
    TCNT3 = 0;
    TIFR3 = (1 << TOV3);
    TIMSK3 |= (1 << TOIE3);
}

ISR(TIMER3_OVF_vect) {
    ACK_AGV_PORT &= ~(1 << ACK_AGV);
    TIMSK3 &= ~(1 << TOIE3); // interrupt weer uitzetten
}
