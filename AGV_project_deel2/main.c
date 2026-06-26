/* Code voor AGV. Bevat nu alleen de code voor de detectiemodule, omdat de tilhulp niet gerealiseerd is.
De vervangende module die gebruikt wordt voor de wisselopdracht communiceert op dezelfde manier als de detectiemodule,
waardoor hiervoor dezelfde code gebruikt kan worden.
 */
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
int main(void)
{
    init_function();

    while(1)
    {
        rfid_module(); // programma voor wanneer de detectiemodule erop staat
    }

    return 0;
}
