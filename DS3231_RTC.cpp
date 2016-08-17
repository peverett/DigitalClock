#include "DS3231_RTC.h"

// This is the hardcoded RTC module I2C address.
static const uint8_t DS3231_I2C_ADDRESS = 0x68;

// Helper function that converts char Binary Coded Decimal (BCD) value into decimal.
static uint8_t bcd2dec(char mask, char val)
{
  val = val & mask;
  return (uint8_t)((val >> 4) * 10) + (val & 0xF);
}

// Helper function that converts decimal to Bindary Coded Decimal (BCD).
static char dec2bcd(uint8_t val)
{
  return (char)(((val/10) << 4) | val % 10);
}

// Reads the date/time from DS2321 Registers 0x00 to 0x06 (7 bytes), directly 
// into the TM_T structure. The values are converted from BCD into decimal.
TM_T *get_date_time(TM_T *date_time)
{
    uint8_t *ptr = (uint8_t *)date_time;

    // Set I2C to the DS3231 address and the register to read from, register 0x00.
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0x00);
    Wire.endTransmission();

    // Read the 7 bytes from register 0x00 to 0x06.
    Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
    while(Wire.available())
    {
      *ptr++ = bcd2dec( 0x7F, Wire.read() );
    }
    
    return date_time;
}

// Reads the temperature from registers 0x11 (whole) and 0x12 (fraction).
// For the temp, only interested in 0.5 degree changes, whereas the register
// used the top two bits  to represent 0.0, 0,25, 0.5 and 0,75. By only reading 
// the top bit and checking for that, give the 0.5 degree step. 
TEMP_T *get_temp(TEMP_T *temp)
{
    uint8_t *ptr = (uint8_t *)temp;
    
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0x11);
    Wire.endTransmission();

    // Read 2 bytes from register 0x11 to 0x12.
    Wire.requestFrom(DS3231_I2C_ADDRESS, 2);
    while(Wire.available())
    {
      *ptr++ = Wire.read();  // Temp is NOT BCD encoded.
      *ptr = (0x80 & Wire.read()) ? 5 : 0;
    }

    return temp;
}

void set_date_time(TM_T *date_time)
{
    // Set I2C to the DS3231 address and the register to read from, register 0x00.
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0x00); // register 0x00
    Wire.write( dec2bcd(date_time->tm_sec) ); 
    Wire.write( dec2bcd(date_time->tm_min) ); 
    Wire.write( dec2bcd(date_time->tm_hour) );
    Wire.write( date_time->tm_wday );
    Wire.write( dec2bcd(date_time->tm_mday) );
    Wire.write( dec2bcd(date_time->tm_mon) );
    Wire.write( dec2bcd(date_time->tm_year) );
    Wire.endTransmission();
}

// Reads registers 0x08-0x09 (AL1M2-AL1M3) for Alarm1 - Seconds is always 0
// Reads registers 0x0B-0x0C (AL1M2-AL2M3) for Alarm2 
uint8_t get_alarm_time(uint8_t alarm_id, ALARM_T *alarm_time)
{
    int result = 0;

    if (alarm_id == ALARM1 || alarm_id == ALARM2) {
        uint8_t *ptr = (uint8_t *)alarm_time;
        uint8_t alarm_reg = 0x08;           // Alarm 1 by default.

        if (alarm_id == ALARM2) {
            alarm_reg = 0x0B;               // Alarm 2.
        }

        // set the register to read from - alarm1 or alarm2.
        Wire.beginTransmission(DS3231_I2C_ADDRESS);
        Wire.write(alarm_reg);
        Wire.endTransmission();

        // read 2 bytes from the alarm registers - minutes & hours
        Wire.requestFrom(DS3231_I2C_ADDRESS, 2);
        while(Wire.available())
        {
          *ptr++ = bcd2dec( 0x7F, Wire.read() );
        }

        result = 1;
    }
    return result;
}

// Writes registers 0x07-0x09 (AL1M1-AL1M3) for Alarm1 - Seconds is always 0
// Writes registers 0x0B-0x0C (AL1M2-AL2M3) for Alarm2 
int set_alarm_time(uint8_t alarm_id, const ALARM_T *alarm_time)
{
    int result = 0;

    if (alarm_id == ALARM1 || alarm_id == ALARM2) {
        uint8_t alarm_reg = 0x07;       // Alarm 1 by default.

        if (alarm_id == ALARM2) {
            alarm_reg = 0x0B;               // Alarm 2.
        }

        // Set the register to write to - alarm1 or alarm2.
        Wire.beginTransmission(DS3231_I2C_ADDRESS);
        Wire.write( alarm_reg );
        
        if (alarm_id == ALARM1) {   // Only required for ALARM1
          Wire.write( 0 );          // Set seconds to 0.
        }
        
        Wire.write( dec2bcd(alarm_time->tm_min) );
        Wire.write( dec2bcd(alarm_time->tm_hour) );
        Wire.endTransmission();
        
        result = 1;
    }
    
    return result;
}

// Sets the A1M4/A2M4 bit 7 to alarm when hours, minutes (and seconds) match.
// Sets the appropriate bit in the Control register (after reading it).
// Clears the appropriate bit in the Status register (after readint it).
int set_alarm(uint8_t alarm_id, bool enable)
{
    uint8_t temp_reg;

    int result = 0;

    if (alarm_id == ALARM1 || alarm_id == ALARM2) {
        uint8_t alarm_reg = 0x0A;       // A1M4 by default.

        if (alarm_id == ALARM2) {
            alarm_reg = 0x0D;               // A2M4.
        }

        // Set the register to write to - A1M4 or A2M4.
        Wire.beginTransmission(DS3231_I2C_ADDRESS);
        Wire.write( alarm_reg );
        if (enable)
            Wire.write( 0x80 );                 // Set bit 7 - alarm on hours/mins.
        else 
            Wire.write( 0x00 );
        Wire.endTransmission();

        // Read the Control register and then set the appropriate alarm bit.
        Wire.beginTransmission(DS3231_I2C_ADDRESS);
        Wire.write( 0x0E );
        Wire.endTransmission();

        Wire.requestFrom(DS3231_I2C_ADDRESS, 1);
        while(Wire.available())
        {
          temp_reg = Wire.read();
        }

        // Now write it back with the appropriate bit set or unset.
        Wire.beginTransmission(DS3231_I2C_ADDRESS);
        Wire.write( 0x0E );
        if (enable)
            Wire.write( temp_reg | alarm_id );
        else
            Wire.write( temp_reg & (~alarm_id) );
        Wire.endTransmission();

        // If enabling an alarm...
        // Read the Status register and then clear the alarm bit.
        if (enable) {
            clear_alarm(alarm_id);
        }
        
        result = 1;
    }
    
    return result;
}

// Read the Control and Status registers basically.
void get_alarm_status(uint8_t *enabled, uint8_t *triggered)
{
    int result = 0;

    // Read the Control register and  mask out all but the Alarm bits.
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write( 0x0E );
    Wire.endTransmission();

    Wire.requestFrom(DS3231_I2C_ADDRESS, 1);
    while(Wire.available())
    {
      *enabled = ALARM_MASK & Wire.read();
    }

    // Read the Status register alarm bits
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write( 0x0F );
    Wire.endTransmission();

    Wire.requestFrom(DS3231_I2C_ADDRESS, 1);
    while(Wire.available())
    {
      *triggered = ALARM_MASK & Wire.read();
    }
}

int clear_alarm(uint8_t alarm_id)
{
    int result = 0;

    if (alarm_id & ALARM_MASK) {
        uint8_t temp_reg;

        // Read the Status register.
        Wire.beginTransmission(DS3231_I2C_ADDRESS);
        Wire.write( 0x0F );
        Wire.endTransmission();

        Wire.requestFrom(DS3231_I2C_ADDRESS, 1);
        while(Wire.available())
        {
          temp_reg = Wire.read();
        }

        // Now write it back with the appropriate bit cleared.
        Wire.beginTransmission(DS3231_I2C_ADDRESS);
        Wire.write( 0x0F );
        Wire.write( temp_reg & (~alarm_id) );
        Wire.endTransmission();

        result = 1;
    }
}
