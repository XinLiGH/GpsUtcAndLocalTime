/****************************************************************
 * Copyright (C) 2017, Yagro, all right reserved.
 * File name:    main.c
 * Date:         2017.10.17
 * Description:  GPS, UTC and local time displays.
*****************************************************************/

/****************************************************************
 *                        Header include
*****************************************************************/
#include "DateTime.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

/****************************************************************
 *                       Global variables
*****************************************************************/


/****************************************************************
 *                     Function declaration
*****************************************************************/
static void gotoxy(int x, int y);

/****************************************************************
 *                     Function definition
*****************************************************************/

/****************************************************************
 * Function:    main
 * Description: Program entry.
 * Input:
 * Output:
 * Return:
*****************************************************************/
int main(void)
{
  for(;;)
  {
    time_t        times     = 0;
    double        mjd       = 0.0;
    DateTime      utctime   = {.year = 1970, .month = 1, .day = 1, .hour = 0, .minute = 0, .second = 0};
    DateTime      localtime = {.year = 1970, .month = 1, .day = 1, .hour = 8, .minute = 0, .second = 0};
    DateTime      gpstime   = {.year = 1970, .month = 1, .day = 1, .hour = 0, .minute = 0, .second = 0};
    GpsWeekSecond gpstimews = {0};

    time(&times);

    if(times > INT32_MAX)
    {
      utctime = GregorianCalendarDateAddSecond(utctime, INT32_MAX);
      utctime = GregorianCalendarDateAddSecond(utctime, (int)(times - INT32_MAX));
    }
    else
    {
      utctime = GregorianCalendarDateAddSecond(utctime, (int)times);
    }

    mjd       = GregorianCalendarDateToModifiedJulianDate(utctime);
    localtime = GregorianCalendarDateAddHour(utctime, 8);
    gpstime   = GregorianCalendarDateAddSecond(utctime, 18);
    gpstimews = GregorianCalendarDateToGpsWeekSecond(gpstime);

    gotoxy(0, 0);

    printf("Local | %d-%.2d-%.2d %.2d:%.2d:%.2d | timezone UTC+8\n",
           localtime.year, localtime.month, localtime.day,
           localtime.hour, localtime.minute, localtime.second);

    printf("UTC   | %d-%.2d-%.2d %.2d:%.2d:%.2d | MJD %.5f\n",
           utctime.year, utctime.month, utctime.day,
           utctime.hour, utctime.minute, utctime.second,
           mjd);

    printf("GPS   | %d-%.2d-%.2d %.2d:%.2d:%.2d | week %d %d s\n",
           gpstime.year, gpstime.month, gpstime.day,
           gpstime.hour, gpstime.minute, gpstime.second,
           gpstimews.week, gpstimews.second);

    Sleep(100);
  }
}

/****************************************************************
 * Function:    gotoxy
 * Description: Move the cursor to the specified position on the text screen.
 * Input:       x: X axis coordinates.
 *              y: Y axis coordinates.
 * Output:
 * Return:
*****************************************************************/
static void gotoxy(int x, int y)
{
  COORD  pos  = {x, y};
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hOut, pos);
}
