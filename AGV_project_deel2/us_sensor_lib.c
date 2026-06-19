#include "us_sensor_lib.h"


uint16_t ultrasoonAfstand_R_VOORUIT(void)
{
    // 1. Trigger
    US_TRIG_R_VOOR_PORT &= ~(1 << US_TRIG_R_VOOR);
    US_TRIG_R_VOOR_PORT |= (1 << US_TRIG_R_VOOR); _delay_us(10);
    US_TRIG_R_VOOR_PORT &= ~(1 << US_TRIG_R_VOOR);

    // 2. Wacht op echo
    uint32_t timeout = TIMEOUT;
    while (!(US_ECHO_R_VOOR_PIN & (1 << US_ECHO_R_VOOR)) && timeout--);
    if (timeout == 0) return 999;

    // 3. Timer starten (prescaler 8)
    TCNT1 = 0;
    TCCR1B = (1 << CS11);

    // 4. Wachten op einde echo
    while (US_ECHO_R_VOOR_PIN & (1 << US_ECHO_R_VOOR) && TCNT1 < OVERFLOW);
    TCCR1B = 0;

    // 5. Bereken afstand
    uint16_t distance = TCNT1 * TICKFACTOR;

    // 6. Return waarde
    return distance;
}

uint16_t ultrasoonAfstand_L_VOORUIT(void)
{
    // 1. Trigger
    US_TRIG_L_VOOR_PORT &= ~(1 << US_TRIG_L_VOOR); //_delay_us(2);
    US_TRIG_L_VOOR_PORT |= (1 << US_TRIG_L_VOOR); _delay_us(10);
    US_TRIG_L_VOOR_PORT &= ~(1 << US_TRIG_L_VOOR);

    // 2. Wacht op start echo
    uint32_t timeout = TIMEOUT;
    while(!(US_ECHO_L_VOOR_PIN & (1 << US_ECHO_L_VOOR)) && timeout--);
    if(timeout == 0) return 999; // Foutmelding

    // 3. Start timer (Prescaler 8 -> 1 tick = 0.5us)
    TCNT1 = 0;
    TCCR1B = (1 << CS11);

    // 4. Wacht op einde echo
    while((US_ECHO_L_VOOR_PIN & (1 << US_ECHO_L_VOOR)) && TCNT1 < OVERFLOW);
    TCCR1B = 0; // Stop timer

    // 5. Bereken: ticks * 0.5us * 0.0343 / 2
    uint16_t distanceL = TCNT1 * TICKFACTOR;

    // 6. Return waarde
    return distanceL;
}

///ACHTERUIT///
uint16_t ultrasoonAfstand_R_ACHTERUIT(void)
{
    // 1. Trigger
    US_TRIG_R_ACHTER_PORT &= ~(1 << US_TRIG_R_ACHTER);
    US_TRIG_R_ACHTER_PORT |= (1 << US_TRIG_R_ACHTER); _delay_us(10);
    US_TRIG_R_ACHTER_PORT &= ~(1 << US_TRIG_R_ACHTER);

    // 2. Wacht op echo
    uint32_t timeout = TIMEOUT;
    while (!(US_ECHO_R_ACHTER_PIN & (1 << US_ECHO_R_ACHTER)) && timeout--);
    if (timeout == 0) return 999;

    // 3. Timer starten (prescaler 8)
    TCNT1 = 0;
    TCCR1B = (1 << CS11);

    // 4. Wachten op einde echo
    while (US_ECHO_R_ACHTER_PIN & (1 << US_ECHO_R_ACHTER) && TCNT1 < OVERFLOW);
    TCCR1B = 0;

    // 5. Bereken afstand
    uint16_t distance = TCNT1 * TICKFACTOR;

    // 6. Return waarde
    return distance;
}

uint16_t ultrasoonAfstand_L_ACHTERUIT(void)
{
    // 1. Trigger
    US_TRIG_L_ACHTER_PORT &= ~(1 << US_TRIG_L_ACHTER); //_delay_us(2);
    US_TRIG_L_ACHTER_PORT |= (1 << US_TRIG_L_ACHTER); _delay_us(10);
    US_TRIG_L_ACHTER_PORT &= ~(1 << US_TRIG_L_ACHTER);

    // 2. Wacht op start echo
    uint32_t timeout = TIMEOUT;
    while(!(US_ECHO_L_ACHTER_PIN & (1 << US_ECHO_L_ACHTER)) && timeout--);
    if(timeout == 0) return 999; // Foutmelding

    // 3. Start timer (Prescaler 8 -> 1 tick = 0.5us)
    TCNT1 = 0;
    TCCR1B = (1 << CS11);

    // 4. Wacht op einde echo
    while((US_ECHO_L_ACHTER_PIN & (1 << US_ECHO_L_ACHTER)) && TCNT1 < OVERFLOW);
    TCCR1B = 0; // Stop timer

    // 5. Bereken: ticks * 0.5us * 0.0343 / 2
    uint16_t distanceL = TCNT1 * TICKFACTOR;

    // 6. Return waarde
    return distanceL;
}

