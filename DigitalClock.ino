/**
 * Digital Clock Implementation
 * - Maple Leaf Mini STM 32
 * - ILI9341 TFT Touch 250 x 320
 * - DS3231 Real Time Clock
 */

#include <SPI.h>                  // Used by the TFT and Touch libraries
#include <Wire.h>                 // Used for accessing the DS3231 RTC on I2C.
#include <Adafruit_GFX_AS.h>      // Core graphics library, with extra fonts.
#include <Adafruit_ILI9341_STM.h> // STM32 DMA Hardware-specific library
#include <XPT2046.h>              // SPI capacitive touch interface
#include "DS3231_RTC.h"           // DS3231 Real Time Clock
#include "GUI.h"                  // Graphical User Interface classes
#include "DateTime.h"
#include "beep.h"

// The TFT Screen uses SPI 1 (default SPI port).
#define tft_cs   7
#define tft_dc   9
#define tft_rst  8  

// Pins for the touch panel - touch will used SPI2 port (pins 28 to 30).
#define touch_cs  31
#define touch_irq 27
#define touch_spiport 2

#define display_date_full 0
#define display_date 1
#define display_temp 2
#define display_last 3

#if 0
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
#endif

// Screen and touch panel
Adafruit_ILI9341_STM tft = Adafruit_ILI9341_STM(tft_cs, tft_dc, tft_rst);
XPT2046 touch = XPT2046(touch_cs, touch_irq, touch_spiport);

uint8_t dm = display_date;

DisplayTimeWidget dtw = DisplayTimeWidget(&tft, 0, 0);
DisplayDateFullWidget ddfw = DisplayDateFullWidget(&tft, 0, 120);
DisplayDateWidget ddw = DisplayDateWidget(&tft, 0, 120);
DisplayTempWidget temp = DisplayTempWidget(&tft, 0, 120);

void DisplayMain(uint8_t mode, bool display_time=true)
{
  TM_T now;
  get_date_time(&now);

  if (display_time)
  {
    tft.fillScreen(ILI9341_BLACK);
    tft.drawFastHLine(10, 120, 300, ILI9341_WHITE);  
    dtw.Display(now);
  }
  
  switch (mode)
  {
    case display_date_full:
      ddfw.Display(now);
      break;
    case display_date:
      ddw.Display(now);
      break;
    default:
      {
        TEMP_T temp_now;
        
        get_temp(&temp_now);
        temp.Display(temp_now);
      }
      break;
  }
}

static void DisplayUpdate(uint8_t mode)
{
  TM_T now;

  get_date_time(&now);
  dtw.Update(now);
  
  switch (mode)
  {
    case display_date_full:
      ddfw.Update(now);
      break;
    case display_date:
      ddw.Update(now);
      break;
    default:
      {
        TEMP_T temp_now;
        
        get_temp(&temp_now);
        temp.Update(temp_now);
      }
      break;
  }
}

int count;

/** 
 * setup
 */
void setup() {
  // Initialise the TFT screen.
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_DARKGREEN);
  Serial.begin(9600);

  // Initialise the touch panel.
  touch.begin(240, 320);
  touch.setCalibration(248, 1700, 1743, 309);
  touch.setRotation(XPT2046::ROT270);
  touch.powerDown();

  // I2C initialisation for the RTC.
  Wire.begin();

  // Just pause for a bit.
  tft.drawCentreString("Intialising...", 160, 103, 4);
  delay(5000);

  DisplayMain(dm);
  Serial.println("Setup Complete");
  delay(50);
  
  //dd.Display(now);
  //dow.Display(now);
  count = 0;
}

void loop() {
  DisplayUpdate(dm);
  
  //dd.Update(now);
  //dow.Update(now);

  if (touch.isTouching())
  {
    if (count == 0)
      beepOn();
    else if (count >= 1)
      beepOff();
    count +=1;
  }
  else
  { 
    beepOff();
    if (count >= 20 ) // More than a second before release.
    {  
      TM_T now;

      get_date_time(&now); 
         
      tft.fillScreen(ILI9341_BLACK);
      Serial.println("SetTime>");
      Serial.flush();
      SetTime st_ctrl(&tft, &touch);
      Serial.println("SetTime Display");
      Serial.flush();
      st_ctrl.Display(now); 
      Serial.println("SetTime Update");
      Serial.flush();
      st_ctrl.Update(now);
      Serial.println("<SetTime");
      Serial.flush();

      tft.fillScreen(ILI9341_BLACK);
      SetDate sd_ctrl(&tft, &touch);
      sd_ctrl.Display(now);
      sd_ctrl.Update(now); 

      DisplayMain(dm);
    }
    else if (count > 0) // Less then a second, rotate the bottom part of the main display.
    {
      dm = (dm + 1) % display_last;
      DisplayMain(dm, false);
    }
    count = 0;
  }
  
  delay(50);
}
