#ifndef DIGITAL_CLOCK_GUI_
#define DIGITAL_CLOCK_GUI_
/*!
 * \file
 *
 * \brief This module contains classes providing primitive GUI support for a
 * ILI9341 driven display. 
 *
 * - It assumes the display is 320 by 240 pixels.
 * - There is little validation, to save code space.
 */

#include <Adafruit_GFX_AS.h>        // Core graphics library, with extra fonts.
#include <Adafruit_ILI9341_STM.h>   // STM32 DMA Hardware-specific library

/*!
 * \defgroup font_defines Font size definitions.
 *
 * These defines are specific to the height and width of font 6 and font 7
 * digits, colons and fullstops.
 * \{
 */
#define BTN_H 34    /*!< LCD Font size 7 minimum button height. */
#define DGT_W 34    /*!< LCD Font size 7 digit width. */
#define DGT_H 48    /*!< LCD Font size 7 digit height. */
#define CLN_W 14    /*!< LCD Font size 7 colon width. */
#define CLN_H 48    /*!< LCD Font size 7 colon height. */

#define DGT6_W 27   /*!< Font size 6 digit width. */
#define DGT6_H 48   /*!< Font size 6 digit height. */
#define FS6_W 15    /*!< Font size 6 full stop width. */
#define FS6_H 48    /*!< Font size 6 full stop height. */
/*! \} */

/*!
 * Component GUI base class which provides a common interface and constant
 * defines for font widths. 
 */
class Component {
protected:
  Adafruit_ILI9341_STM* tft;    /*!< Pointer to ILI9341 display class. */
  int x;                        /*!< X co-ord of top left corner. */
  int y;                        /*!< Y co-ord of top left corner. */
  int fgc;                      /*!< Forground colour. */
  int bgc;                      /*!< Background colour. */

  /*! Font widths - only font size 2, 4, 6 and 7 are valid - others are zero.*/
  const int font_width[8] = { 0, 0, 8, 0, 14, 0, 27, 34 };
  /*! Font heights - only font size 2, 4, 6 and 7 are valid. */
  const int font_height[8] = { 0, 0, 16, 0, 26, 0, 48, 48 };

public: 
  /*!
   * \brief Component class constructor.
   *
   * \param screen Pointer to ILI9341 screen instance.
   * \param x_pos X position of the top left corner of the component.
   * \param y_pos Y position of the top left corner of the component.
   */
  Component(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos);

  /*! 
   * \brief Default Component class constructor.
   */
  Component();

  /*!
   * \brief Draws the graphics component on the display.
   */
  virtual void Draw() = 0;
  
  /*!
   * \brief Sets the ILI9341 screen instance.
   * \param screen Pointer to ILI9341 screen instance.
   */
  void setScreen(Adafruit_ILI9341_STM* screen); 

  /*!
   * \brief Set the components foreground and background colours.
   *
   * By default these are:
   *    - Foreground - ILI9341_WHITE
   *    - Background - ILI9341_BLACK
   *
   * \param foreground Foreground colour to set.
   * \param foreground Background colour to set.
   */
  void setColor(int foreground, int background);

  /*!
   * \brief Sets the X and Y position of the top left corner of the component.
   *
   * \param x_pos X position of the top left corner of the component.
   * \param y_pos Y position of the top left corner of the component.
   */
  void setPosition(int x_pos, int y_pos);
};

/*!
 * \Brief Digit class.
 *
 * Draws a Digit in the range 0 to 9. Font size 7 of the Arduino GFX AS class
 * is a 7-segment display of digits with colons and full stops and this class
 * is designed to display that although it will also display the smaller font
 * digits too.
 */
class Digit : public Component { 
  int val;
  int fntsz;
public:
  /*! 
   * Digit class constructor.
   *
   * \param screen Pointer to ILI9341 screen instance.
   * \param x_pos X position of the top left corner of the component.
   * \param y_pos Y position of the top left corner of the component.
   * \param font_size Font size to use, only 2, 4, 6 and 7 are supported. 
   *        defaults to font size 7.
   * \param initial_value Initial digit value, 0 to 9. Defaults to 0.
   */
  Digit(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int font_size = 7,
    int initial_value = 0
    );

  /*!
   * \brief Default Digit class constructor
   * 
   * Defaults the font size to 7 and the initial value to 0.
   */
  Digit();

  /*! 
   * Set the value of the digit. 
   *
   * \param value Value to set the digit to in the range 0 to 9.
   */
  void setValue(int value);

  /*! 
   * Draw the digit but only if the value passed is different than the current
   * value.
   *
   * \param value New digit value in range 0 to 9.
   */
  void Update(int value);

  /*!
   * Set the font size.
   Acer Aspire V Nitro*
   * \param font_size Font size to use, only 2, 4, 6 and 7 are supported.
   */
  void setFontSize(int font_size);
  
  /*! 
   * Draw the digit on the screen.
   */
  void Draw();
};

/*!
 * \brief Colon class
 *
 * Literally only draws a colon ':'.
 */
class Colon : public Component {
  int fntsz;
public:
  /*! 
   * Colon class constructor.
   *
   * \param screen Pointer to ILI9341 screen instance.
   * \param x_pos X position of the top left corner of the component.
   * \param y_pos Y position of the top left corner of the component.
   * \param font_size Font size to use, only 2, 4, 6 and 7 are supported.
   */
  Colon(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int font_size
    );

  /*!
   * Default Colon class constructor.
   *
   * Defaults the font size to 7.
   */
  Colon();

  /*!
   * Set the font size.
   *
   * \param font_size Font size to use, only 2, 4, 6 and 7 are supported.
   */
  void setFontSize(int font_size);

  /*! 
   * Draw the colon on the screen.
   */
  void Draw();       
};

/*!
 * \brief Fullstop class - literally just draws a full stop.
 */
class Fullstop : public Component {
  int fntsz;
public:
  /*! 
   * Fullstop class constructor.
   *
   * \param screen Pointer to ILI9341 screen instance.
   * \param x_pos X position of the top left corner of the component.
   * \param y_pos Y position of the top left corner of the component.
   * \param font_size Font size to use, only 2, 4, 6 and 7 are supported.
   */
  Fullstop(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int font_size
    );

  /*!
   * Default Fullstop class constructor.
   *
   * Defaults the font size to 7.
   */
  Fullstop();

  /*!
   * Set the font size.
   *
   * \param font_size Font size to use, only 2, 4, 6 and 7 are supported.
   */
  void setFontSize(int font_size);

  /*! 
   * Draw the fullstop on the screen.
   */
  void Draw();       
};

/*!
 * \brief DoubleDigit class.
 *
 * Displays a double digit value, range 0 to 99. Can be set to show a leading
 * 0 or a space if the value is in the range 0 to 9.
 */
class DoubleDigit : public Component {
  int val;
  int fntsz;
  bool lz;

public:
  /*! 
   * \brief DoubleDigit class constructor.
   *
   * \param screen Pointer to ILI9341 screen instance.
   * \param x_pos X position of the top left corner of the component.
   * \param y_pos Y position of the top left corner of the component.
   * \param font_size Font size to use, only 2, 4, 6 and 7 are supported. 
   *        defaults to font size 6.
   * \param initial_value Initial digit value, 0 to 99. Defaults to 0.
   * \param leading_zero Set to 'true' to show a leading zero if the
   *        value is less than 10. By default this is set to 'true'.
   */
  DoubleDigit(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int font_size = 6,
    int value = 0,
    bool leading_zero = true
    );

  /*
   * \brief Default DoubleDigit class constructor.
   *
   * By default, font is 6, value is 0 and display leading zero is 'true'.
   */
  DoubleDigit();

  /*!
   * \brief Set the value.
   *
   * \param value New value to set.
   */
  void setValue(int value);  

  /*! 
   * Draw the DoubleDigit but only if the value passed is different than the
   * current value.
   *
   * \param value New digit value in range 0 to 9.
   */
  void Update(int value);

  /*!
   * \brief Set the font size.
   *
   * \param font_size Font size to use, only 2, 4, 6 and 7 are supported.
   */
  void setFontSize(int font_size);

  /*!
   * \brief Show a leading 0 when the value of the double digit is less than
   * 10.
   *
   * \param show Set to 'true' to display the leading 0. Otherwise a space is
   * displayed instead.
   */
  void showLeadingZero(bool show);
  
  /*! 
   * Draw the DoubleDigit on the screen.
   */
  void Draw();
};

/*!
 * \brief MonthString class
 *
 * Displays the current month as a string. The month is set as an integer,
 * in the range 0 (January) through to 11 (December).
 */
class MonthString: public Component {
  int month;
  const char month_str[12][12] = {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
  };

public:
  /*!
   * \brief MonthString constructor
   *
   * \param screen Pointer to ILI9341 screen instance.
   * \param x_pos X position of the top left corner of the component.
   * \param y_pos Y position of the top left corner of the component.
   * \param font_size Font size to use, only 2, 4, 6 and 7 are supported. 
   *        defaults to font size 6.
   * \param initial_month Integer value for month in range 0 (January) through
   *        to 11 (December).
   */
  MonthString(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int initial_month
    );  
  
  /*!
   * \brief Default MonthString constructor.
   * 
   * By default, the month is set to 0 (January).
   */
  MonthString();

  /*!
   * \brief Set the month value.
   *
   * \param new_month Integer value for month in range 0 (January) through
   *        to 11 (December).
   */
  void setMonth(int new_month);  

  /*! 
   * \brief Display the month string but only if the value passed is different
   * than current value.
   *
   * \param value new_month New month value in range 0 (January) to 11 
   * (December).
   */
  void Update(int new_month);

  /*! 
   * \brief Display the month string on the screen.
   */
  void Draw();
};

/*!
 * \brief OrdinalString class.
 *
 * Depending on the unit value of the number set, this class will display the
 * correct ordinal string for that number e.g.
 *      + 1 - displays "st" i.e. 1st
 *      + 2 - displays "nd" i.e. 2nd
 *      + 3 - displays "rd" i.e. 3rd
 *      + any other number - displays "th" e.g. "4th"
 */
class OrdinalString : public Component
{
  int day;
  int fntsz;
  const char ord_str[4][3] = {
    "th",
    "st",
    "nd",
    "rd"
  };

public:
   /*!
   * \brief OrdinalString constructor.
   *
   * \param screen Pointer to ILI9341 screen instance.
   * \param x_pos X position of the top left corner of the component.
   * \param y_pos Y position of the top left corner of the component.
   * \param intial_day Initial day value 1 to 31.
   * \param font_size Font size to use, only 2, 4, 6 and 7 are supported. 
   *        defaults to font size 4.
   */
  OrdinalString(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int initial_day = 1,
    int font_size = 4
    );

  /*! 
   * \brief Default OrdinalString constructor.
   *
   * Defaults font size to 4 and day to 1.
   */
  OrdinalString(); 

  /*! 
   * \brief set day value to display ordinal for.
   *
   * \param new_day The new day value in the range 1 to 31.
   */
  void setDay(int new_day);  

  /*!
   * \brief Display the ordinal string but only if the new_day value is
   * different than the current day value.
   *
   * \param new_day The new day value in the range 1 to 31.
   */
  void Update(int new_day);

  /*!
   * \brief Set the font size.
   *
   * \param font_size The new font size, valid values are 2, 4, 6 and 7.
   */
  void setFontSize(int font_size);

  /*!
   * \Brief Draw the ordinal string on the screen.
   */
  void Draw();
};

/*!
 * \brief WeekDay class
 */
class WeekDay : public Component
{
  int day;
  const char day_str[7][10] = {
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
  };
public:
  /*!
   * \brief
   * WeekDay class constructor.
   *
   * \param screen Pointer to ILI9341 screen instance.
   * \param x_pos X position of the top left corner of the component.
   * \param y_pos Y position of the top left corner of the component.
   * \param initial_day Integer value for the day in the week, range 0 (Monday) 
   *        to 6 (Sunday). Defaults to 0 (Monday).
   */
  WeekDay(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int initial_day = 0
    );
  
  /*!
   * \brief Default WeekDay class constructor.
   *
   * Defaults the day of week to 0 (Sunday).
   */
  WeekDay(); 
  
  /*!
   * \brief Set a new week day.
   *
   * \param new_day Day of week in range 0 (Monday) to 6 (Sunday).
   */
  void setDay(int new_day);  

  /*!
   * \brief if the new_day of week is different than the current day then 
   * update the value and display it.
   *
   * \param new_day New day of week value in range 0 (Monday) to 6 (Sunday).
   */
  void Update(int new_day);

  /*!
   * \brief Draw the day of week string on the screen.
   */
  void Draw();
};

/*!
 * \brief Button class.
 *
 * Draws a button box with the specified text centred inside it. The font size
 * should always allow the button text string to fit inside the box bondary.
 *
 * The Button is shown in inverse colours. When 'pressed' the colours will 
 * invert until the 'release' function is called.
 */
class Button: public Component 
{
  int fntsz;
  char* bttntxt;
  int bttnw;
  int bttnh;
public:

  /*!
   * \brief Button constructor.
   *
   * Font size cannot be specified with the constructor and defaults to 4. The
   * method 'setFontSize' can be used to set the font independantly once the
   * class is instantiated.
   *
   * \param screen Pointer to ILI9341 screen instance.
   * \param x_pos X position of the top left corner of the Button box.
   * \param y_pos Y position of the top left corner of the Button box.
   * \param width The width of the button box.
   * \param height The height of the button box.
   * \param text Null terminated char string to be displayed in the box.
   */
  Button(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int width,
    int height,
    char* text
    );

  /*!
   * \brief Default Button constructor.
   */
  Button();

  /*!
   * \brief Called to determine if the button is has been pressed.
   *
   * If the co-ordinates (X, Y) passed to this method are within the Button's
   * box boundary then the button is 'pressed'. The colour of the button box
   * and text are inverted to visually show this.
   *
   * \param x_pos X position co-ordinate.
   * \param y_pos Y position co-ordinate.
   *
   * \returns Pointer to this instance of the Button class.
   */
  Component* Press(int x_pos, int y_pos);

  /*!
   * \brief Called to indicate the button was 'released'.
   */
  void Release();

  /*!
   * \brief Set the button text font size.
   *
   * \param font_size The new font size, valid font sizes are 2, 4, 6 and 7.
   */
  void setFontSize(int font_size);

  /*!
   * \brief Set the Button width and height.
   *
   * \param width New width for the Button box.
   * \param height New height for the Button box.
   */
  void setWidthHeight(int width, int height);

  /*!
   * \brief Set the text to be displayed in the button.
   *
   * \param text Null terminated char string to be displayed.
   */
  void setText(char *text);

  /*!
   * Draw the Button box and text to the screen.
   */
  void Draw();
};

#endif // DIGITAL_CLOCK_GUI

