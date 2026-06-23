/*
Timer 0 NOG NIET
Timer 1 gebruikt voor us sensoren
Timer 2 gebruikt voor bochten
Timer 3 gebruikt voor acknowledge agv
Timer 4 gebruikt voor 2 sec stilstaan rfid module
Timer 5 gebruikt voor motoren

Externe interrupt: INT0 / arduino pin 21
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "communicatie_lib.h"
#include "init.h"
#include "motor_lib.h"
#include "navigatie_lib.h"
#include "rfid_module_lib.h"
#include "us_sensor_lib.h"
#include "testen.h"


int main(void)
{
    /// hier komt de code voor de AGV ///
    init();
    init_test();

    while(1){
        test_ontvang();
    }




/*
    while(1){
        /// TILMODULE ///
        if (!(MODNUMMER_PIN & (1 << MODNUMMER))){
            // TILMODULE
        }
        /// RFID ///
        else{ //modnummer laag
            rfid_module();
        }
    }

    return 0;
*/
}
