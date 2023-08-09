#include <stdio.h>
#include "help.h"

// Displaying Help Menu
void help_menu()
{
	printf("\n\nWelcome to Dear-Diary \nA Journal/Diary Writing Software providing a simple and easy to use CLI Interface.\nSupport the development by forking the Github repository at 'https://github.com/Naman2608/diary'\n");
	printf("\nUsage :\n\t diary <command>\n");
	printf("\nAvailable Commands : \n");
	printf("\t-new : Create a New Diary Entry\n\t-h : Open Help Menu\n\t-o : Open an old Diary Entry\n\t-set : Set\\/Reset Password\n\t-today : Open Today's Diary Entry\n\t-last : Open Last Diary Entry\n\t-random : Open Random Diary Entry\n\t");
}

// Handling invalid arguments
void invalid_args()
{
	printf("Invalid Argument(s), Please use '-h' for more information\n");
}