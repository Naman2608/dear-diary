
#include <time.h>
#include <stdio.h>
#include "TimeString.h"

int DD, MM, YY, TH, TM, TS;
char DD_Str[12],TT_Str[12];

void getTheTime()
{
    time_t rawtime;
    struct tm *tm;
    time(&rawtime);
    tm = localtime(&rawtime);
    tzset();

    // storing the date/month/and year to a structure
    DD = tm->tm_mday,        // The Current Date
    MM = tm->tm_mon + 1,     // Here 0 = January and 11 = December, so an increment is made to get the dateString
    YY = tm->tm_year + 1900; // This returns the total number of years since 1900, so adding 1900 will get the current dateString
    TH = tm->tm_hour;
    TM = tm->tm_min;
    TS = tm->tm_sec;
    // Storing the resulting Time Values in a string using sprintf()
    sprintf(DD_Str, "%02d-%02d-%d", DD, MM, YY); // DD_Str stores Date in a DD-MM-YY format
    sprintf(TT_Str, "%d:%d:%d", TH, TM, TS); // TT_Str stores Time in a HH-MM-SS format
}
