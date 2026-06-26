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

float percentageSteering_R(int temp) //int diffAfstand
{
    static float helftPadBreedte = HALF_PAD;
    static float percentageAfwijking = 0;
    if (helftPadBreedte < temp)  percentageAfwijking = 0;
    else percentageAfwijking = (helftPadBreedte - temp)/helftPadBreedte;
    return percentageAfwijking;
}

float percentageSteering_L(int temp) //int diffAfstand
{
    static float helftPadBreedte = HALF_PAD;
    static float percentageAfwijking = 0;
    if (helftPadBreedte < temp)  percentageAfwijking = 0;
    else percentageAfwijking = (helftPadBreedte - temp)/helftPadBreedte;
    return percentageAfwijking;
}

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
    while (wandenWeg < 2) // Blijft in de while tot dat de wanden weg zijn.
    {
        afstandL = ultrasoonAfstand_L();
        afstandL = ultrasoonAfstand_L();
        afstand_R = ultrasoonAfstand_R();

        if ((ultrasoonAfstand_R() > VERWEG) || (ultrasoonAfstand_L() > VERWEG)) wandenWeg++;
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

void timer_ms(int aantal){
    TCNT2 = 6;
    TCCR2A = 0;
    TCCR2B = (0 << CS22)|(1 << CS21) | (1 << CS20);
    int count = 0;
    int timer_klaar = FALSE;

    while(timer_klaar == FALSE)
    if (TIFR2 & (1 << TOV2))
        {
            if (++count >= aantal)
            {
                TIFR2 = (1 << TOV2);
                TCNT2 = 6;
                timer_klaar = TRUE;
            }
            TIFR2 = (1 << TOV2);
            TCNT2 = 6;
        }
}

void timer_s(int aantal){
    TCNT4 = 3036;
    TCCR4A = 0;
    TCCR4B = (1 << CS42)|(0 << CS41) | (0 << CS40);
    int count = 0;
    int timer_klaar = FALSE;

    while(timer_klaar == FALSE)
    if (TIFR4 & (1 << TOV4))
        {
            if (++count >= aantal)
            {
                TIFR4 = (1 << TOV4);
                TCNT4 = 6;
                timer_klaar = TRUE;
            }
            TIFR4 = (1 << TOV4);
            TCNT4 = 6;
        }
}
