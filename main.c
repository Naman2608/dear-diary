/*
	main.c
	Works as an Entry Point for the Application
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "TimeString.h" // To Get the Current Time in a String
#include "Authentication.h" // To use Password Functionaliy
#include "help.h"
#include "new.h"
#include "open.h"


// Program Starts from here ---
int main(int argc, char const *argv[])
{
	if (!create_diary_dir()) {
        exit(EXIT_FAILURE);
    }

	int tm_isdst;  // Daylight Savings Time flag
	getTheTime();  // getTheTime() is function of TimeString.h
	// printf("THE TIME IS : %s\n", TT_Str);
	if (argc == 1 || !strcmp(argv[1], "-h")){
	
		// Handling no arguments passed
		help_menu();
		printf("\n---------------------------------------------\nUse ./diary -new to start writing \n\n");

	}
	else{
		// Authetication
		int count = 1;
		while (count <=3){
			if (mainAuthen())
			{
				break;
			}
			count++;
			if (count==4)
			{

				fprintf(stderr,"\nAuthentication Limit Exceeded\nExiting ...\n");
				sleep_ms(1000);
				exit(EXIT_FAILURE);

			}

		}
		sleep_ms(1000);
        
		// printf("%d Argument(s) Recieved,\n", argc - 1); // Checking the Arguments
		// for (int i = 1; i < argc; i++)
		// {
			// printf("Argument %d : %s\n", i, argv[i]);
			
			// Redirecting to help menu
			if (!strcmp(argv[1], "-h"))
			{
				help_menu();
			}
			// Redirecting to New Entry
			else if (!strcmp(argv[1], "-new"))
			{
				add_entry();
			}
			// Opening the diary
			else if (!strcmp(argv[1], "-o"))
			{
				open_Diary();	
			}
			else if (!strcmp(argv[1], "-rm"))
			{
				
			}
			else if (!strcmp(argv[1], "-set"))
			{
				// set_Pass();
				if (check_pass_status())
				{
					printf("Key already exists! A key must be unique & not the same as before\n");
				}
				
				set_Pass();   
				
			}
			// Handling any other argument entered other than above
			else
			{
				invalid_args();
			}
        // }
	}
	return 0;
}

