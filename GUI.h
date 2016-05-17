#ifndef DIGITAL_CLOCK_GUI_
#define DIGITAL_CLOCK_GUI_

#include <Adafruit_GFX_AS.h>    // Core graphics library, with extra fonts.
#include <Adafruit_ILI9341_STM.h> // STM32 DMA Hardware-specific library

// Based on size 7 LCD Font
#define BTN_W 34
#define BTN_H 34
#define DGT_W 34
#define DGT_H 48
#define CLN_W 14
#define CLN_H 48

// Based on size 6 Font
#define DGT6_W 27
#define DGT6_H 48
#define FS6_W 15
#define FS6_H 48

class Component {
protected:
  Adafruit_ILI9341_STM* tft;
  int x;
  int y;
  int fgc;
  int bgc;
  const int font_width[8] = { 0, 0, 8, 0, 14, 0, 27, 34 };
  const int font_height[8] = { 0, 0, 16, 0, 26, 0, 48, 48 };
public: 
  Component(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos);
  Component();
  virtual void Draw() = 0;
  void setScreen(Adafruit_ILI9341_STM* screen); 
  void setColor(int foreground, int background);
  void setPosition(int x_pos, int y_pos);
};

class Digit : public Component { 
  int val;
  int fntsz;
public:
  Digit(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int font_size,
    int initial_value
    );
  Digit();
  void setValue(int value);
  void Update(int value);
  void setFontSize(int font_size);
  void Draw();
};

class Colon : public Component {
  int fntsz;
public:
  Colon(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int font_size
    );
  Colon();
  void setFontSize(int font_size);
  void Draw();       
};

class Fullstop : public Component {
  int fntsz;
public:
  Fullstop(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int font_size
    );
  Fullstop();
  void setFontSize(int font_size);
  void Draw();       
};

class DoubleDigit : public Component {
  int val;
  int fntsz;
  bool lz;

public:
  DoubleDigit(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int font_size = 6,
    int value = 0,
    bool leading_zero = true
    );
  DoubleDigit();
  void setValue(int value);  
  void Update(int value);
  void setFontSize(int font_size);
  void showLeadingZero(bool show);
  void Draw();
};

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
  MonthString(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int initial_month
    );  
  MonthString();
  void setMonth(int new_month);  
  void Update(int new_month);
  void Draw();
};

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
  OrdinalString(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int initial_day = 1,
    int font_size = 4
    );
  OrdinalString(); 
  void setDay(int new_day);  
  void Update(int new_day);
  void setFontSize(int font_size);
  void Draw();
};

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
  WeekDay(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int initial_day = 1
    );
  WeekDay(); 
  void setDay(int new_day);  
  void Update(int new_day);
  void Draw();
};

class Button: public Component 
{
  int fntsz;
  char* bttntxt;
  int bttnw;
  int bttnh;
public:
  Button(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int width,
    int height,
    char* text
    );
  Button();
  Component* Press(int x_pos, int y_pos);
  void Release();
  void setFontSize(int font_size);
  void setWidthHeight(int width, int height);
  void setText(char *text);
  void Draw();
};

#endif // DIGITAL_CLOCK_GUI


