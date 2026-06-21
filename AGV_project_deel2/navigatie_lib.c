#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "communicatie_lib.h"
#include "init.h"
#include "motor_lib.h"
#include "navigatie_lib.h"
#include "rfid_module_lib.h"
#include "us_sensor_lib.h"

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

void padNavigerenNorm(void)
{
    int wandenWeg = 0;
    static unsigned int diffAfstand = 0;
    static unsigned int afstandL = 0;
    static unsigned int afstand_R = 0;
    int count = 0;
    int rfid_module_teller = 0;
    motor_config(VOORUIT, LINKS);
    motor_config(VOORUIT, RECHTS);

    motor_L(1.0);
    motor_R(1.0);
    while (wandenWeg < 2)
    {
        /// onderstaande stukje toegevoegd voor rfid module
        if (((MODNUMMER_PIN & (1 << MODNUMMER)) == 0) && ((NEXT_MOD_PIN & (1 << NEXT_MOD)) != 0)) {
            motor_L(0.0);
            motor_R(0.0);
            acknowledge_agv();

            TCNT1 = 0;
            while (rfid_module_teller < 2) { // 2 sec wachten, elke cycle duurt ongeveer 1 sec
                if (TIFR1 & (1 << TOV1)) {
                    TIFR1 = (1 << TOV1);
                    rfid_module_teller++;
                }
            }

        }


        afstandL = ultrasoonAfstand_L_VOORUIT();
        //afstandL = ultrasoonAfstand_L_VOOR();
        afstand_R = ultrasoonAfstand_R_VOORUIT();

        ///print_waarde(afstandL);   ///TEST

        if ((ultrasoonAfstand_R_VOORUIT() > VERWEG) || (ultrasoonAfstand_L_VOORUIT() > VERWEG)) wandenWeg++;
        else
        {
            wandenWeg = 0;
            if (afstandL > afstand_R)
            {
                diffAfstand = afstandL - afstand_R;
                motor_L(1.0);
                motor_R(percentageSteering_R(diffAfstand));
            }

            if (afstand_R > afstandL)
            {
                diffAfstand = afstand_R - afstandL;
                motor_L(percentageSteering_L(diffAfstand));
                motor_R(1.0);
            }
        }
    }
    motor_R(1.0);
    motor_L(1.0);
}

void padNavigerenLinks(void){
    ///...///
}

void padNavigerenRechts(void){
    ///...///
}

void kerenR(void)
{
    int teller = 0;
    int count = 0;
    int temp = 0;
    while(temp == 0)
    {
    TCNT2 = 6;
    TCCR2A = 0;
    TCCR2B = (0 << CS22)|(1 << CS21) | (1 << CS20);
    motor_L(0);
    motor_R(1);

    count = 0;
    while(1)
    {
        if (TIFR2 & (1 << TOV2))
        {
            if (++count >= 500)
            {
                TIFR2 = (1 << TOV2);
                TCNT2 = 6;
                break;
            }
            TIFR2 = (1 << TOV2);
            TCNT2 = 6;
        }
    }
    motor_L(1);
    motor_R(1);

    TCNT2 = 6;
    count = 0;
    while (1)
    {
        if (TIFR2 & (1 << TOV2))
        {
            if (++count >= 400)     ///WP COUNT -> 300
            {
                break;
            }
            TIFR2 = (1 << TOV2);
            TCNT2 = 6;
        }
    }
    teller++;
    if (ultrasoonAfstand_L_VOORUIT() < 20) {temp = 1;}
    //if (ultrasoonAfstand_R() < 20) {temp = 1;}
    }
}
