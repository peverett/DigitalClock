#include "GUI.h"

/**
 * Component class methods - this is the base class.
 */

Component::Component(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos)
: tft(screen), x(x_pos), y(y_pos)
{
  fgc = ILI9341_WHITE;
  bgc = ILI9341_BLACK;
}
 
Component::Component()
{
  tft = NULL;
  x = 0;
  y = 0;
  fgc = ILI9341_WHITE;
  bgc = ILI9341_BLACK;
}

void Component::setScreen(Adafruit_ILI9341_STM* screen)
{ 
  tft=screen; 
}

void Component::setColor(int foreground, int background)
{
  fgc=foreground;
  bgc=background;
}

void Component::setPosition(int x_pos, int y_pos)
{
  x = x_pos;
  y = y_pos;  
}

/**
 * Digit class methods.
 */

Digit::Digit(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int font_size,
    int initial_value
    )
  : Component(screen, x_pos, y_pos), fntsz(font_size), val(initial_value)
  {
  }

Digit::Digit(): Component()
{
  fntsz = 7;
  val = 0;
}

void Digit::setValue(int value)
{
  val = value;
}

void Digit::Update(int value) 
{
  if (value != val)
  {
    val = value;
    this->Draw();
  }
}

void Digit::setFontSize(int font_size)
{
  fntsz = font_size;
}

void Digit::Draw()
{
  if (tft)
  {
    tft->setTextColor(fgc, bgc);
    tft->drawChar( char(0x30 + val), x, y, fntsz);
  }
}

/**
 * Colon class - only displays a colon - static.
 */
 
Colon::Colon(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int font_size
    )
  : Component(screen, x_pos, y_pos), fntsz(font_size)
{ }

Colon::Colon() : Component()
{
  fntsz = 7; 
}

void Colon::Draw()
{
  if (tft) 
  {
    tft->setTextColor(fgc, bgc);
    tft->drawChar(':', x, y, fntsz);
  }
}

/**
 * Fullstop class - only displays a fullstop - static.
 */
 
Fullstop::Fullstop(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int font_size
    )
  : Component(screen, x_pos, y_pos), fntsz(font_size)
{ }

Fullstop::Fullstop() : Component()
{
  fntsz = 6; 
}

void Fullstop::Draw()
{
  if (tft) 
  {
    tft->setTextColor(fgc, bgc);
    tft->drawChar('.', x, y, fntsz);
  }
}
  
/**
 * Digit class methods.
 */

DoubleDigit::DoubleDigit(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int font_size,
    int initial_value,
    bool leading_zero
    )
  : Component(screen, x_pos, y_pos), fntsz(font_size), val(initial_value), lz(leading_zero)
  {
  }

DoubleDigit::DoubleDigit(): Component()
{
  fntsz = 6;
  val = 0;
  lz = true;
}

void DoubleDigit::setValue(int value)
{
  val = value;
}

void DoubleDigit::Update(int value) 
{
  if (value != val)
  {
    val = value;
    this->Draw();
  }
}

void DoubleDigit::setFontSize(int font_size)
{
  fntsz = font_size;
}

void DoubleDigit::showLeadingZero(bool show)
{
  lz = show;
}

void DoubleDigit::Draw()
{
  if (tft)
  {
    int tens = (val / 10);
     
    tft->setTextColor(fgc, bgc);
    if (lz || tens )
    {
      tft->drawChar( char(0x30 + tens), x, y, fntsz);
    }
    else // Blank out the previous digit with a rectangle.
    {
      tft->fillRect(x, y, font_width[fntsz], font_height[fntsz], bgc);
    }
    tft->drawChar( char(0x30 + (val % 10)), x+font_width[fntsz], y, fntsz);
  }
}

/** 
 *  Month String class.
 */
MonthString::MonthString(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int initial_month
    )
: Component(screen, x_pos, y_pos), month(initial_month)
{ }  
    
MonthString::MonthString()
: Component()
{
  month = 0;
}
  
void MonthString::setMonth(int new_month)
{
  month = new_month; 
}

void MonthString::Update(int new_month)
{
  if (month != new_month)
  {
    month = new_month;
    this->Draw();
  }

}

void MonthString::Draw()
{
  if (tft)
  {
    tft->setTextColor(fgc, bgc); 
    // Draw a rectangle to clear the previous month displayed (if there was one).
    // Font size is 4 - width is 14, height is 28.
    tft->fillRect(x, y, 140, 26, bgc);
    // Assume max string length is 140 (font 4 width = 14 * 10 char) - mid point is 70.
    tft->drawCentreString( (char *)month_str[month], x+70, y, 4);
  }
}

/**
 * Ordinal string class
 * Displays a the string "st", "nd", "rd" or "th" depending on the 'day', up to 31.
 */
OrdinalString::OrdinalString(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int initial_day,
    int font_size
    )
: Component(screen, x_pos, y_pos), day(initial_day), fntsz(font_size)
{}

OrdinalString::OrdinalString() : Component()
{
  day = 1;
  fntsz = 4;
}

void OrdinalString::setDay(int new_day)
{
  day = new_day; 
}

void OrdinalString::Update(int new_day)
{
  if (day != new_day)
  {
    day = new_day;
    this->Draw();
  }
}

void OrdinalString::setFontSize(int font_size)
{
  fntsz = font_size;
}

void OrdinalString::Draw()
{
  if (tft)
  {
    int index = 0;
    tft->setTextColor(fgc, bgc); 

    switch(day)
    {
      case 1: case 21: case 31:
        index = 1;
        break;
      case 2: case 22:
        index = 2;
        break;
      case 3: case 23:
        index = 3;
        break;
      default:
        break;
    }
    // Draw a blank box to erase what ever was there before.
    tft->fillRect(x, y, (font_width[fntsz]*2)+2, font_height[fntsz], bgc);
    tft->drawString((char *)ord_str[index], x, y, fntsz);    
  }
}

/**
 * WeekDay class - displays day of week as a string.
 */
WeekDay::WeekDay(
  Adafruit_ILI9341_STM* screen,
  int x_pos,
  int y_pos,
  int initial_day
  )
: Component(screen, x_pos, y_pos), day(initial_day)
{ }

WeekDay::WeekDay() : Component()
{
  day = 0;
}

void WeekDay::setDay(int new_day)
{
  day = new_day;  
}

void WeekDay::Update(int new_day)
{
  if (day != new_day)
  {
    day = new_day;
    this->Draw();
  }
}

void WeekDay::Draw()
{
  if (tft)
  {
    tft->setTextColor(fgc, bgc); 
    // Draw a rectangle to clear the previous month displayed (if there was one).
    // Font size is 4 - width is 14, height is 26.
    tft->fillRect(x, y, 140, 26, bgc);
    // Assume max string length is 140 (font 4 width = 10 * 10 + fudge - mid point is 70.
    tft->drawCentreString( (char *)day_str[day], x+70, y, 4);
  }
}

/**
 * Button class - simple button box with text. Ensure box is bigger than text.
 */
Button::Button(
    Adafruit_ILI9341_STM* screen,
    int x_pos,
    int y_pos,
    int width,
    int height,
    char* text
    )
: Component(screen, x_pos, y_pos), bttnw(width), bttnh(height), bttntxt(text), fntsz(4)
{ }

Button::Button() : Component() 
{
  bttnw = 0;
  bttnh = 0;
  bttntxt = NULL;
  fntsz = 4;
}

Component* Button::Press(int x_pos, int y_pos)
{
  if( (x_pos >= x) && (x_pos <= (x+bttnw)) &&
      (y_pos >= y) && (y_pos <= (y+bttnh)) ) 
  {
    this->Release();            // Trying not to repeat myself.
    return (Component *)this;
  }
  else 
  { 
    return NULL;   
  }
}

void Button::Release()
{
    // Swap foreground and background color (using the classic XOR trick).
    fgc ^= bgc;
    bgc ^= fgc;
    fgc ^= bgc;
    this->Draw();  
}

void Button::setFontSize(int font_size)
{
  fntsz = font_size;
}

void Button::setWidthHeight(int width, int height)
{
  bttnw = width;
  bttnh = height;
}

void Button::setText(char *text)
{
  bttntxt = text;
}

void Button::Draw()
{
  if (tft && bttntxt && bttnw && bttnh)
  {
    int half_width = x+(bttnw/2);

    // By default - Button colours are inverted.
    tft->setTextColor(bgc, fgc);
    tft->fillRect(x, y, bttnw, bttnh, fgc);
    tft->drawRect(x, y, bttnw, bttnh, bgc);
    tft->drawCentreString(
      bttntxt, x+(bttnw/2), 
      y+(bttnh/2)-(font_height[fntsz]/2),
      fntsz
      );
  }
}

