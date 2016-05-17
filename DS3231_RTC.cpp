#include "DS3231_RTC.h"

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

