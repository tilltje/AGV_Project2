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

// Bepaalt snelheid rechts a.d.h.v. afstand tot rand
float percentageSteering_R(int afstand) //int diffAfstand
{
    static float helftPadBreedte = HALF_PAD;
    static float percentageAfwijking = 0;
    if (helftPadBreedte < afstand) {
        percentageAfwijking = 0;
    }
    else {
        percentageAfwijking = (helftPadBreedte - afstand)/helftPadBreedte;
    }
    return percentageAfwijking;
}

// Bepaalt snelheid links a.d.h.v. afstand tot rand
float percentageSteering_L(int afstand) //int diffAfstand
{
    static float helftPadBreedte = HALF_PAD;
    static float percentageAfwijking = 0;
    if (helftPadBreedte < afstand) {
        percentageAfwijking = 0;
    }
    else {
        percentageAfwijking = (helftPadBreedte - afstand)/helftPadBreedte;
    }
    return percentageAfwijking;
}

// Controleert afstanden tot wanden en past op basis daarvan snelheden aan
void padNavigeren(int kant)
{
    int wandenWeg = 0;
    static unsigned int diffAfstand = 0;
    static unsigned int afstandL = 0;
    static unsigned int afstand_R = 0;

    motor_config(VOORUIT, LINKS);
    motor_config(VOORUIT, RECHTS);

    motor_L(1.0);
    motor_R(1.0);
    while (wandenWeg < 2) // Blijft in de while totdat de wanden weg zijn.
    {
        afstandL = ultrasoonAfstand_L();
        afstand_R = ultrasoonAfstand_R();

        if ((ultrasoonAfstand_R() > VERWEG) || (ultrasoonAfstand_L() > VERWEG)) {
            wandenWeg++;
        }
        else
        {
            wandenWeg = 0;
            if (afstandL > afstand_R)
            {
                diffAfstand = afstandL - afstand_R;
                motor_L(1.0);
                motor_R(percentageSteering_R(diffAfstand));
            }
            else if (afstand_R > afstandL)
            {
                diffAfstand = afstand_R - afstandL;
                motor_L(percentageSteering_L(diffAfstand));
                motor_R(1.0);
            }
            else{
                motor_R(1.0);
                motor_L(1.0);
            }
        }
    }
    motor_R(1.0);
    motor_L(1.0);
}

// Bocht naar rechts,
void kerenR(void)
{
    int temp = 0;
    while(temp == 0)
    {
        // MOTOR L uit, MOTOR R aan
        motor_L(0);
        motor_R(1);

        timer_ms(500);

        // MOTOR L en R aan
        motor_L(1);
        motor_R(1);

        timer_ms(400);

        if (ultrasoonAfstand_L() < 20) {temp = 1;}
    }
}
