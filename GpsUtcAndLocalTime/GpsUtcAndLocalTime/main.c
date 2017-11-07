/**
  ******************************************************************************
  * @file    main.c
  * @author  XinLi
  * @version v1.0
  * @date    24-October-2017
  * @brief   Main program body.
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
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

/* Macro definitions ---------------------------------------------------------*/
/* Type definitions ----------------------------------------------------------*/
/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/
static void gotoxy(int x, int y);

/* Function definitions ------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None.
  * @return None.
  */
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

/**
  * @brief  Move the cursor to the specified position on the text screen.
  * @param  [in] x: X axis coordinates.
  * @param  [in] y: Y axis coordinates.
  * @return None.
  */
static void gotoxy(int x, int y)
{
  COORD  pos  = {x, y};
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hOut, pos);
}
