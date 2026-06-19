/*
 */

#include <avr/io.h>
#include <util/delay.h>
#include "init.h"
#include "us_sensor_lib.h"
#include "motor_lib.h"
#include "navigatie_lib.h"


int main(void)
{
    /// hier komt de code voor de AGV ///
    init();

    while(1){
        /// TILMODULE ///
        if (!(MODNUMMER_PIN & (1 << MODNUMMER))){
            // TILMODULE
        }
        /// RFID ///
        else{
            // RFID
        }
    }

    return 0;
}
