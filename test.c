#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
   time_t epoch = time(NULL);

   putenv("TZ=GMT+5:30");
   tzset();
   printf("Time: %s", ctime(&epoch));

   return (0);
}
