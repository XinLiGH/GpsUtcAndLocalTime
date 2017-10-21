/****************************************************************
 * Copyright (C) 2017, Yagro, all right reserved.
 * File name:    DateTime.h
 * Date:         2017.10.17
 * Description:  Date and time module header file.
*****************************************************************/

#ifndef __DATETIME_H
#define __DATETIME_H

/****************************************************************
 *                        Header include
*****************************************************************/


/****************************************************************
 *                       Macro definition
*****************************************************************/


/****************************************************************
 *                       Type definition
*****************************************************************/


/****************************************************************
 *                     Structure definition
*****************************************************************/
typedef struct
{
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
}DateTime;

typedef struct
{
  int week;
  int second;
}GpsWeekSecond;


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/****************************************************************
 *                     Variable declaration
*****************************************************************/


/****************************************************************
 *                     Function declaration
*****************************************************************/
DateTime GregorianCalendarDateAddYear(DateTime time, int year);
DateTime GregorianCalendarDateAddMonth(DateTime time, int month);
DateTime GregorianCalendarDateAddWeek(DateTime time, int week);
DateTime GregorianCalendarDateAddDay(DateTime time, int day);
DateTime GregorianCalendarDateAddHour(DateTime time, int hour);
DateTime GregorianCalendarDateAddMinute(DateTime time, int minute);
DateTime GregorianCalendarDateAddSecond(DateTime time, int second);
GpsWeekSecond GregorianCalendarDateToGpsWeekSecond(DateTime time);
double GregorianCalendarDateToJulianDate(DateTime time);
double GregorianCalendarDateToModifiedJulianDate(DateTime time);
GpsWeekSecond GpsWeekSecondAddYear(GpsWeekSecond time, int year);
GpsWeekSecond GpsWeekSecondAddMonth(GpsWeekSecond time, int month);
GpsWeekSecond GpsWeekSecondAddWeek(GpsWeekSecond time, int week);
GpsWeekSecond GpsWeekSecondAddDay(GpsWeekSecond time, int day);
GpsWeekSecond GpsWeekSecondAddHour(GpsWeekSecond time, int hour);
GpsWeekSecond GpsWeekSecondAddMinute(GpsWeekSecond time, int minute);
GpsWeekSecond GpsWeekSecondAddSecond(GpsWeekSecond time, int second);
DateTime GpsWeekSecondToGregorianCalendarDate(GpsWeekSecond time);
double GpsWeekSecondToJulianDate(GpsWeekSecond time);
double GpsWeekSecondToModifiedJulianDate(GpsWeekSecond time);
double JulianDateAddYear(double jd, int year);
double JulianDateAddMonth(double jd, int month);
double JulianDateAddWeek(double jd, int week);
double JulianDateAddDay(double jd, int day);
double JulianDateAddHour(double jd, int hour);
double JulianDateAddMinute(double jd, int minute);
double JulianDateAddSecond(double jd, int second);
DateTime JulianDateToGregorianCalendarDate(double jd);
GpsWeekSecond JulianDateToGpsWeekSecond(double jd);
double JulianDateToModifiedJulianDate(double jd);
double ModifiedJulianDateAddYear(double mjd, int year);
double ModifiedJulianDateAddMonth(double mjd, int month);
double ModifiedJulianDateAddWeek(double mjd, int week);
double ModifiedJulianDateAddDay(double mjd, int day);
double ModifiedJulianDateAddHour(double mjd, int hour);
double ModifiedJulianDateAddMinute(double mjd, int minute);
double ModifiedJulianDateAddSecond(double mjd, int second);
DateTime ModifiedJulianDateToGregorianCalendarDate(double mjd);
GpsWeekSecond ModifiedJulianDateToGpsWeekSecond(double mjd);
double ModifiedJulianDateToJulianDate(double mjd);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* __DATETIME_H */
