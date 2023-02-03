// Created by Ashu Sharma on 03-02-2023.
// This file is dedicated to providing dates & time Strings and dealing with time

#ifndef DEAREST_DIARY_TIMESTRING_H
#define DEAREST_DIARY_TIMESTRING_H

#endif //DEAREST_DIARY_TIMESTRING_H

#include <string.h>
#include <stdlib.h>
#include <time.h >


// Get Time String
char getTheTime(){
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t); // storing the date/month/and year to a structure
    int DD = tm.tm_mday,   // The Current Date
        MM = tm.tm_mon+1, // Here 0 = January and 11 = December, so an increment is made to get the dateString
        YY = tm.tm_year+1900; // This returns the total number of years since 1900, so adding 1900 will get the current dateString

    // Hey Naman! I'll need your help here

    char prefix[20];
    snprintf(prefix, sizeof(prefix),"%s: %s: %s",DD,MM,YY);
    printf("DD");
    printf("DD/MM/YY --> %s", prefix);

/*    int DD_length = snprintf( NULL, 0, "%d", DD );
    int MM_length = snprintf( NULL, 0, "%d", MM );
    int YY_length = snprintf( NULL, 0, "%d", YY );
    char* DD_str = malloc( DD_length+ 1 );
    snprintf( DDstr, length + 1, "%d", x );*/

}


// Concatenate to Time String
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}