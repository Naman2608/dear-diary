// Created by Ashu Sharma on 03-02-2023.
// This file is dedicated for experimental features

#include <stdio.h>
#include <time.h>

#include "TimeString.h"

int main(void) {
    /*time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("%s", asctime(tm));*/
    /*time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("Current Date: %d-%d-%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);*/
    /*char str1[7] = "Ashu", str2[7] = "sharma";

    printf("%s", concat(str1, str2));*/
    printf("exps.c");
    getTheTime();

    return 0;
}