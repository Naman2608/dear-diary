#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Versioned by Naman Chabbra

// Create a new Entry
void add_entry(){
	char text[100];
	printf("\nStart Writting...\n");
	FILE *fp;
	fgets(text,99,stdin);

	fp= fopen("diary.txt","a+");
	if (fp == NULL){
		printf("Failed to Open the File, Please check the file name\n");
		exit(0);
	}

	fputs(text,fp);
	fclose(fp);
}

// Displaying Help Menu
void help_menu(){
	printf("\nWelcome to Help Menu\n");
}

// Handling invalid arguments
void invalid_args()
{
	printf("Invalid Argument(s), Please use '-h' for more information\n");
}

int main(int argc, char const *argv[])
{
	// int i = 0;
	if(argc > 1) {
		printf("%d Argument(s) Recieved,\n", argc-1); // Checking the Arguments
		for (int i = 1; i < argc; i++)
		{
			printf("Argument %d : %s\n", i, argv[i]);
			// Redirecting to help menu
			if(! strcmp(argv[i], "-h")) {
				help_menu();
			}
				// Redirecting to New Entry
			else if(! strcmp(argv[i], "-new")) {
				add_entry();
			}
				// Handling any other argument entered other than above
			else {
				invalid_args();
			}
		}
	}
	// Handling no arguments passed
	else {
		printf("Please use '-h' for more information\n");
	}
	return 0;
}
