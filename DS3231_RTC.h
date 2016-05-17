#ifndef DS3231_RTC_
#define DS3231_RTC_

// Very basic class for Arduino I2C control of the DS3231 Real-time Clock.
// Implemented as a singleton, as there can only be one instance on the I2C bus.
// Please refer to the DS3231 Extremely Accurate I2C-Integrated RTC/TCXO/Crystal
// Data sheet.

#include <Wire.h>

typedef struct _tm {
  uint8_t tm_sec;
  uint8_t tm_min;
  uint8_t tm_hour;
  uint8_t tm_wday;
  uint8_t tm_mday;
  uint8_t tm_mon;
  uint8_t tm_year;
} TM_T;

typedef struct _temperature {
  uint8_t temp_degrees;
  uint8_t temp_half;
} TEMP_T;

TM_T *get_date_time(TM_T *date_time);
TEMP_T *get_temp(TEMP_T *temp);
void set_date_time(TM_T *date_time);

#endif   /* DS3231_RTC_ */
