/**
  ******************************************************************************
  * @file    DateTime.h
  * @author  XinLi
  * @version v1.0
  * @date    24-October-2017
  * @brief   Header file for DateTime.c module.
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

#ifndef __DATETIME_H
#define __DATETIME_H

#ifdef __cplusplus
extern "C" {
#endif

/* Header includes -----------------------------------------------------------*/
/* Macro definitions ---------------------------------------------------------*/
/* Type definitions ----------------------------------------------------------*/
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

/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/
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

/* Function definitions ------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __DATETIME_H */
