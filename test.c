// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// int main()
// {
//    time_t epoch = time(NULL);

//    putenv("TZ=GMT+5:30");
//    tzset();
//    printf("Time: %s", ctime(&epoch));

//    return (0);
// }

// #define _GNU_SOURCE /* for tm_gmtoff and tm_zone */

// #include <stdio.h>
// #include <time.h>

// /* Checking errors returned by system calls was omitted for the sake of readability. */
// int main(void)
// {
//    time_t t = time(NULL);
//    struct tm lt = {0};

//    localtime_r(&t, &lt);

//    printf("Offset to GMT is %lds.\n", lt.tm_gmtoff);
//    printf("The time zone is '%s'.\n", lt.tm_zone);

//    return 0;
// }

// /* localtime example */
// #include <stdio.h>
// #include <time.h>

// int main()
// {
//    time_t rawtime;
//    struct tm *timeinfo;

//    time(&rawtime);
//    timeinfo = localtime(&rawtime);
//    printf("Current local time and date: %s", asctime(timeinfo));
//    int tz;
//    setenv("TZ", "GMTGMT-1,M3.4.0/01,M10.4.0/02", 1);
//    tzset();

//    tz = getenv("TZ");
//    printf("%d", tz);
//    return 0;
// }
#define _POSIX_SOURCE
// #include <env.h>
#include <stdio.h>
#include <time.h>
int main()
{
   time_t rawtime;
   struct tm *info;
   time(&rawtime);
   info = localtime(&rawtime);
   setenv("TZ", "IST-05:30:00", 1);
   tzset();
   printf("Current local time and date: %s", asctime(info));
   return (0);
}