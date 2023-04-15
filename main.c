/*
	main.c
	Works as an Entry Point for the Application
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TimeString.h" // To Get the Current Time in a String

// Create a new Entry
void add_entry()
{
	FILE *fp; // file pointer
	int n = 3, i = 0;
	char **text;					   // 2D array
	text = malloc(n * sizeof(char *)); // Allocating only One block of memory for first line

	char terminate[] = "exit()\n"; // Termination array for exit diary writing
	printf("\nStart Writting...");
	// Just Storing Time and a line break as default for every file ------>
	char Date_Time[50];
	sprintf(Date_Time, "\n%s\n@%s\nDear Diary,", DD_Str, TT_Str);
	printf("\n%s\n", Date_Time);
	text[0] = malloc(10 * sizeof(char));
	text[0] = Date_Time;
	text[1] = malloc(2 * sizeof(char));
	text[1] = "\n";
	// --------------------------------------------------------------------<
	for (i = 2; i < n; i++)
	{
		text[i] = malloc(100 * sizeof(char));

		fgets(text[i], 100, stdin);

		if (strcmp(text[i], terminate) == 0)
		{
			break;
		}
		if (i >= n - 1)
		{
			n++;
			text = realloc(text, (n + 1) * sizeof(char *));
		}
	}
	if (text == NULL)
	{
		printf("Error: out of memory ...\n");
		exit(1);
	}

	fp = fopen(DD_Str, "a+");
	if (fp == NULL)
	{
		printf("Failed to Open the File, Please check the file name\n");
		exit(0);
	}
	for (int i = 0; i < n - 1; i++)
	{

		fputs(text[i], fp);
	}

	fclose(fp);
}
// Opening Diary
void open_Diary(void)
{
	char *file_name;
	printf("Enter the Date for Dairy Entry in the following format :  DD-MM-YY \n for eg:(23-4-2023) \n");
	scanf("%s", file_name);

	FILE *file = fopen(file_name, "r");
	if (file == NULL)
	{
		printf("%s\n", "No Dairy exist");
	}
	else
	{
		char c;
		while ((c = fgetc(file)) != EOF) //Read the file contents and print them.
		{
			printf("%c", c);
		}
	}
	fclose(file);
}
// Displaying Help Menu
void help_menu()
{
	printf("\n\nDear-Diary is a Simple & Elegant Diary Writting Software that provides an easy to use CLI Interface.\nYou can support the development by forking the Github repository at 'https://github.com/Naman2608/diary'\n");
	printf("\nUsage :\n\t main <command>\n");
	printf("\nAvailable Commands : \n");
	printf("\t-new : Create a New Diary Entry\n\t-h : Open Help Menu\n\t-o : Open an old Diary Entry\n");
}

// Handling invalid arguments
void invalid_args()
{
	printf("Invalid Argument(s), Please use '-h' for more information\n");
}

int main(int argc, char const *argv[])
{
	int tm_isdst; /* Daylight Savings Time flag */
	getTheTime();
	// printf("THE TIME IS : %s\n", TT_Str);
	// int i = 0;
	if (argc > 1)
	{
		printf("%d Argument(s) Recieved,\n", argc - 1); // Checking the Arguments
		for (int i = 1; i < argc; i++)
		{
			printf("Argument %d : %s\n", i, argv[i]);
			// Redirecting to help menu
			if (!strcmp(argv[i], "-h"))
			{
				help_menu();
			}
			// Redirecting to New Entry
			else if (!strcmp(argv[i], "-new"))
			{
				add_entry();
			}
			// Opening the diary
			else if (!strcmp(argv[i], "-o"))
			{
				open_Diary();
			}
			// Handling any other argument entered other than above
			else
			{
				invalid_args();
			}
		}
	}
	// Handling no arguments passed
	else
	{
		help_menu();
		printf("\n---------------------------------------------\nPlease use '-new' to create a new Diary Entry\n---------------------------------------------\n");
	}
	return 0;
}
