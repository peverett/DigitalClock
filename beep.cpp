#include "beep.h"

void beepDelay(int delay_ms)
{
  analogWrite(PWM_PIN, PWM_VALUE);
  delay(delay_ms);
  analogWrite(PWM_PIN, 0);
}
