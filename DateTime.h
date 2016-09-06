#ifndef DATETIME_
#define DATETIME_
/*!
 * \file
 *
 * \brief DateTime display widgets using the basic GUI components.
 * 
 * Widgets are either full screen (320x240) or half screen (320x120)
 */

#include <XPT2046.h>

#include "DS3231_RTC.h"
#include "GUI.h"

/*!
 * \brief Main display time half-widget. Display the time as a 6-digits.
 *
 * Format is HH:MM:SS.
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

  /*!
   * \brief Constructor.
   *
   * \param screen Pointer to an ILI9341 display class for the TFT.
   * \param x_pos Top left corner X co-ordinate.
   * \param y_pos Top left conrer Y co-ordinate.
   */
  DisplayTime(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos);

  /*!
   * \brief Display the time widget, drawing it completely.
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Display(TM_T now);

  /*!
   * \brief Update the time widget display.
   *
   * Only update the part of the time display that has changed since the last
   * update.
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Update(TM_T now);
};

/*
 * \brief DisplayTimeWidget
 *
 * The only purpose of this widget is to centre a DisplayTime component in a
 * 320 x 120 half of the screen. It fills that space (-1 pixel each side) with
 * a black rectangle first to blank out what ever was there before.
 */
class DisplayTimeWidget: public DisplayTime
{
  Adafruit_ILI9341_STM* tft;
  int ox;
  int oy;
public:

  /*!
   * \brief Constructor.
   *
   * \param screen Pointer to an ILI9341 display class for the TFT.
   * \param x_pos Top left corner X co-ordinate.
   * \param y_pos Top left conrer Y co-ordinate.
   */
  DisplayTimeWidget(Adafruit_ILI9341_STM* screen, int x_pos=0, int y_pos=0);

  /*!
   * \brief Display the time widget, drawing it completely.
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Display(TM_T now);
};

/*! 
 * \brief DisplayDateFull Class
 *
 * Displays the date in a full, formal format:
 *
 * Day of week (Monday, Tuesday, etc)
 * Day of month with ordinal e.g. 24th
 * Month (January, February, etc).
 * Full year e.g. 2016
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

  /*!
   * \brief Constructor.
   *
   * \param screen Pointer to an ILI9341 display class for the TFT.
   * \param x_pos Top left corner X co-ordinate.
   * \param y_pos Top left conrer Y co-ordinate.
   */
  DisplayDateFull(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos);

  /*!
   * \brief Display the date, drawing it completely.
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Display(TM_T now);

  /*!
   * \brief Update the date display.
   *
   * Only update the part of the date display that has changed since the last
   * update.
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Update(TM_T now);
};

/*
 * \brief DisplayDateFullWidget
 *
 * The only purpose of this widget is to centre a DisplayFullDate component in
 * a 320 x 120 half of the screen. It fills that space (-1 pixel each side)
 * with a black rectangle first to blank out what ever was there before.
 */
class DisplayDateFullWidget : public DisplayDateFull
{
  Adafruit_ILI9341_STM* tft;
  int ox;
  int oy;
public:

  /*!
   * \brief Constructor.
   *
   * \param screen Pointer to an ILI9341 display class for the TFT.
   * \param x_pos Top left corner X co-ordinate.
   * \param y_pos Top left conrer Y co-ordinate.
   */
  DisplayDateFullWidget(Adafruit_ILI9341_STM* screen, int x_pos=0, int y_pos=0);

  /*!
   * \brief Update the full date widget display.
   *
   * Only update the part of the date display that has changed since the last
   * update.
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Display(TM_T now);
};

/*! 
 * \brief DisplayDate Class
 *
 * Displays the date in a 8-digit format e.g. DD.MM.YYYY:
 *
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

  /*!
   * \brief Constructor.
   *
   * \param screen Pointer to an ILI9341 display class for the TFT.
   * \param x_pos Top left corner X co-ordinate.
   * \param y_pos Top left conrer Y co-ordinate.
   */
  DisplayDate(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos);

  /*!
   * \brief Display the date, drawing it completely.
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Display(TM_T now);

  /*!
   * \brief Update the date display.
   *
   * Only update the part of the date display that has changed since the last
   * update.
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Update(TM_T now);
};

/*!
 * \brief DayOfWeek display component
 *
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

  /*!
   * \brief Constructor.
   *
   * \param screen Pointer to an ILI9341 display class for the TFT.
   * \param x_pos Top left corner X co-ordinate.
   * \param y_pos Top left conrer Y co-ordinate.
   */
  DayOfWeek(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos);

  /*!
   * \brief Display the DayOfWeek component, drawing it completely.
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Display(TM_T now);
  
  /*!
   * \brief Update the DayOfWeek display.
   *
   * Only update the part of the DayOfWeek display that has changed since the
   * last update.
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Update(TM_T now);
};

/*! 
 * \brief DisplayDateWidget class
 *
 * Displays the date in 8-digit format with the day of week as a highlighted
 * button  above.
 */
class DisplayDateWidget : public DisplayDate, DayOfWeek
{
  Adafruit_ILI9341_STM* tft;
  int ox;
  int oy;
public:
  /*!
   * \brief Constructor.
   *
   * \param screen Pointer to an ILI9341 display class for the TFT.
   * \param x_pos Top left corner X co-ordinate.
   * \param y_pos Top left conrer Y co-ordinate.
   */
  DisplayDateWidget(Adafruit_ILI9341_STM* screen, int x_pos=0, int y_pos=0);

  /*!
   * \brief Display the Date widget, drawing all components.
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Display(TM_T now);

  /*!
   * \brief Update the Date widget display.
   *
   * Only update the part or components that has changed since the last
   * update.
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Update(TM_T now);
};

/*!
 * \brief DisplayTemp class
 *
 * Displays the Temperature read from the DS3231 RTC module. The format is
 * double digit and half degree e.g. 24.0 24.5 25.0 etc.
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
  /*!
   * \brief Constructor.
   *
   * \param screen Pointer to an ILI9341 display class for the TFT.
   * \param x_pos Top left corner X co-ordinate.
   * \param y_pos Top left conrer Y co-ordinate.
   */
  DisplayTemp(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos);
  
  /*!
   * \brief Display the temp widget, drawing it completely.
   *
   * \param now TEMP_T structure containing the current date and time.
   */
  void Display(TEMP_T temperature);

  /*!
   * \brief Update the temp widget display.
   *
   * Only update the part of the temp display that has changed since the last
   * update.
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Update(TEMP_T temperature); 
};

/*!
 * \brief Half screen Temp display widget.
 *
 * Positions the temperature display so that it is centered in a half screen
 * 320 x 120.
 */
class DisplayTempWidget : public DisplayTemp
{
  Adafruit_ILI9341_STM* tft;
  int ox;
  int oy;
public:

  /*!
   * \brief Constructor.
   *
   * \param screen Pointer to an ILI9341 display class for the TFT.
   * \param x_pos Top left corner X co-ordinate.
   * \param y_pos Top left conrer Y co-ordinate.
   */
  DisplayTempWidget(Adafruit_ILI9341_STM* screen, int x_pos=0, int y_pos=0);

  /*!
   * \brief Display the temp half screen widget, drawing it completely.
   *
   * \param now TEMP_T structure containing the current date and time.
   */
  void Display(TEMP_T temperature);
};

/*!
 * \brief SetTime full screen control widget.
 *
 * Full screen control widget for setting the time fields of the TM_T 
 * structure. If the user presses the 'Ok' button, the time changes are
 * written to the RTC. If 'Cancel' then they are forgotten.
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

  /*!
   * \brief Constructor.
   *
   * No need for X,Y coordinates as this is a full screen widget.
   *
   * \param screen Pointer to an ILI9341 display class for the TFT.
   * \param touch_screen Pointer to the XPT2046 touch class.
   */
  SetTime(Adafruit_ILI9341_STM* screen, XPT2046* touch_screen);

  /*!
   * \brief Display the SetTime widget, drawing it completely.
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Display(TM_T now);

  /*!
   * \brief Update the time widget display.
   *
   * Goes into a control loop, reading the touchscreen in a loop and only
   * exits if the 'Ok' or 'Cancel' button are pressed. 
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Update(TM_T now);
};

/*!
 * \brief SetDate full screen control widget.
 *
 * Full screen control widget for setting the date fields of the TM_T 
 * structure. If the user presses the 'Ok' button, the date changes are
 * written to the RTC. If 'Cancel' then they are forgotten.
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
  /*!
   * \brief Update the date widget display.
   *
   * Goes into a control loop, reading the touchscreen in a loop and only
   * exits if the 'Ok' or 'Cancel' button are pressed. 
   *
   * \param now TM_T structure containing the current date and time.
   */
  SetDate(Adafruit_ILI9341_STM* screen, XPT2046* touch_screen);
  
  /*!
   * \brief Display the SetDate widget, drawing it completely.
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Display(TM_T now);

  /*!
   * \brief Update the SetDate widget display.
   *
   * Goes into a control loop, reading the touchscreen in a loop and only
   * exits if the 'Ok' or 'Cancel' button are pressed. 
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Update(TM_T now);
};

/*!
 * \brief SetDayOfWeek full screen control widget.
 *
 * Full screen control widget for setting the Week Day field of the TM_T 
 * structure. If the user presses the 'Ok' button, the date changes are
 * written to the RTC. If 'Cancel' then they are forgotten.
 *
 * The days are displayed as buttons and by pressing and highlighting the 
 * 'day' button - the day of week is selected.
 */
class SetDayOfWeek
{
  const static int MAX_BTTNS = 9;
  Button mo, tu, we, th, fr, sa, su;
  int ox;
  int oy;
  int today;
  Button bok, bcancel;
  Button *bttns[MAX_BTTNS];
  Adafruit_ILI9341_STM* tft;
  XPT2046* touch;
public:
  /*!
   * \brief Constructor.
   *
   * No need for X,Y coordinates as this is a full screen widget.
   *
   * \param screen Pointer to an ILI9341 display class for the TFT.
   * \param touch_screen Pointer to the XPT2046 touch class.
   */
  SetDayOfWeek(Adafruit_ILI9341_STM* screen, XPT2046* touch_screen);

  /*!
   * \brief Display the SetDayOfWeek widget, drawing it completely.
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Display(TM_T now);

  /*!
   * \brief Update the SetDayOfWeek widget display.
   *
   * Goes into a control loop, reading the touchscreen in a loop and only
   * exits if the 'Ok' or 'Cancel' button are pressed. 
   *
   * \param now TM_T structure containing the current date and time.
   */
  void Update(TM_T now);
};

/*!
 * \brief SetUpScreen Is the man menu screen for setup configuration.
 *
 * Full screen display. This function displays buttons for each configuration
 * option and goes into a display loop until 'Done' is pressed, when it 
 * returns to the main 'display' functionality.
 *
* \param screen Pointer to an ILI9341 display class for the TFT.
* \param touch_screen Pointer to the XPT2046 touch class.
 */
void SetUpScreen(Adafruit_ILI9341_STM& tft, XPT2046& touch);

class DisplayAlarm
{
    const static int MAX_COMPS=7;
    int ox;
    int oy;
    Digit ht, hu, mt, mu;
    Colon c1;
    Button on, off;
    Component *comps[MAX_COMPS];
public:

    /*!
     * \brief Constructor
     * \param screen Pointer to an ILI9341 display class for the TFT.
     * \param x_pos Top left corner X co-ordinate.
     * \param y_pos Top left conrer Y co-ordinate.
     */
    DisplayAlarm(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos);

    /*!
     * \brief Display the alarm widget, drawing it completely.
     *
     * \param alm ALARM_T structure containing alarm information.
     */
    void Display(ALARM_T alarm);

    /*!
     * \brief Update the alarm widget display.
     *
     * Only update the part of the alarm display that has changed since the last
     * update.
     *
     * \param alm ALARM_T structure containing alarm information.
     */
    void Update(ALARM_T alarm);
};

/*! 
 * \brief DisplayAlarmWidget class
 *
 * Displays the Alarm and it's status (on or off)
 */
class DisplayAlarmWidget : public DisplayAlarm
{
  Adafruit_ILI9341_STM* tft;
  int ox;
  int oy;
public:
  /*!
   * \brief Constructor.
   *
   * \param screen Pointer to an ILI9341 display class for the TFT.
   * \param x_pos Top left corner X co-ordinate.
   * \param y_pos Top left conrer Y co-ordinate.
   */
  DisplayAlarmWidget(
          Adafruit_ILI9341_STM* screen, 
          int x_pos=0, 
          int y_pos=0
          );

  /*!
   * \brief Display the alarm widget, drawing all components.
   *
   * \param alarm_id Which alarm to display #ALARM1 or #ALARM2.
   * \param enabled Non-zero indicates the alarm is ON.
   * \param alarm ALARM_T structure containing the alarm hour and minute.
   */
  void Display(
        uint8_t alarm_id, 
        uint8_t enabled, 
        ALARM_T alarm
        );

};

#endif
