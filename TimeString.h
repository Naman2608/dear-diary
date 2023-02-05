// Created by Ashu Sharma on 03-02-2023.
// This file is dedicated to providing dates & time Strings and dealing with time

#ifndef DEAREST_DIARY_TIMESTRING_H
#define DEAREST_DIARY_TIMESTRING_H

#endif // DEAREST_DIARY_TIMESTRING_H

// Get Time String
void getTheTime()
{
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t); // storing the date/month/and year to a structure
    DD = tm.tm_mday,   // The Current Date
    MM = tm.tm_mon+1, // Here 0 = January and 11 = December, so an increment is made to get the dateString
    YY = tm.tm_year+1900; // This returns the total number of years since 1900, so adding 1900 will get the current dateString

    sprintf(DD_Str, "%d", DD);
    sprintf(MM_Str, "%d", MM);
    sprintf(YY_Str, "%d", YY);

    printf("%s-%s-%s", DD_Str, MM_Str, YY_Str);
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