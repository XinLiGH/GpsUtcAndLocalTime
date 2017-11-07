/**
  ******************************************************************************
  * @file    DateTime.c
  * @author  XinLi
  * @version v1.0
  * @date    24-October-2017
  * @brief   Date and time module source file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>Copyright &copy; 2017 XinLi</center></h2>
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <https://www.gnu.org/licenses/>.
  *
  ******************************************************************************
  */

/* Header includes -----------------------------------------------------------*/
#include "DateTime.h"

/* Macro definitions ---------------------------------------------------------*/
/* Type definitions ----------------------------------------------------------*/
/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/
/* Function definitions ------------------------------------------------------*/

/**
  * @brief  Gregorian calendar date add year.
  * @param  [in] time: Gregorian calendar date.
  * @param  [in] year: The number of year to add.
  * @return Gregorian calendar date.
  */
DateTime GregorianCalendarDateAddYear(DateTime time, int year)
{
  time.year += year;

  if(time.month == 2)
  {
    int mday = 0;

    if((((time.year % 4) == 0) && ((time.year % 100) != 0)) || ((time.year % 400) == 0))
    {
      mday = 29;
    }
    else
    {
      mday = 28;
    }

    if(time.day > mday)
    {
      time.month += 1;
      time.day   -= mday;
    }
  }

  return time;
}

/**
  * @brief  Gregorian calendar date add month.
  * @param  [in] time:  Gregorian calendar date.
  * @param  [in] month: The number of month to add.
  * @return Gregorian calendar date.
  */
DateTime GregorianCalendarDateAddMonth(DateTime time, int month)
{
  time.year  += month / 12;
  time.month += month % 12;

  if(time.month > 12)
  {
    time.year  += 1;
    time.month -= 12;
  }

  int mday = 0;

  if((time.month == 1) || (time.month == 3) || (time.month == 5) || (time.month == 7) ||
     (time.month == 8) || (time.month == 10) || (time.month == 12))
  {
    mday = 31;
  }
  else if((time.month == 4) || (time.month == 6) || (time.month == 9) || (time.month == 11))
  {
    mday = 30;
  }
  else
  {
    if((((time.year % 4) == 0) && ((time.year % 100) != 0)) || ((time.year % 400) == 0))
    {
      mday = 29;
    }
    else
    {
      mday = 28;
    }
  }

  if(time.day > mday)
  {
    time.month += 1;
    time.day   -= mday;

    if(time.month > 12)
    {
      time.year  += 1;
      time.month -= 12;
    }
  }

  return time;
}

/**
  * @brief  Gregorian calendar date add week.
  * @param  [in] time: Gregorian calendar date.
  * @param  [in] week: The number of week to add.
  * @return Gregorian calendar date.
  */
DateTime GregorianCalendarDateAddWeek(DateTime time, int week)
{
  double jd = GregorianCalendarDateToJulianDate(time) + week * 7.0;

  return JulianDateToGregorianCalendarDate(jd);
}

/**
  * @brief  Gregorian calendar date add day.
  * @param  [in] time: Gregorian calendar date.
  * @param  [in] day:  The number of day to add.
  * @return Gregorian calendar date.
  */
DateTime GregorianCalendarDateAddDay(DateTime time, int day)
{
  double jd = GregorianCalendarDateToJulianDate(time) + day;

  return JulianDateToGregorianCalendarDate(jd);
}

/**
  * @brief  Gregorian calendar date add hour.
  * @param  [in] time: Gregorian calendar date.
  * @param  [in] hour: The number of hour to add.
  * @return Gregorian calendar date.
  */
DateTime GregorianCalendarDateAddHour(DateTime time, int hour)
{
  time.hour += hour;

  double jd = GregorianCalendarDateToJulianDate(time);

  return JulianDateToGregorianCalendarDate(jd);
}

/**
  * @brief  Gregorian calendar date add minute.
  * @param  [in] time:   Gregorian calendar date.
  * @param  [in] minute: The number of minute to add.
  * @return Gregorian calendar date.
  */
DateTime GregorianCalendarDateAddMinute(DateTime time, int minute)
{
  time.minute += minute;

  double jd = GregorianCalendarDateToJulianDate(time);

  return JulianDateToGregorianCalendarDate(jd);
}

/**
  * @brief  Gregorian calendar date add second.
  * @param  [in] time:   Gregorian calendar date.
  * @param  [in] second: The number of seconds to add.
  * @return Gregorian calendar date.
  */
DateTime GregorianCalendarDateAddSecond(DateTime time, int second)
{
  time.second += second;

  double jd = GregorianCalendarDateToJulianDate(time);

  return JulianDateToGregorianCalendarDate(jd);
}

/**
  * @brief  Gregorian calendar date to gps week and second.
  * @param  [in] time: Gregorian calendar date.
  * @return Gps week and second.
  */
GpsWeekSecond GregorianCalendarDateToGpsWeekSecond(DateTime time)
{
  double jd = GregorianCalendarDateToJulianDate(time);

  return JulianDateToGpsWeekSecond(jd);
}

/**
  * @brief  Gregorian calendar date to julian date.
  * @param  [in] time: Gregorian calendar date.
  * @return Julian date.
  */
double GregorianCalendarDateToJulianDate(DateTime time)
{
  int jdn = (1461 * (time.year + 4800 + (time.month - 14) / 12)) / 4
          + (367 * (time.month - 2 - 12 * ((time.month - 14) / 12))) / 12
          - (3 * ((time.year + 4900 + (time.month - 14) / 12) / 100)) / 4
          + time.day - 32075;

  double jd = jdn + ((time.hour - 12) * 3600.0 + time.minute * 60.0 + time.second) / 86400.0;

  return jd;
}

/**
  * @brief  Gregorian calendar date to modified julian date.
  * @param  [in] time: Gregorian calendar date.
  * @return Modified julian date.
  */
double GregorianCalendarDateToModifiedJulianDate(DateTime time)
{
  return GregorianCalendarDateToJulianDate(time) - 2400000.5;
}

/**
  * @brief  Gps week and second add year.
  * @param  [in] time: Gps week and second.
  * @param  [in] year: The number of year to add.
  * @return Gps week and second.
  */
GpsWeekSecond GpsWeekSecondAddYear(GpsWeekSecond time, int year)
{
  DateTime date = GpsWeekSecondToGregorianCalendarDate(time);

  date = GregorianCalendarDateAddYear(date, year);

  return GregorianCalendarDateToGpsWeekSecond(date);
}

/**
  * @brief  Gps week and second add month.
  * @param  [in] time:  Gps week and second.
  * @param  [in] month: The number of month to add.
  * @return Gps week and second.
  */
GpsWeekSecond GpsWeekSecondAddMonth(GpsWeekSecond time, int month)
{
  DateTime date = GpsWeekSecondToGregorianCalendarDate(time);

  date = GregorianCalendarDateAddMonth(date, month);

  return GregorianCalendarDateToGpsWeekSecond(date);
}

/**
  * @brief  Gps week and second add week.
  * @param  [in] time: Gps week and second.
  * @param  [in] week: The number of week to add.
  * @return Gps week and second.
  */
GpsWeekSecond GpsWeekSecondAddWeek(GpsWeekSecond time, int week)
{
  time.week += week;

  return time;
}

/**
  * @brief  Gps week and second add day.
  * @param  [in] time: Gps week and second.
  * @param  [in] day:  The number of day to add.
  * @return Gps week and second.
  */
GpsWeekSecond GpsWeekSecondAddDay(GpsWeekSecond time, int day)
{
  time.week   += day / 7;
  time.second += day % 7 * 86400;

  if(time.second > 604799)
  {
    time.week   += 1;
    time.second -= 604800;
  }

  return time;
}

/**
  * @brief  Gps week and second add hour.
  * @param  [in] time: Gps week and second.
  * @param  [in] hour: The number of hour to add.
  * @return Gps week and second.
  */
GpsWeekSecond GpsWeekSecondAddHour(GpsWeekSecond time, int hour)
{
  time.week   += hour / 168;
  time.second += hour % 168 * 3600;

  if(time.second > 604799)
  {
    time.week   += 1;
    time.second -= 604800;
  }
  
  return time;
}

/**
  * @brief  Gps week and second add minute.
  * @param  [in] time:   Gps week and second.
  * @param  [in] minute: The number of minute to add.
  * @return Gps week and second.
  */
GpsWeekSecond GpsWeekSecondAddMinute(GpsWeekSecond time, int minute)
{
  time.week   += minute / 10080;
  time.second += minute % 10080 * 60;
  
  if(time.second > 604799)
  {
    time.week   += 1;
    time.second -= 604800;
  }
  
  return time;
}

/**
  * @brief  Gps week and second add second.
  * @param  [in] time:   Gps week and second.
  * @param  [in] second: The number of second to add.
  * @return Gps week and second.
  */
GpsWeekSecond GpsWeekSecondAddSecond(GpsWeekSecond time, int second)
{
  time.week   += second / 604800;
  time.second += second % 604800;

  if(time.second > 604799)
  {
    time.week   += 1;
    time.second -= 604800;
  }
  
  return time;
}

/**
  * @brief  Gps week and second to gregorian calendar date.
  * @param  [in] time: Gps week and second.
  * @return Gregorian calendar date.
  */
DateTime GpsWeekSecondToGregorianCalendarDate(GpsWeekSecond time)
{
  double jd = GpsWeekSecondToJulianDate(time);

  return JulianDateToGregorianCalendarDate(jd);
}

/**
  * @brief  Gps week and second to julian date.
  * @param  [in] time: Gps week and second.
  * @return Julian date.
  */
double GpsWeekSecondToJulianDate(GpsWeekSecond time)
{
  double jd = 2444244.5 + time.week * 7.0 + time.second / 86400.0;

  return jd;
}

/**
  * @brief  Gps week and second to modified julian date.
  * @param  [in] time: Gps week and second.
  * @return Modified julian date.
  */
double GpsWeekSecondToModifiedJulianDate(GpsWeekSecond time)
{
  return GpsWeekSecondToJulianDate(time) - 2400000.5;
}

/**
  * @brief  Julian date add year.
  * @param  [in] jd:   Julian date.
  * @param  [in] year: The number of year to add.
  * @return Julian date.
  */
double JulianDateAddYear(double jd, int year)
{
  DateTime date = JulianDateToGregorianCalendarDate(jd);

  date = GregorianCalendarDateAddYear(date, year);

  return GregorianCalendarDateToJulianDate(date);
}

/**
  * @brief  Julian date add month.
  * @param  [in] jd:    Julian date.
  * @param  [in] month: The number of month to add.
  * @return Julian date.
  */
double JulianDateAddMonth(double jd, int month)
{
  DateTime date = JulianDateToGregorianCalendarDate(jd);

  date = GregorianCalendarDateAddMonth(date, month);

  return GregorianCalendarDateToJulianDate(date);
}

/**
  * @brief  Julian date add week.
  * @param  [in] jd:   Julian date.
  * @param  [in] week: The number of week to add.
  * @return Julian date.
  */
double JulianDateAddWeek(double jd, int week)
{
  jd += week * 7.0;

  return jd;
}

/**
  * @brief  Julian date add day.
  * @param  [in] jd:  Julian date.
  * @param  [in] day: The number of day to add.
  * @return Julian date.
  */
double JulianDateAddDay(double jd, int day)
{
  jd += day;

  return jd;
}

/**
  * @brief  Julian date add hour.
  * @param  [in] jd:   Julian date.
  * @param  [in] hour: The number of hour to add.
  * @return Julian date.
  */
double JulianDateAddHour(double jd, int hour)
{
  jd += hour / 24.0;

  return jd;
}

/**
  * @brief  Julian date add minute.
  * @param  [in] jd:     Julian date.
  * @param  [in] minute: The number of minute to add.
  * @return Julian date.
  */
double JulianDateAddMinute(double jd, int minute)
{
  jd += minute / 1440.0;

  return jd;
}

/**
  * @brief  Julian date add second.
  * @param  [in] jd:     Julian date.
  * @param  [in] second: The number of second to add.
  * @return Julian date.
  */
double JulianDateAddSecond(double jd, int second)
{
  jd += second / 86400.0;

  return jd;
}

/**
  * @brief  Julian date to gregorian calendar date.
  * @param  [in] jd: Julian date.
  * @return Gregorian calendar date.
  */
DateTime JulianDateToGregorianCalendarDate(double jd)
{
  int y = 4716;
  int j = 1401;
  int m = 2;
  int n = 12;
  int r = 4;
  int p = 1461;
  int v = 3;
  int u = 5;
  int s = 153;
  int w = 2;
  int b = 274277;
  int c = -38;

  int jdn = (int)(jd + 0.5);
  int f   = jdn + j + (((4 * jdn + b) / 146097) * 3) / 4 + c;
  int e   = r * f + v;
  int g   = (e % p) / r;
  int h   = u * g + w;

  DateTime time = {0};

  time.day    = (h % s) / u + 1;
  time.month  = (h / s + m) % n + 1;
  time.year   = e / p - y + (n + m - time.month) / n;
  time.hour   = (int)((jd + 0.5 - jdn) * 86400.5) / 3600;
  time.minute = (int)((jd + 0.5 - jdn) * 86400.5 - time.hour * 3600) / 60;
  time.second = (int)((jd + 0.5 - jdn) * 86400.5 - time.hour * 3600 - time.minute * 60);

  return time;
}

/**
  * @brief  Julian date to gps week and second.
  * @param  [in] jd: Julian date.
  * @return Gps week and second.
  */
GpsWeekSecond JulianDateToGpsWeekSecond(double jd)
{
  GpsWeekSecond time = {0};
  DateTime      date = JulianDateToGregorianCalendarDate(jd);

  time.week   = (int)(jd - 2444244.5) / 7;
  time.second = ((int)(jd - 2444244.5) - time.week * 7) * 86400 + date.hour * 3600 + date.minute * 60 + date.second;

  return time;
}

/**
  * @brief  Julian date to modified julian date.
  * @param  [in] jd: Julian date.
  * @return Modified julian date.
  */
double JulianDateToModifiedJulianDate(double jd)
{
  double mjd = jd - 2400000.5;

  return mjd;
}

/**
  * @brief  Modified julian date add year.
  * @param  [in] mjd:  Modified julian date.
  * @param  [in] year: The number of year to add.
  * @return Modified julian date.
  */
double ModifiedJulianDateAddYear(double mjd, int year)
{
  DateTime date = ModifiedJulianDateToGregorianCalendarDate(mjd);

  date = GregorianCalendarDateAddYear(date, year);

  return GregorianCalendarDateToModifiedJulianDate(date);
}

/**
  * @brief  Modified julian date add month.
  * @param  [in] mjd:   Modified julian date.
  * @param  [in] month: The number of month to add.
  * @return Modified julian date.
  */
double ModifiedJulianDateAddMonth(double mjd, int month)
{
  DateTime date = ModifiedJulianDateToGregorianCalendarDate(mjd);

  date = GregorianCalendarDateAddMonth(date, month);

  return GregorianCalendarDateToModifiedJulianDate(date);
}

/**
  * @brief  Modified julian date add week.
  * @param  [in] mjd:  Modified julian date.
  * @param  [in] week: The number of week to add.
  * @return Modified julian date.
  */
double ModifiedJulianDateAddWeek(double mjd, int week)
{
  mjd += week * 7.0;

  return mjd;
}

/**
  * @brief  Modified julian date add day.
  * @param  [in] mjd: Modified julian date.
  * @param  [in] day: The number of day to add.
  * @return Modified julian date.
  */
double ModifiedJulianDateAddDay(double mjd, int day)
{
  mjd += day;

  return mjd;
}

/**
  * @brief  Modified julian date add hour.
  * @param  [in] mjd:  Modified julian date.
  * @param  [in] hour: The number of hour to add.
  * @return Modified julian date.
  */
double ModifiedJulianDateAddHour(double mjd, int hour)
{
  mjd += hour / 24.0;

  return mjd;
}

/**
  * @brief  Modified julian date add minute.
  * @param  [in] mjd:    Modified julian date.
  * @param  [in] minute: The number of minute to add.
  * @return Modified julian date.
  */
double ModifiedJulianDateAddMinute(double mjd, int minute)
{
  mjd += minute / 1440.0;

  return mjd;
}

/**
  * @brief  Modified julian date add second.
  * @param  [in] mjd:    Modified julian date.
  * @param  [in] second: The number of second to add.
  * @return Modified julian date.
  */
double ModifiedJulianDateAddSecond(double mjd, int second)
{
  mjd += second / 86400.0;

  return mjd;
}

/**
  * @brief  Modified julian date to gregorian calendar date.
  * @param  [in] mjd: Modified julian date.
  * @return Gregorian calendar date.
  */
DateTime ModifiedJulianDateToGregorianCalendarDate(double mjd)
{
  return JulianDateToGregorianCalendarDate(mjd + 2400000.5);
}

/**
  * @brief  Modified julian date to gps week and second.
  * @param  [in] mjd: Modified julian date.
  * @return Gps week and second.
  */
GpsWeekSecond ModifiedJulianDateToGpsWeekSecond(double mjd)
{
  return JulianDateToGpsWeekSecond(mjd + 2400000.5);
}

/**
  * @brief  Modified julian date to julian date.
  * @param  [in] mjd: Modified julian date.
  * @return Julian date.
  */
double ModifiedJulianDateToJulianDate(double mjd)
{
  double jd = mjd + 2400000.5;

  return jd;
}
