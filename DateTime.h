#ifndef DATETIME_
#define DATETIME_

#include "DS3231_RTC.h"
#include "GUI.h"
#include <XPT2046.h>

/**
 * Class for displaying the time, as a segmented display 
 */
class DisplayTime 
{
  const static int MAX_COMPS=8;
  int ox;
  int oy;
  Digit ht, hu, mt, mu, st, su;
  Colon c1, c2;
  Component *comps[MAX_COMPS];
public:
  DisplayTime(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos);
  void Display(TM_T now);
  void Update(TM_T now);
};

/*
 * The only purpose of this Widgit is to position the Time Display in the middle of
 * a 320 x 120 area.
 */
class DisplayTimeWidget: public DisplayTime
{
  Adafruit_ILI9341_STM* tft;
  int ox;
  int oy;
public:
  DisplayTimeWidget(Adafruit_ILI9341_STM* screen, int x_pos=0, int y_pos=0);
  void Display(TM_T now);
};

/**
 * Class for displaying the date in a formal format with
 * string for weekday and month. Size 4 font.
 */
class DisplayDateFull
{
  const static int MAX_COMPS=6;
  int ox;
  int oy;
  DoubleDigit dd;
  OrdinalString os;
  MonthString ms;
  DoubleDigit yu;
  DoubleDigit yl;
  WeekDay wd;
  Component *comps[MAX_COMPS];
public:
  DisplayDateFull(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos);
  void Display(TM_T now);
  void Update(TM_T now);
};

/**
 * Half screen widget for the DisplayDateFull class.
 */
class DisplayDateFullWidget : public DisplayDateFull
{
  Adafruit_ILI9341_STM* tft;
  int ox;
  int oy;
public:
  DisplayDateFullWidget(Adafruit_ILI9341_STM* screen, int x_pos=0, int y_pos=0);
  void Display(TM_T now);
};

/**
 * Class for displaying the date in Font 6 digits in DD.MM.YYYY format.
 */
class DisplayDate
{
  const static int MAX_COMPS=6;
  int ox;
  int oy;
  DoubleDigit md;
  DoubleDigit mn;
  DoubleDigit yu;
  DoubleDigit yl;
  Fullstop fs1, fs2;
  Component *comps[MAX_COMPS];
public:
  DisplayDate(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos);
  void Display(TM_T now);
  void Update(TM_T now);
};

/**
 * Class for indicating the weekday by highlighting day in shortform e.g.
 * 
 *    Mo  Tu  We  Th  Fr  Sa  Su
 *        --
 *        
 * Uses the Button widget but they don't work as buttons.
 */
class DayOfWeek
{
  const static int MAX_BTTNS = 7;
  Button mo, tu, we, th, fr, sa, su;
  int ox;
  int oy;
  Button *bttns[MAX_BTTNS];
  int today;
public:
  DayOfWeek(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos);
  void Display(TM_T now);
  void Update(TM_T now);
};

/**
 * Half screen widget for the DisplayDate class.
 * 
 * DIFFERENT FROM DisplayDateFull - displays date in digital format and also
 * the day of the week as buttons.
 */
class DisplayDateWidget : public DisplayDate, DayOfWeek
{
  Adafruit_ILI9341_STM* tft;
  int ox;
  int oy;
public:
  DisplayDateWidget(Adafruit_ILI9341_STM* screen, int x_pos=0, int y_pos=0);
  void Display(TM_T now);
  void Update(TM_T now);
};

/**
 * Class for displaying the temperature read from the DS3231 RTC module.
 */
class DisplayTemp
{
  DoubleDigit tmp;
  Digit hlfdgr;
  Fullstop fs;
  int ox;
  int oy;
  Adafruit_ILI9341_STM* tft;
public:
  DisplayTemp(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos);
  void Display(TEMP_T temperature);
  void Update(TEMP_T temperature); 
};

/**
 * Class for displaying the temperature as a half screen widget
 */
class DisplayTempWidget : public DisplayTemp
{
  Adafruit_ILI9341_STM* tft;
  int ox;
  int oy;
public:
  DisplayTempWidget(Adafruit_ILI9341_STM* screen, int x_pos=0, int y_pos=0);
  void Display(TEMP_T temperature);
};

/**
 * Class for setting the time - full screen contol widget.
 */
class SetTime
{
  const static int MAX_BTTNS=14;
  int ox;
  int oy;
  DisplayTime dt;
  Button htu, htd, huu, hud, mtu, mtd, muu, mud, stu, std, suu, sud;
  Button bok, bcancel;
  Button *bttns[MAX_BTTNS];
  Adafruit_ILI9341_STM* tft;
  XPT2046* touch;
public:
  SetTime(Adafruit_ILI9341_STM* screen, XPT2046* touch_screen);
  void Display(TM_T now);
  void Update(TM_T now);
};

/**
 * Class for setting the date - full screen contol widget.
 */
class SetDate
{
  const static int MAX_BTTNS=8;
  int ox;
  int oy;
  DisplayDate dd;
  Button mdu, mdd, mu, md, yu, yd;
  Button bok, bcancel;
  Button *bttns[MAX_BTTNS];
  Adafruit_ILI9341_STM* tft;
  XPT2046* touch;
public:
  SetDate(Adafruit_ILI9341_STM* screen, XPT2046* touch_screen);
  void Display(TM_T now);
  void Update(TM_T now);
};

/**
 * Full screen display of SetUp options as buttons.
 */
void SetUpScreen();

#endif
