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

void rfid_module(void) {
    while ((NEXT_MOD_PIN & (1 << NEXT_MOD)) == 0) {
        // niks doen
    }
    padNavigeren(LINKS);
    NEXT_AGV_PORT |= (1 << NEXT_AGV);   // bocht bereikt
    EIMSK |= (1 << INT4);
    kerenR();                           // bocht
    padNavigeren(LINKS);
    /// stoppen in vak
}
