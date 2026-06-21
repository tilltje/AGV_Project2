#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "communicatie_lib.h"
#include "init.h"
#include "motor_lib.h"
#include "navigatie_lib.h"
#include "rfid_module_lib.h"
#include "us_sensor_lib.h"


void rfid_module(void) {
    while ((NEXT_MOD_PIN & (1 << NEXT_MOD)) == 0) {
        // niks doen
    }
    acknowledge_agv(); // acknowledgen naar module dat we gaan starten
    padNavigerenNorm();
    NEXT_AGV_PORT |= (1 << NEXT_AGV); // bocht bereikt
    kerenR(); // bocht
    /// stoppen in vak
}
