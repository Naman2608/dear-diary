// Created by Ashu Sharma on 03-02-2023.
// This file provides time in String format for File saving, File Opening & Time Printing Purposes

#ifndef DEAREST_DIARY_TIMESTRING_H
#define DEAREST_DIARY_TIMESTRING_H

#endif // DEAREST_DIARY_TIMESTRING_H

int DD, MM, YY, TH, TM, TS;
char DD_Str[12];
char TT_Str[12];

// Get Time String
void getTheTime()
{
    time_t rawtime;
    struct tm *tm;
    time(&rawtime);
    tm = localtime(&rawtime);
    tzset();
    printf("Current local time and date: %s", asctime(tm));
    // storing the date/month/and year to a structure
    DD = tm->tm_mday,            // The Current Date
    MM = tm->tm_mon + 1,     // Here 0 = January and 11 = December, so an increment is made to get the dateString
    YY = tm->tm_year + 1900; // This returns the total number of years since 1900, so adding 1900 will get the current dateString
    TH = tm->tm_hour;
    TM = tm->tm_min;
    TS = tm->tm_sec;
    // Storing the resulting Time Values in a string using sprintf()
    sprintf(DD_Str, "%d-%d-%d", DD, MM, YY); // DD_Str stores Date in a DD-MM-YY format
    sprintf(TT_Str, "%d:%d:%d", TH, TM, TS); // TT_Str stores Time in a HH-MM-SS format
}
