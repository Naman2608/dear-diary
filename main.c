#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TimeString.h"

getTheTime();


// Create a new Entry
void add_entry()
{
	FILE *fp;
	int n = 3, i = 0;
	char **text;					   // 2D array
	text = malloc(n * sizeof(char *)); // Allocating only One block of memory for first line

	char terminate[] = "exit()\n"; // Termination array for exit diary writing
	printf("\nStart Writting...\n");
        char *currentDate = __DATE__;
	printf("\n%s\n", currentDate);
	text[0] = malloc(10 * sizeof(char));
	text[0]= currentDate;
//	char line[]="\n";
	text[1] = malloc(2 * sizeof(char)); 
        text[1] = "\n";

//	strcat(currentDate,line);
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

	fp = fopen("diary.txt", "a+");
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

// Displaying Help Menu
void help_menu()
{
	printf("\nDear-Diary Help Menu\nDear-Diary is a Simple & Elegant Diary Writting Software that provides an easy to use CLI Interface.\nYou can support the development by forking the Github repository at 'https://github.com/Naman2608/diary'\n");
	printf("Usage : main <command>");
	printf("\nAvailable Commands : \n");
	printf("-new : Create a New Diary Entry\n-h : Open Help Menu\n-o : Open an old Diary Entry");
}

// Handling invalid arguments
void invalid_args()
{
	printf("Invalid Argument(s), Please use '-h' for more information\n");
}

int main(int argc, char const *argv[])
{
    printf("THE TIME IS : %s", DD_Str);
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
		printf("Please use '-h' for more information\n");
	}
	return 0;
}
