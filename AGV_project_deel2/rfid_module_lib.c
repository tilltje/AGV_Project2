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

// Programma voor detectiemodule
void rfid_module(void) {
    while ((NEXT_MOD_PIN & (1 << NEXT_MOD)) == 0) { // Wachten tot knop wordt ingedrukt
    }
    padNavigeren(LINKS); // Rijden, links of rechts maakt hier niet uit
    NEXT_AGV_PORT |= (1 << NEXT_AGV);   // Bocht is bereikt, dus aan module doorgeven dat die moet stoppen met detecteren
    EIMSK |= (1 << INT4);               // Lijndetectie interrupt aanzetten
    kerenR();                           // Bocht uitvoeren
    padNavigeren(LINKS); // Rijden, links of rechts maakt hier niet uit
}
