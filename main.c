/*
	main.c
	Works as an Entry Point for the Application
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TimeString.h" // To Get the Current Time in a String

void open_Diary(void);
void help_menu();
void add_entry();
void invalid_args();

// Program Starts from here ---
int main(int argc, char const *argv[])
{

	int tm_isdst;   // Daylight Savings Time flag
	getTheTime();  // getTheTime() is function of TimeString.h
	// printf("THE TIME IS : %s\n", TT_Str);
	// int i = 0;

	FILE *fp;

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
		printf("tm_isdst %d-> ", tm_isdst);
		help_menu();
		printf("\n---------------------------------------------\nPlease use '-new' for Writing about you day \n");
	}
	return 0;
}

// Create a new Entry
void add_entry()
{
	FILE *fp; // FILE structure type pointer store all the related data of file
	int n = 3, i = 0;
	char **text;		      // 2D array
	text = malloc(n * sizeof(char *)); // Allocating only One block of memory for first line

	char terminate[] = "exit()\n"; // Termination array for exit diary writing

	printf("\nStart Writting...\nfor Exit type exit()\n");
	// Just Storing Time and a line break as default for every file ------>
	char Date_Time[50];
	sprintf(Date_Time, "\n%s\n@%s\nDear Diary,\n", DD_Str, TT_Str);
	printf("\n%s\n", Date_Time);
	// Allocating memory and variable for universal cases of every diary writing.
	text[0] = malloc(50 * sizeof(char));
	text[0] = Date_Time;

    // Encripting Date_Time
	for (int i = 0; text[0][i]!='\0'; ++i)
	{
		text[0][i]=text[0][i]+3;
	}
	
	// --------------------------------------------------------------------<
	for (i = 1; i < n; i++)
	{
		text[i] = malloc(100 * sizeof(char));
         // for input 
		fgets(text[i], 100, stdin);

         // comparing termination ("exit()" with input text)
		if (strcmp(text[i], terminate) == 0)
		{
			break;
		}

		// for encription purpose 
		for (int j = 0;text[i][j]!='\0'; ++j)
		{
			text[i][j]= text[i][j] +3 ;
		}
        // reallocating memory for next line
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
     // creating a file with name of Date
	fp = fopen(DD_Str, "a+");
	// if file not created sucessfully then it will exit code 
	if (fp == NULL)
	{
		printf("Failed to Open the File, Please check the file name\n");
		exit(1); // A non zero value in exit means abnormal termination of program
	}

     // copying content of text to file
	for (int i = 0; i < n - 1; i++)
	{

		fputs(text[i], fp);
	}
     // closing file the buffer assosited with file is removed from the memory
	fclose(fp);
}
// Opening Diary
void open_Diary(void)
{
	char *file_name = malloc(sizeof(char) * 20);
	printf("Enter the Date for Dairy Entry in the following format :  DD-MM-YY \n for eg:(23-4-2023) \n");
	scanf("%s", file_name);

	FILE *fp = fopen(file_name, "r+");
	if (fp == NULL)
	{
		printf("No Dairy exist");
		free(file_name);
		exit(1);
	}
	else
	{
		char c;
		while ((c = fgetc(fp)) != EOF) //Read the file contents from buffer untill EOF(macro) encontered.
		{
			printf("%c", c-3); // c-3 for decription
		}
	}
	fclose(fp);
	free(file_name);
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