/****************************************************************
 * Copyright (C) 2017, Yagro, all right reserved.
 * File name:    DateTime.c
 * Date:         2017.10.17
 * Description:  Date and time module source file.
*****************************************************************/

/****************************************************************
 *                        Header include
*****************************************************************/
#include "DateTime.h"

/****************************************************************
 *                       Global variables
*****************************************************************/


/****************************************************************
 *                     Function declaration
*****************************************************************/


/****************************************************************
 *                     Function definition
*****************************************************************/

/****************************************************************
 * Function:    GregorianCalendarDateAddYear
 * Description: Gregorian calendar date add year.
 * Input:       time: Gregorian calendar date.
 *              year: The number of year to add.
 * Output:
 * Return:      Gregorian calendar date.
*****************************************************************/
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

/****************************************************************
 * Function:    GregorianCalendarDateAddMonth
 * Description: Gregorian calendar date add month.
 * Input:       time:  Gregorian calendar date.
 *              month: The number of month to add.
 * Output:
 * Return:      Gregorian calendar date.
*****************************************************************/
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

/****************************************************************
 * Function:    GregorianCalendarDateAddWeek
 * Description: Gregorian calendar date add week.
 * Input:       time: Gregorian calendar date.
 *              week: The number of week to add.
 * Output:
 * Return:      Gregorian calendar date.
*****************************************************************/
DateTime GregorianCalendarDateAddWeek(DateTime time, int week)
{
  double jd = GregorianCalendarDateToJulianDate(time) + week * 7.0;

  return JulianDateToGregorianCalendarDate(jd);
}

/****************************************************************
 * Function:    GregorianCalendarDateAddDay
 * Description: Gregorian calendar date add day.
 * Input:       time: Gregorian calendar date.
 *              day:  The number of day to add.
 * Output:
 * Return:      Gregorian calendar date.
*****************************************************************/
DateTime GregorianCalendarDateAddDay(DateTime time, int day)
{
  double jd = GregorianCalendarDateToJulianDate(time) + day;

  return JulianDateToGregorianCalendarDate(jd);
}

/****************************************************************
 * Function:    GregorianCalendarDateAddHour
 * Description: Gregorian calendar date add hour.
 * Input:       time: Gregorian calendar date.
 *              hour: The number of hour to add.
 * Output:
 * Return:      Gregorian calendar date.
*****************************************************************/
DateTime GregorianCalendarDateAddHour(DateTime time, int hour)
{
  time.hour += hour;

  double jd = GregorianCalendarDateToJulianDate(time);

  return JulianDateToGregorianCalendarDate(jd);
}

/****************************************************************
 * Function:    GregorianCalendarDateAddMinute
 * Description: Gregorian calendar date add minute.
 * Input:       time:   Gregorian calendar date.
 *              minute: The number of minute to add.
 * Output:
 * Return:      Gregorian calendar date.
*****************************************************************/
DateTime GregorianCalendarDateAddMinute(DateTime time, int minute)
{
  time.minute += minute;

  double jd = GregorianCalendarDateToJulianDate(time);

  return JulianDateToGregorianCalendarDate(jd);
}

/****************************************************************
 * Function:    GregorianCalendarDateAddSecond
 * Description: Gregorian calendar date add second.
 * Input:       time:   Gregorian calendar date.
 *              second: The number of seconds to add.
 * Output:
 * Return:      Gregorian calendar date.
*****************************************************************/
DateTime GregorianCalendarDateAddSecond(DateTime time, int second)
{
  time.second += second;

  double jd = GregorianCalendarDateToJulianDate(time);

  return JulianDateToGregorianCalendarDate(jd);
}

/****************************************************************
 * Function:    GregorianCalendarDateToGpsWeekSecond
 * Description: Gregorian calendar date to gps week and second.
 * Input:       time: Gregorian calendar date.
 * Output:
 * Return:      Gps week and second.
*****************************************************************/
GpsWeekSecond GregorianCalendarDateToGpsWeekSecond(DateTime time)
{
  double jd = GregorianCalendarDateToJulianDate(time);

  return JulianDateToGpsWeekSecond(jd);
}

/****************************************************************
 * Function:    GregorianCalendarDateToJulianDate
 * Description: Gregorian calendar date to julian date.
 * Input:       time: Gregorian calendar date.
 * Output:
 * Return:      Julian date.
*****************************************************************/
double GregorianCalendarDateToJulianDate(DateTime time)
{
  int jdn = (1461 * (time.year + 4800 + (time.month - 14) / 12)) / 4
          + (367 * (time.month - 2 - 12 * ((time.month - 14) / 12))) / 12
          - (3 * ((time.year + 4900 + (time.month - 14) / 12) / 100)) / 4
          + time.day - 32075;

  double jd = jdn + ((time.hour - 12) * 3600.0 + time.minute * 60.0 + time.second) / 86400.0;

  return jd;
}

/****************************************************************
 * Function:    GregorianCalendarDateToModifiedJulianDate
 * Description: Gregorian calendar date to modified julian date.
 * Input:       time: Gregorian calendar date.
 * Output:
 * Return:      Modified julian date.
*****************************************************************/
double GregorianCalendarDateToModifiedJulianDate(DateTime time)
{
  return GregorianCalendarDateToJulianDate(time) - 2400000.5;
}

/****************************************************************
 * Function:    GpsWeekSecondAddYear
 * Description: Gps week and second add year.
 * Input:       time: Gps week and second.
 *              year: The number of year to add.
 * Output:
 * Return:      Gps week and second.
*****************************************************************/
GpsWeekSecond GpsWeekSecondAddYear(GpsWeekSecond time, int year)
{
  DateTime date = GpsWeekSecondToGregorianCalendarDate(time);

  date = GregorianCalendarDateAddYear(date, year);

  return GregorianCalendarDateToGpsWeekSecond(date);
}

/****************************************************************
 * Function:    GpsWeekSecondAddMonth
 * Description: Gps week and second add month.
 * Input:       time:  Gps week and second.
 *              month: The number of month to add.
 * Output:
 * Return:      Gps week and second.
*****************************************************************/
GpsWeekSecond GpsWeekSecondAddMonth(GpsWeekSecond time, int month)
{
  DateTime date = GpsWeekSecondToGregorianCalendarDate(time);

  date = GregorianCalendarDateAddMonth(date, month);

  return GregorianCalendarDateToGpsWeekSecond(date);
}

/****************************************************************
 * Function:    GpsWeekSecondAddWeek
 * Description: Gps week and second add week.
 * Input:       time: Gps week and second.
 *              week: The number of week to add.
 * Output:
 * Return:      Gps week and second.
*****************************************************************/
GpsWeekSecond GpsWeekSecondAddWeek(GpsWeekSecond time, int week)
{
  time.week += week;

  return time;
}

/****************************************************************
 * Function:    GpsWeekSecondAddDay
 * Description: Gps week and second add day.
 * Input:       time: Gps week and second.
 *              day:  The number of day to add.
 * Output:
 * Return:      Gps week and second.
*****************************************************************/
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

/****************************************************************
 * Function:    GpsWeekSecondAddHour
 * Description: Gps week and second add hour.
 * Input:       time: Gps week and second.
 *              hour: The number of hour to add.
 * Output:
 * Return:      Gps week and second.
*****************************************************************/
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

/****************************************************************
 * Function:    GpsWeekSecondAddMinute
 * Description: Gps week and second add minute.
 * Input:       time:   Gps week and second.
 *              minute: The number of minute to add.
 * Output:
 * Return:      Gps week and second.
*****************************************************************/
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

/****************************************************************
 * Function:    GpsWeekSecondAddSecond
 * Description: Gps week and second add second.
 * Input:       time:   Gps week and second.
 *              second: The number of second to add.
 * Output:
 * Return:      Gps week and second.
*****************************************************************/
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

/****************************************************************
 * Function:    GpsWeekSecondToGregorianCalendarDate
 * Description: Gps week and second to gregorian calendar date.
 * Input:       time: Gps week and second.
 * Output:
 * Return:      Gregorian calendar date.
*****************************************************************/
DateTime GpsWeekSecondToGregorianCalendarDate(GpsWeekSecond time)
{
  double jd = GpsWeekSecondToJulianDate(time);

  return JulianDateToGregorianCalendarDate(jd);
}

/****************************************************************
 * Function:    GpsWeekSecondToJulianDate
 * Description: Gps week and second to julian date.
 * Input:       time: Gps week and second.
 * Output:
 * Return:      Julian date.
*****************************************************************/
double GpsWeekSecondToJulianDate(GpsWeekSecond time)
{
  double jd = 2444244.5 + time.week * 7.0 + time.second / 86400.0;

  return jd;
}

/****************************************************************
 * Function:    GpsWeekSecondToModifiedJulianDate
 * Description: Gps week and second to modified julian date.
 * Input:       time: Gps week and second.
 * Output:
 * Return:      Modified julian date.
*****************************************************************/
double GpsWeekSecondToModifiedJulianDate(GpsWeekSecond time)
{
  return GpsWeekSecondToJulianDate(time) - 2400000.5;
}

/****************************************************************
 * Function:    JulianDateAddYear
 * Description: Julian date add year.
 * Input:       jd:   Julian date.
 *              year: The number of year to add.
 * Output:
 * Return:      Julian date.
*****************************************************************/
double JulianDateAddYear(double jd, int year)
{
  DateTime date = JulianDateToGregorianCalendarDate(jd);

  date = GregorianCalendarDateAddYear(date, year);

  return GregorianCalendarDateToJulianDate(date);
}

/****************************************************************
 * Function:    JulianDateAddMonth
 * Description: Julian date add month.
 * Input:       jd:    Julian date.
 *              month: The number of month to add.
 * Output:
 * Return:      Julian date.
*****************************************************************/
double JulianDateAddMonth(double jd, int month)
{
  DateTime date = JulianDateToGregorianCalendarDate(jd);

  date = GregorianCalendarDateAddMonth(date, month);

  return GregorianCalendarDateToJulianDate(date);
}

/****************************************************************
 * Function:    JulianDateAddWeek
 * Description: Julian date add week.
 * Input:       jd:   Julian date.
 *              week: The number of week to add.
 * Output:
 * Return:      Julian date.
*****************************************************************/
double JulianDateAddWeek(double jd, int week)
{
  jd += week * 7.0;

  return jd;
}

/****************************************************************
 * Function:    JulianDateAddDay
 * Description: Julian date add day.
 * Input:       jd:  Julian date.
 *              day: The number of day to add.
 * Output:
 * Return:      Julian date.
*****************************************************************/
double JulianDateAddDay(double jd, int day)
{
  jd += day;

  return jd;
}

/****************************************************************
 * Function:    JulianDateAddHour
 * Description: Julian date add hour.
 * Input:       jd:   Julian date.
 *              hour: The number of hour to add.
 * Output:
 * Return:      Julian date.
*****************************************************************/
double JulianDateAddHour(double jd, int hour)
{
  jd += hour / 24.0;

  return jd;
}

/****************************************************************
 * Function:    JulianDateAddMinute
 * Description: Julian date add minute.
 * Input:       jd:     Julian date.
 *              minute: The number of minute to add.
 * Output:
 * Return:      Julian date.
*****************************************************************/
double JulianDateAddMinute(double jd, int minute)
{
  jd += minute / 1440.0;

  return jd;
}

/****************************************************************
 * Function:    JulianDateAddSecond
 * Description: Julian date add second.
 * Input:       jd:     Julian date.
 *              second: The number of second to add.
 * Output:
 * Return:      Julian date.
*****************************************************************/
double JulianDateAddSecond(double jd, int second)
{
  jd += second / 86400.0;

  return jd;
}

/****************************************************************
 * Function:    JulianDateToGregorianCalendarDate
 * Description: Julian date to gregorian calendar date.
 * Input:       jd: Julian date.
 * Output:
 * Return:      Gregorian calendar date.
*****************************************************************/
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

/****************************************************************
 * Function:    JulianDateToGpsWeekSecond
 * Description: Julian date to gps week and second.
 * Input:       jd: Julian date.
 * Output:
 * Return:      Gps week and second.
*****************************************************************/
GpsWeekSecond JulianDateToGpsWeekSecond(double jd)
{
  GpsWeekSecond time = {0};
  DateTime      date = JulianDateToGregorianCalendarDate(jd);

  time.week   = (int)(jd - 2444244.5) / 7;
  time.second = ((int)(jd - 2444244.5) - time.week * 7) * 86400 + date.hour * 3600 + date.minute * 60 + date.second;

  return time;
}

/****************************************************************
 * Function:    JulianDateToModifiedJulianDate
 * Description: Julian date to modified julian date.
 * Input:       jd: Julian date.
 * Output:
 * Return:      Modified julian date.
*****************************************************************/
double JulianDateToModifiedJulianDate(double jd)
{
  double mjd = jd - 2400000.5;

  return mjd;
}

/****************************************************************
 * Function:    ModifiedJulianDateAddYear
 * Description: Modified julian date add year.
 * Input:       mjd:  Modified julian date.
 *              year: The number of year to add.
 * Output:
 * Return:      Modified julian date.
*****************************************************************/
double ModifiedJulianDateAddYear(double mjd, int year)
{
  DateTime date = ModifiedJulianDateToGregorianCalendarDate(mjd);

  date = GregorianCalendarDateAddYear(date, year);

  return GregorianCalendarDateToModifiedJulianDate(date);
}

/****************************************************************
 * Function:    ModifiedJulianDateAddMonth
 * Description: Modified julian date add month.
 * Input:       mjd:   Modified julian date.
 *              month: The number of month to add.
 * Output:
 * Return:      Modified julian date.
*****************************************************************/
double ModifiedJulianDateAddMonth(double mjd, int month)
{
  DateTime date = ModifiedJulianDateToGregorianCalendarDate(mjd);

  date = GregorianCalendarDateAddMonth(date, month);

  return GregorianCalendarDateToModifiedJulianDate(date);
}

/****************************************************************
 * Function:    ModifiedJulianDateAddWeek
 * Description: Modified julian date add week.
 * Input:       mjd:  Modified julian date.
 *              week: The number of week to add.
 * Output:
 * Return:      Modified julian date.
*****************************************************************/
double ModifiedJulianDateAddWeek(double mjd, int week)
{
  mjd += week * 7.0;

  return mjd;
}

/****************************************************************
 * Function:    ModifiedJulianDateAddDay
 * Description: Modified julian date add day.
 * Input:       mjd: Modified julian date.
 *              day: The number of day to add.
 * Output:
 * Return:      Modified julian date.
*****************************************************************/
double ModifiedJulianDateAddDay(double mjd, int day)
{
  mjd += day;

  return mjd;
}

/****************************************************************
 * Function:    ModifiedJulianDateAddHour
 * Description: Modified julian date add hour.
 * Input:       mjd:  Modified julian date.
 *              hour: The number of hour to add.
 * Output:
 * Return:      Modified julian date.
*****************************************************************/
double ModifiedJulianDateAddHour(double mjd, int hour)
{
  mjd += hour / 24.0;

  return mjd;
}

/****************************************************************
 * Function:    ModifiedJulianDateAddMinute
 * Description: Modified julian date add minute.
 * Input:       mjd:    Modified julian date.
 *              minute: The number of minute to add.
 * Output:
 * Return:      Modified julian date.
*****************************************************************/
double ModifiedJulianDateAddMinute(double mjd, int minute)
{
  mjd += minute / 1440.0;

  return mjd;
}

/****************************************************************
 * Function:    ModifiedJulianDateAddSecond
 * Description: Modified julian date add second.
 * Input:       mjd:    Modified julian date.
 *              second: The number of second to add.
 * Output:
 * Return:      Modified julian date.
*****************************************************************/
double ModifiedJulianDateAddSecond(double mjd, int second)
{
  mjd += second / 86400.0;

  return mjd;
}

/****************************************************************
 * Function:    ModifiedJulianDateToGregorianCalendarDate
 * Description: Modified julian date to gregorian calendar date.
 * Input:       mjd: Modified julian date.
 * Output:
 * Return:      Gregorian calendar date.
*****************************************************************/
DateTime ModifiedJulianDateToGregorianCalendarDate(double mjd)
{
  return JulianDateToGregorianCalendarDate(mjd + 2400000.5);
}

/****************************************************************
 * Function:    ModifiedJulianDateToGpsWeekSecond
 * Description: Modified julian date to gps week and second.
 * Input:       mjd: Modified julian date.
 * Output:
 * Return:      Gps week and second.
*****************************************************************/
GpsWeekSecond ModifiedJulianDateToGpsWeekSecond(double mjd)
{
  return JulianDateToGpsWeekSecond(mjd + 2400000.5);
}

/****************************************************************
 * Function:    ModifiedJulianDateToJulianDate
 * Description: Modified julian date to julian date.
 * Input:       mjd: Modified julian date.
 * Output:
 * Return:      Julian date.
*****************************************************************/
double ModifiedJulianDateToJulianDate(double mjd)
{
  double jd = mjd + 2400000.5;

  return jd;
}
