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

	// Redirecting to help menu
	if (argc == 1 || !strcmp(argv[1], "-h"))
	{
		// Handling no arguments passed
		help_menu();
		printf("\n---------------------------------------------\nUse ./diary -new to start writing \n\n");
	}
	else
	{	
		// Redirecting to New Entry
		if (!strcmp(argv[1], "-new"))
		{
			Authenticating();
			add_entry();
		}
		// Opening the diary
		else if (!strcmp(argv[1], "-o"))
		{
			Authenticating();
			open_Diary();	
		}
		else if (!strcmp(argv[1], "-rm"))
		{
			
		}
		else if (!strcmp(argv[1], "-set"))
		{
			Authenticating();
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
	}
	return 0;
}

