#ifndef BEEP_H_
#define BEEP_H_

#include <arduino.h>

#define PWM_VALUE 200
#define PWM_PIN 25

static void inline beepOn()
{
  analogWrite(PWM_PIN, PWM_VALUE);
}

static void inline beepOff()
{
  analogWrite(PWM_PIN, 0);
}

void beepDelay(int delay_ms);

#endif /* BEEP_H_ */
