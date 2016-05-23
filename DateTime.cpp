#include "DateTime.h"
#include "beep.h"

/*
 ***************************************************************************
 */

DisplayTime::DisplayTime(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos)
{
  ox = x_pos;
  oy = y_pos;

  comps[0] = &ht;
  comps[1] = &hu;
  comps[2] = &c1;
  comps[3] = &mt;
  comps[4] = &mu;
  comps[5] = &c2;
  comps[6] = &st;
  comps[7] = &su;
  
  for (int idx=0; idx < DisplayTime::MAX_COMPS; idx++)
  {
    comps[idx]->setScreen(screen);
  }
}

void DisplayTime::Display(TM_T now)
{
    int x = ox;
    int y = oy;

    ht.setPosition(x, y);
    ht.setValue(now.tm_hour / 10);
    hu.setPosition(x+=DGT_W, y);
    hu.setValue(now.tm_hour % 10);
    c1.setPosition(x+=DGT_W, y);
    mt.setPosition(x+=CLN_W, y);
    mt.setValue(now.tm_min / 10);
    mu.setPosition(x+=DGT_W, y);
    mu.setValue(now.tm_min % 10);
    c2.setPosition(x+=DGT_W, y);
    st.setPosition(x+=CLN_W, y);
    st.setValue(now.tm_sec / 10);
    su.setPosition(x+=DGT_W, y);
    su.setValue(now.tm_sec % 10); 

    for (int idx=0; idx < MAX_COMPS; idx++)
    {
      comps[idx]->Draw();
    }
}

void DisplayTime::Update(TM_T now)
{
    ht.Update(now.tm_hour / 10);
    hu.Update(now.tm_hour % 10);
    mt.Update(now.tm_min / 10);
    mu.Update(now.tm_min % 10);
    st.Update(now.tm_sec / 10);
    su.Update(now.tm_sec % 10);
}

/*
 ***************************************************************************
 */
 
DisplayTimeWidget::DisplayTimeWidget(
  Adafruit_ILI9341_STM* screen, 
  int x_pos, 
  int y_pos
  )
: DisplayTime(screen, x_pos+44, y_pos+36), tft(screen), ox(x_pos), oy(y_pos)
{ }

void DisplayTimeWidget::Display(TM_T now)
{
  tft->fillRect(ox+1, oy+1, 318, 118, ILI9341_BLACK);
  DisplayTime::Display(now);
}

/*
 ***************************************************************************
 */
 
DisplayDateFull::DisplayDateFull(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos) 
{
  ox = x_pos;
  oy = y_pos;

  comps[0] = &dd;
  comps[1] = &os;
  comps[2] = &ms;
  comps[3] = &yu;
  comps[4] = &yl;
  comps[5] = &wd;
  
  for (int idx=0; idx < DisplayDateFull::MAX_COMPS; idx++)
  {
    comps[idx]->setScreen(screen);
  }
}

void DisplayDateFull::Display(TM_T now)
{
  // Total width = 264
  dd.setPosition(ox, oy+70);
  dd.setValue(now.tm_mday);
  dd.setFontSize(4);
  dd.showLeadingZero(false);
  os.setPosition(ox+28, oy+70);
  os.setDay(now.tm_mday);
  os.setFontSize(2);
  ms.setPosition(ox+44, oy+70);
  ms.setMonth(now.tm_mon-1);
  yu.setPosition(ox+184, oy+70);
  yu.setValue(20);
  yu.setFontSize(4);
  yl.setPosition(ox+212, oy+70);
  yl.setValue(now.tm_year);
  yl.setFontSize(4);
  wd.setPosition(ox+50, oy+30);
  wd.setDay(now.tm_wday-1);

  for (int idx=0; idx < DisplayDateFull::MAX_COMPS; idx++)
    {
      comps[idx]->Draw();
    }
}

void DisplayDateFull::Update(TM_T now){
  dd.Update(now.tm_mday);
  os.Update(now.tm_mday); 
  ms.Update(now.tm_mon-1);
  yl.Update(now.tm_year);
  wd.Update(now.tm_wday-1);
}

/*
 ***************************************************************************
 */

DisplayDateFullWidget::DisplayDateFullWidget(
  Adafruit_ILI9341_STM* screen, 
  int x_pos, 
  int y_pos
)
: DisplayDateFull(screen, x_pos+40, y_pos), tft(screen), ox(x_pos), oy(y_pos)
{}

void DisplayDateFullWidget::Display(TM_T now)
{
  tft->fillRect(ox+1, oy+1, 318, 118, ILI9341_BLACK);
  DisplayDateFull::Display(now);
}

/*
 ***************************************************************************
 */

DisplayDate::DisplayDate(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos)
{
  ox = x_pos;
  oy = y_pos;

  comps[0] = &md;
  comps[1] = &fs1;
  comps[2] = &mn;
  comps[3] = &fs2;
  comps[4] = &yu;
  comps[5] = &yl;
  
  for (int idx=0; idx < DisplayDate::MAX_COMPS; idx++)
  {
    comps[idx]->setScreen(screen);
  }
}

void DisplayDate::Display(TM_T now)
{
  int x = ox;
  int y = oy;
  
  md.setPosition(x, y);
  md.setValue(now.tm_mday);
  md.setFontSize(6);
  fs1.setPosition(x+=(DGT6_W*2), y);
  mn.setPosition(x+=FS6_W, y);
  mn.setValue(now.tm_mon);
  mn.setFontSize(6);
  fs2.setPosition(x+=(DGT6_W*2), y);
  yu.setPosition(x+=FS6_W, y);
  yu.setValue(20);
  yu.setFontSize(6);
  yl.setPosition(x+=(DGT6_W*2), y);
  yl.setValue(now.tm_year);
  yl.setFontSize(6);

  for (int idx=0; idx < DisplayDate::MAX_COMPS; idx++)
  {
    comps[idx]->Draw();
  }
}

void DisplayDate::Update(TM_T now)
{
    md.Update(now.tm_mday);
    mn.Update(now.tm_mon);
    yl.Update(now.tm_year);
}

/*
 ***************************************************************************
 */

DayOfWeek::DayOfWeek(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos)
: ox(x_pos), oy(y_pos), today(0)
{
  bttns[0] = &mo; // Lines up with the tm_wday value from the RTC
  bttns[1] = &tu;
  bttns[2] = &we;
  bttns[3] = &th;
  bttns[4] = &fr;
  bttns[5] = &sa;
  bttns[6] = &su;

  for (int idx=0; idx < DayOfWeek::MAX_BTTNS; idx++)
  {
    bttns[idx]->setScreen(screen);
    bttns[idx]->setWidthHeight(20, 20);
    bttns[idx]->setFontSize(2);
  }
}

void DayOfWeek::Display(TM_T now)
{
  int x = ox;
  int y = oy;

  mo.setPosition(x, y);
  mo.setText("Mo");
  tu.setPosition(x+=40, y);
  tu.setText("Tu");
  we.setPosition(x+=40, y);
  we.setText("We");
  th.setPosition(x+=40, y);
  th.setText("Th");
  fr.setPosition(x+=40, y);
  fr.setText("Fr");
  sa.setPosition(x+=40, y);
  sa.setText("Sa");
  su.setPosition(x+=40, y);
  su.setText("Su");

  for (int idx=0; idx < DayOfWeek::MAX_BTTNS; idx++)
  {
    bttns[idx]->setColor(ILI9341_BLACK, ILI9341_WHITE); 
    bttns[idx]->Draw();  
  }

  // Highlight the actual day
  today = now.tm_wday;
  bttns[today-1]->Release();
}

void DayOfWeek::Update(TM_T now)
{
  if (today != now.tm_wday)
  {
    bttns[today-1]->Release();  // Un-highlight the current day.
    today = now.tm_wday;
    bttns[today-1]->Release();  // Now highlight the new day.
  }
}

/*
 ***************************************************************************
 */

DisplayDateWidget::DisplayDateWidget(
  Adafruit_ILI9341_STM* screen, 
  int x_pos, 
  int y_pos
  )
: DisplayDate(screen, x_pos+37, y_pos+62),
  DayOfWeek(screen, x_pos+30,  y_pos+20),
  tft(screen), ox(x_pos), oy(y_pos)
{}

void DisplayDateWidget::Display(TM_T now)
{
  tft->fillRect(ox+1, oy+1, 318, 118, ILI9341_BLACK);
  DisplayDate::Display(now);
  DayOfWeek::Display(now);
}

void DisplayDateWidget::Update(TM_T now)
{
  DisplayDate::Update(now);
  DayOfWeek::Update(now);
}

/*
 ***************************************************************************
 */

DisplayTemp::DisplayTemp(Adafruit_ILI9341_STM* screen, int x_pos, int y_pos)
: tft(screen), ox(x_pos), oy(y_pos)
{
  tmp.setScreen(screen);
  fs.setScreen(screen);
  hlfdgr.setScreen(screen);
}

void DisplayTemp::Display(TEMP_T temperature)
{
  int x = ox;
  int y = oy;
  
  tmp.setPosition(x, oy);
  tmp.setFontSize(6);
  tmp.setValue(temperature.temp_degrees);
  tmp.Draw();
  fs.setPosition(x+=(DGT6_W*2), oy);
  fs.Draw();
  hlfdgr.setPosition(x+=FS6_W, oy);
  hlfdgr.setFontSize(6);
  hlfdgr.setValue(temperature.temp_half);
  hlfdgr.Draw();

  // Text for degrees C
  tft->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft->drawString("O", x+=DGT6_W+11, oy, 2);
  tft->drawString("C", x+=8, oy, 4);  
}

void DisplayTemp::Update(TEMP_T temperature)
{
  tmp.Update(temperature.temp_degrees);
  hlfdgr.Update(temperature.temp_half);
}

/*
 ***************************************************************************
 */

DisplayTempWidget::DisplayTempWidget(
  Adafruit_ILI9341_STM* screen, 
  int x_pos,
  int y_pos
  )
: DisplayTemp(screen, x_pos+103, y_pos+36), tft(screen), ox(x_pos), oy(y_pos)
{}

void DisplayTempWidget::Display(TEMP_T temperature)
{
  tft->fillRect(ox+1, oy+1, 318, 118, ILI9341_BLACK);
  DisplayTemp::Display(temperature);
}

/*
 ***************************************************************************
 */

SetTime::SetTime(Adafruit_ILI9341_STM* screen, XPT2046* touch_screen)
: dt(screen, 44, 96), tft(screen), touch(touch_screen)
{
  ox = 44;   // These are the positions of the Time display so 
  oy = 60;   // buttons & text must be laid out in relation.
  Serial.println("ST::ST:start"); Serial.flush();
  
  bttns[0] = &htu; // plus buttons
  bttns[1] = &huu;  
  bttns[2] = &mtu;  
  bttns[3] = &muu;  
  bttns[4] = &stu; 
  bttns[5] = &suu;  
  
  bttns[6] = &htd;  
  bttns[7] = &hud;   
  bttns[8] = &mtd; 
  bttns[9] = &mud;  
  bttns[10] = &std;  
  bttns[11] = &sud; 

  bttns[12] = &bok;
  bttns[13] = &bcancel;

  for (int idx=0; idx < MAX_BTTNS; idx++)
  {
    bttns[idx]->setScreen(screen);
  }
  Serial.println("ST::ST:end"); Serial.flush();
}

void SetTime::Display(TM_T now)
{
  int x = ox;
  int y = oy;
  Serial.println("ST::Display:Start"); Serial.flush();
  
  dt.Display(now);
  
  // 'Plus' buttons.
  htu.setPosition(x, y);
  huu.setPosition(x+=DGT_W, y);
  mtu.setPosition(x+=DGT_W+CLN_W, y);
  muu.setPosition(x+=DGT_W, y);
  stu.setPosition(x+=DGT_W+CLN_W, y);
  suu.setPosition(x+=DGT_W, y);

  for (int idx=0; idx < 6; idx++)
  {
    bttns[idx]->setText("+");
    bttns[idx]->setWidthHeight(34, 34);
    bttns[idx]->Draw();
  }

  x = ox;
  y = oy + BTN_H + DGT_H + 2;
  
  // 'Minus' buttons.
  htd.setPosition(x, y);
  hud.setPosition(x+=DGT_W, y);
  mtd.setPosition(x+=DGT_W+CLN_W, y);
  mud.setPosition(x+=DGT_W, y);
  std.setPosition(x+=DGT_W+CLN_W, y);
  sud.setPosition(x+=DGT_W, y);

  for (int idx=6; idx < 12; idx++)
  {
    bttns[idx]->setText("-");
    bttns[idx]->setWidthHeight(34, 34);
    bttns[idx]->Draw();
  }

  // Other buttons
  bok.setPosition(ox+4, oy+136);
  bok.setWidthHeight(96, 34);
  bok.setText("Ok");
  bok.Draw();

  bcancel.setPosition(ox+140, oy+136);
  bcancel.setWidthHeight(96, 34);
  bcancel.setText("Cancel");
  bcancel.Draw();

  tft->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft->drawCentreString("SET TIME", 160, 10, 4);
  Serial.println("ST::Display:End"); Serial.flush();
}

static void inc_tens(uint8_t &val, uint8_t max_val)
{
  int tens = val / 10;
  int units = val % 10;
  tens = (tens + 1) % max_val;
  val = (tens * 10) + units;
}

static void inc_units(uint8_t &val, uint8_t max_val)
{
  int tens = val / 10;
  int units = val % 10;
  units = (units + 1) % max_val;
  val = (tens * 10) + units;
}

static void dec_tens(uint8_t &val, uint8_t max_val)
{
  int tens = val / 10;
  int units = val % 10;
  tens = (--tens) >= 0 ? tens : max_val-1;
  val = (tens * 10) + units;
}

static void dec_units(uint8_t &val, uint8_t max_val)
{
  int tens = val / 10;
  int units = val % 10;
  units = (--units) >= 0 ? units : max_val-1;
  val = (tens * 10) + units;
}

// Doesn't release control until the 'OK' or 'Cancel' Button is pressed.
void SetTime::Update(TM_T now)
{
  Button* touching = NULL;
  while(true)
  {
    if (!touching && touch->isTouching())
    {
      uint16_t x, y, tens, units;
      touch->getPosition(x, y);

      // Which Button widget is being touched, if any.
      for(int idx=0; idx < MAX_BTTNS; idx++)
      {
        if ( (touching = (Button *)bttns[idx]->Press(x, y)) )
        {
          beepDelay(50); // Beep to show button was pressed.
          break;
        }
      }

      if (touching == &htu)
      {
        inc_tens(now.tm_hour, 3); 
        if ((now.tm_hour/10) == 2  && (now.tm_hour % 10) > 3)
        {
          now.tm_hour = 23;
        }
      }
      else if (touching == &huu)
      {
        if ((now.tm_hour/10) == 2) {
          inc_units(now.tm_hour, 4);
        } 
        else
        {
          inc_units(now.tm_hour, 10);
        }
      }
      else if (touching == &mtu)
      {
        inc_tens(now.tm_min, 6);
      }
      else if (touching == &muu)
      {
        inc_units(now.tm_min, 10);
      }
      else if (touching == &stu)
      {
        inc_tens(now.tm_sec, 6);
      }
      else if (touching == &suu)
      {
        inc_units(now.tm_sec, 10);
      }

      else if (touching == &htd)
      {
        dec_tens(now.tm_hour, 3);
        if ((now.tm_hour/10) == 2  && (now.tm_hour % 10) > 3)
        {
          now.tm_hour = 23;
        }
      }
      else if (touching == &hud)
      {
        if ((now.tm_hour/10) == 2) 
        {
          dec_units(now.tm_hour, 4);
        }
        else
        { 
          dec_units(now.tm_hour, 10);
        }
      }
      else if (touching == &mtd)
      {
        dec_tens(now.tm_min, 6);
      }
      else if (touching == &mud)
      {
        dec_units(now.tm_min, 10);
      }
      else if (touching == &std)
      {
        dec_tens(now.tm_sec, 6);
      }
      else if (touching == &sud)
      {
        dec_units(now.tm_sec, 10);
      }   
      else if (touching == &bok)
      {
        set_date_time(&now);
        bok.Release();
        return;
      }
      else if (touching == &bcancel)
      {
        // Exit without changing time.
        bcancel.Release();
        return;
      }    
    }
    else if (touching && !touch->isTouching())
    {
      dt.Update(now);
      touching->Release();
      touching = NULL;
    }
    delay(100);
  }
}

/*
 ***************************************************************************
 */

SetDate::SetDate(Adafruit_ILI9341_STM* screen, XPT2046* touch_screen)
: dd(screen, 37, 96), tft(screen), touch(touch_screen)
{
  ox = 37;
  oy = 55;

  bttns[0] = &mdu;
  bttns[1] = &mu;
  bttns[2] = &yu;
  bttns[3] = &mdd;
  bttns[4] = &md;
  bttns[5] = &yd;

  bttns[6] = &bok;
  bttns[7] = &bcancel;

  for (int idx=0; idx < MAX_BTTNS; idx++)
  {
    bttns[idx]->setScreen(screen);
  }
}

void SetDate::Display(TM_T now)
{
  int x = ox;
  int y = oy;
  
  dd.Display(now);
  
  // 'Plus' buttons.
  mdu.setPosition(x, y);
  mu.setPosition(x+=(DGT6_W*2)+FS6_W, y);
  yu.setPosition(x+=(DGT6_W*4)+FS6_W, y);
  
  for (int idx=0; idx < 3; idx++)
  {
    bttns[idx]->setText("+");
    bttns[idx]->setWidthHeight(DGT6_W*2, 35);
    bttns[idx]->Draw();
  }

  x = ox;
  y = 150;
  
  // 'Minus' buttons.
  mdd.setPosition(x, y);
  md.setPosition(x+=(DGT6_W*2)+FS6_W, y);
  yd.setPosition(x+=(DGT6_W*4)+FS6_W, y);

  for (int idx=3; idx < 6; idx++)
  {
    bttns[idx]->setText("-");
    bttns[idx]->setWidthHeight(DGT6_W*2, 35);
    bttns[idx]->Draw();
  }

  // Other buttons
  bok.setPosition(40, 196);
  bok.setWidthHeight(100, 34);
  bok.setText("Ok");
  bok.Draw();

  bcancel.setPosition(180, 196);
  bcancel.setWidthHeight(100, 34);
  bcancel.setText("Cancel");
  bcancel.Draw();

  tft->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft->drawCentreString("SET DATE", 160, 10, 4);  
}

void SetDate::Update(TM_T now)
{
  Button* touching = NULL;

  // Days in a given calender month;
  int per_month[12] = { 31, 28, 31, 30,  31, 30, 31, 31,  30, 31, 30, 31 };
  
  if ((now.tm_year % 4) == 0)
  { 
    per_month[1] = 29;
  }

  while(true)
  {
    if (!touching && touch->isTouching())
    {
      uint16_t x, y, tens, units;
      touch->getPosition(x, y);

      // Which Button widget is being touched, if any.
      for(int idx=0; idx < MAX_BTTNS; idx++)
      {
        if ( (touching = (Button *)bttns[idx]->Press(x, y)) )
        {
          beepDelay(50);  // Beep to show a button was pressed.
          break;
        }
      }  

      if (touching == &mdu)
      {
        now.tm_mday = (now.tm_mday == per_month[now.tm_mon-1]) ? 1 : now.tm_mday + 1;
      }
      else if (touching == &mu)
      {
        now.tm_mon = (now.tm_mon == 12) ? 1 : now.tm_mon + 1;
      }
      else if (touching == &yu)
      {
        now.tm_year = (now.tm_year + 1) % 100;
      }
      
      else if (touching == &mdd)
      {
        now.tm_mday = (now.tm_mday == 1) ? per_month[now.tm_mon-1] : now.tm_mday - 1;
      }
      else if (touching == &md)
      {
        now.tm_mon = (now.tm_mon == 1) ? 12 : now.tm_mon -1;
       
      }
      else if (touching == &yd)
      {
        now.tm_year = (now.tm_year == 0) ? 99 : now.tm_year - 1;
      }
      else if (touching == &bok)
      {
        TM_T delta;
        get_date_time(&delta);
        now.tm_hour = delta.tm_hour;
        now.tm_min = delta.tm_min;
        now.tm_sec = delta.tm_sec;
        set_date_time(&now);
        bok.Release();
        return;
      }
      else if (touching == &bcancel)
      {
        // Exit without changing time.
        bcancel.Release();
        return;
      }    
    }
    else if (touching && !touch->isTouching())
    {
      // Adjust February days if year is now a leap year.
      if ((now.tm_year % 4) == 0)
      { 
        per_month[1] = 29;
      }
      else
      {
        per_month[1] = 28;
      }
      
      // Adjust days of month if month has lower days per month.
      if (now.tm_mday > per_month[now.tm_mon-1])
      {
        now.tm_mday = per_month[now.tm_mon-1];
      } 

      dd.Update(now);
      touching->Release();
      touching = NULL;
    }
    delay(50);
  }
}

/*
 ***************************************************************************
 */
 
SetDayOfWeek::SetDayOfWeek(Adafruit_ILI9341_STM* screen, XPT2046* touch_screen) 
 : ox(15), oy(60), today (0), tft(screen), touch(touch_screen)
{
  bttns[0] = &mo; // Lines up with the tm_wday value from the RTC
  bttns[1] = &tu;
  bttns[2] = &we;
  bttns[3] = &th;
  bttns[4] = &fr;
  bttns[5] = &sa;
  bttns[6] = &su;
  bttns[7] = &bok;
  bttns[8] = &bcancel;

  for (int idx=0; idx < MAX_BTTNS; idx++)
  {
    bttns[idx]->setScreen(screen);
    
    if (idx <= 6) // Only day of week buttons.
    {
      bttns[idx]->setWidthHeight(50, 50);
      bttns[idx]->setColor(ILI9341_BLACK, ILI9341_WHITE);
      // bttns[idx]->setFontSize(2);
    }
  }
}

void SetDayOfWeek::Display(TM_T now)
{
  int x = ox;
  int y = oy;

  mo.setPosition(x, y);
  mo.setText("Mo");
  tu.setPosition(x+=60, y);
  tu.setText("Tu");
  we.setPosition(x+=60, y);
  we.setText("We");
  th.setPosition(x+=60, y);
  th.setText("Th");
  fr.setPosition(x+=60, y);
  fr.setText("Fr");
  x = ox + 60;
  sa.setPosition(x, y+=60);
  sa.setText("Sa");
  su.setPosition(x+=120, y);
  su.setText("Su");

  // Other buttons
  bok.setPosition(40, 196);
  bok.setWidthHeight(100, 34);
  bok.setText("Ok");

  bcancel.setPosition(180, 196);
  bcancel.setWidthHeight(100, 34);
  bcancel.setText("Cancel");

  for (int idx=0; idx < MAX_BTTNS; idx++)
  {
    bttns[idx]->Draw();  
  }

  // Highlight the actual day
  today = now.tm_wday;
  bttns[today-1]->Release();  
  
  tft->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft->drawCentreString("SET DAY OF WEEK", 160, 10, 4);  
}

void SetDayOfWeek::Update(TM_T now) 
{
  Button* touching = NULL;

  while(true)
  {
    // Set when a button is pressed.
    int bttn_idx = 0xFF;
    if (!touching && touch->isTouching())
    {
      uint16_t x, y, tens, units;
      touch->getPosition(x, y);

      // Which Button widget is being touched, if any.
      for(int idx=0; idx < MAX_BTTNS; idx++)
      {
        if ( (touching = (Button *)bttns[idx]->Press(x, y)) )
        {
          bttn_idx = idx;
          beepDelay(50);  // Beep to show a button was pressed.
          break;
        }
      }  

      // If a button was pressed.
      if (bttn_idx != 0xFF) 
      {
        // If it was a 'day of week' button - 0 to 6.
        if (bttn_idx <= 6) 
        {
          bttns[today-1]->Release();  // Un-highlight the current day.
          today = bttn_idx + 1;
          //bttns[bttn_idx]->Release();  // Now highlight the new day.  
        }
        else if (touching == &bok)
        {
          TM_T delta;
          get_date_time(&delta);
          now = delta;
          now.tm_wday = today;
          set_date_time(&now);
          bok.Release();
          return;
        }
        else if (touching == &bcancel)
        {
          // Exit without changing day of week.
          bcancel.Release();
          return;
        }         
      }
    }
    else if (touching && !touch->isTouching())
    {
      touching = NULL;
    }
    delay(50);
  }  
}

/**
 * Full screen display of SetUp options as buttons.
 */
void SetUpScreen(Adafruit_ILI9341_STM& tft, XPT2046& touch)
{
  enum EButton {
    bttn_set_time,
    bttn_set_date,
    bttn_set_week_day,
    bttn_done,
    bttn_max    // Always the last enum.
  };

  bool Done = false;
  Button* touching = NULL;
  
  Button* bttns[bttn_max];
  //Button stb(&tft, 20, 40, 130, 40, "Time");
  Button stb(&tft, 95, 40, 130, 40, "Time");
  Button sdb(&tft, 95, 90, 130, 40, "Date");
  Button swdb(&tft, 95, 140, 130, 40, "Week Day");
  //Button sdb(&tft, 170, 40, 130, 40, "Date");
  Button dnb(&tft, 95, 190, 130, 40, "Done");

  EButton pressed;

  bttns[bttn_set_time]      = &stb;
  bttns[bttn_set_date]      = &sdb;
  bttns[bttn_set_week_day]  = &swdb;
  bttns[bttn_done]          = &dnb;

  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.drawCentreString("SET", 160, 10, 4); 
  for(int idx=0; idx < (int)bttn_max; idx++) bttns[idx]->Draw();

  while(!Done)
  {
    if (!touching && touch.isTouching())
    {
      uint16_t x, y, tens, units;
      touch.getPosition(x, y);
      pressed = bttn_max;

      // Which Button widget is being touched, if any.
      for(int idx=0; idx < (int)bttn_max; idx++)
      {
        if ( (touching = (Button *)bttns[idx]->Press(x, y)) )
        {
          beepDelay(50);  // Beep to show a button was pressed.
          pressed = (EButton)idx;
          touching->Release();
          touching = NULL;
          break;
        }
      }  

      if (bttn_max != pressed) 
      {
        TM_T now;
        get_date_time(&now); 
        
        switch (pressed) 
        {
          case bttn_set_time:
          {
            SetTime st_ctrl(&tft, &touch);
            tft.fillScreen(ILI9341_BLACK);
            st_ctrl.Display(now); 
            st_ctrl.Update(now);
            break;
          }
          case bttn_set_date:
          {
            SetDate sd_ctrl(&tft, &touch);
            tft.fillScreen(ILI9341_BLACK);
            sd_ctrl.Display(now);
            sd_ctrl.Update(now); 
            break;
          }
          case bttn_set_week_day:
          {
            SetDayOfWeek sdow_ctrl(&tft, &touch);
            tft.fillScreen(ILI9341_BLACK);
            sdow_ctrl.Display(now);
            sdow_ctrl.Update(now); 
            break;
          }
          case bttn_done:
            Done = true;
            break;
          default:
            // Shouldn't happen
            break;
        }

        // redraw if returning from setup screen.
        if (pressed != bttn_done) {
          tft.fillScreen(ILI9341_BLACK);
          tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
          tft.drawCentreString("SET", 160, 10, 4); 
          for(int idx=0; idx < (int)bttn_max; idx++) bttns[idx]->Draw();
        }
      }
    }
    else if (touching && !touch.isTouching())
    {
      touching->Release();
      touching = NULL;
    }
    delay(50);
  }
}

