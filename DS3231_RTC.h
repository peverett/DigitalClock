#ifndef DS3231_RTC_
#define DS3231_RTC_

/*!
 * \file
 *
 * \brief Application Programming Interface for DS3231 Real-Time Clock
 *
 * The DS3231 is a low-cost, extremely accruate I2C real-time clock (RTC) with
 * integrated temperature compensated crystal oscillator (TCXO) and crystal.
 *
 * Features: 
 *      - Date: Year, month, day of month, day of week. Automatically days of 
 *        month and for leap years.
 *      - Time: Hours, minutes, seconds - 24/12 hour format.
 *      - Two programmable time of day alarms.
 *      - Programmable square wave output.
 *      - Battery-backup for continuous time-keeping. 
 *      - 3.3v operation.
 *
 * Datasheet: https://datasheets.maximintegrated.com/en/ds/DS3231.pdf
 *
 * NOTES: 
 *      - Although the DS3231 module supports 24 or 12 hour format, only the 
 *        24-hour format is supported by this API.
 *      - The Alarm 1/2 Interrupt Enable bits of the Control Register (0x0E)
 *        are used to indicate if an alarm is set or not. This will cause the
 *        INT/SQW pin to be set when an alarm time is reached. Which alarm 
 *        has been triggered can be determined by reading the Status Register.
 *        (get_alarm_status) but getting the interrupt (I/O input) is outside
 *        the scope of this API.      
 */

/*!
 * \defgroup ALARM definitions
 *
 * In the Control (0x0E) and Status (0x0F) Registers, Alarm 1 is bit 0 and
 * Alarm 2 is bit 1. Use these defines to identify these alarms.
 *
 * \{
 */
#define ALARM1 (0x01)       /*!< Alarm 1 is represented by bit 0. */
#define ALARM2 (0x02)       /*!< Alarm 2 is represented by bit 1. */
#define ALARM_MASK (0x03)   /*!< Bit mask for #ALARM1 and #ALARM2. */
/*! \} */

#include <Wire.h>

/*!
 * \brief TM_T struct for representing date and time values in this API.
 *
 * Very similar to the C standard time.h 'struct tm' but no fields for
 * - tm_yday - days since January 1
 * - tm_isdst - Daylight Saving Time flag.
 *
 * For simplicity, no validation of field ranges is performed when setting 
 * the time. Out of range values will cause the DS3231 module to malfunction.
 *
 * The field order matches the order of I2C Registers on the DS3231 module.
 */
typedef struct _tm {
  uint8_t tm_sec;       /*!< Seconds in the minute - range 0..59 */
  uint8_t tm_min;       /*!< Minutes in the hour - range 0..59 */
  uint8_t tm_hour;      /*!< Hours in the day - range 0..23 */
  uint8_t tm_wday;      /*!< Day of week - range 0 (Monday) .. 6 (Sunday) */
  uint8_t tm_mday;      /*!< Day in month - range 1..31 */
  uint8_t tm_mon;       /*!< Month in year - range 1..12 */
  uint8_t tm_year;      /*!< Year in century - range 0..99 */
} TM_T;

/*!
 * \brief Alarm time - hour (24-hour format) and minute for the Alarm.
 */
typedef struct _alarm {
  uint8_t tm_min;       /*!< Minute in the hour - range 0..59 */
  uint8_t tm_hour;      /*!< Hour in the day - range 0..23 */
} ALARM_T;

/*!
 * \Brief TEMP_T struct for representing the temperature read from the RTC.
 */
typedef struct _temperature {
  uint8_t temp_degrees;         /*!< Temperature in degrees centigrade. */
  uint8_t temp_half;            /*!< Temperature half degree: 0 or 5 (.5) */
} TEMP_T;

/*!
 * \brief Read and return the date and time from the RTC.
 *
 * \param date_time Pointer to the TM_T struct which will contain the date
 *        and time read from the RTC.
 *
 * \result The date and time is read and the values stored in the date_time
 *         pointer. The pointer is also returned by this function.
 */
TM_T *get_date_time(TM_T *date_time);

/*!
 * \brief Read and return the temperature.
 *
 * The DS3231 represents the temperature with 10-bits across two registers
 * (11h-12h) to a resolution of 0.25h. However, only half-degree resolution is
 * represented in this API.
 *
 * \param temp Pointer to TEMP_T struct which will contain the temperature when
 *        it has been read.
 *
 * \result The temperature is read and returned in Centigrade with a half 
 *         degree resolution. The pointer passed as a parameter is also 
 *         returned by this function.
 */
TEMP_T *get_temp(TEMP_T *temp);

/*! 
 * \brief Set the date and time.
 *
 * \param date_time Pointer to the TM_T struct which will contain the date
 *        and time read from the RTC.
 */
void set_date_time(TM_T *date_time);

/*! 
 * \brief Get the alarm time.
 *
 * In this implementation, the Alarm 1/2 Interrupt Enable bits of the Control
 * Register are used to indicate if the alarm is active or not. 
 *
 * \param alarm_id Which alarm to read the set time for - #ALARM1 or #ALARM2.
 * \param alarm_time Pointer to the ALARM_T struct which will contain the time
 *        the time the alarm is set for. 
 * \result The set time is passed in the TM_T struct passed as a pointer.
 *         If the alarm is set, the alarm id (#ALARM1 or #ALARM2) is returned.
 *         If the alarm is not set, the function returns 0.
 */
uint8_t get_alarm_time(uint8_t alarm_id, ALARM_T *alarm_time);

/*! 
 * \brief Set alarm time
 *
 * Sets the alarm time of either Alarm 1 or Alarm 2 on the DS3231 module. 
 * Automatically clears the appropriate alarm status bit in the status register
 * so that it will be set when the alarm time is reached. 
 *
 * \param alarm_id Which alarm is to be set - #ALARM1 or #ALARM2.
 * \param alarm_time Uses the ALARM_T struct.
 *
 * \result Returns 1 if successful or 0 otherwise.
 */
int set_alarm_time(uint8_t alarm_id, const ALARM_T *alarm_time);

/*!
 * \brief Set alarm
 *
 * Enables or disables the alarm but setting the appropriate bit in the control
 * register. This will also clear the bit on the status register if the alarm
 * is Enabled.
 *
 * \param alarm_id Which alarm is to be set - #ALARM1 or #ALARM2.
 * \param enable True to enable (set) the alarm, False to disable (unset).
 *
 * \result Returns 1 if successful or 0 otherwise.
 */
int set_alarm(uint8_t alarm_id, bool enable);

/*!
 * \brief get_alarm_status
 *
 * Reads and returns:
 *      - Whether the alarms have been enabled
 *      - Whether the alarms have triggered.
 *
 * \param enabled Pointer to uint8_t bit field which will contain which alarms
 *        are enabled (#ALARM1 and/or #ALARM2).
 * \param triggered Ponter to uint8_t bit field which will contain which alarms
 *        have been triggered (#ALARM1 and/or #ALARM2).
 */
void get_alarm_status(uint8_t *enabled, uint8_t *triggered);

/* \brief cancel_alarm
 *
 * Clears the specied alarm bit(s) in the control register.
 *
 * \param alarm_id The alarm to clear - #ALARM1, #ALARM2 or both.
 *
 * \result Returns 1 if successful or 0 otherwise.
 */
int clear_alarm(uint8_t alarm_id);

#endif   /* DS3231_RTC_ */
