#include "new.h"
#include <stdio.h>
#include <stdlib.h>
#include "TimeString.h"
#include <string.h>
#define DIARY_DIR "entries"

#ifdef _WIN32
#include <Windows.h>

#else
#include <sys/stat.h>
#endif
// Use this SOON <-->
void xor_encrypt_decrypt(char **input,int i, const char *key) {
    for (int j = 0; input[i][j] != '\0'; j++) {
        input[i][j] = input[i][j] ^ key[j % strlen(key)];
    }
}
// Create a new Entry
void add_entry()
{
	FILE *fp; // FILE structure type pointer store all the related data of file
	int n = 3, i = 0;
	char **text;		      // 2D array
	text = malloc(n * sizeof(char *)); // Allocating only One block of memory for first line
    
	char terminate[] = "exit()\n"; // Termination array for exit diary writing

	printf("\nStart Writting...\nWhen you're finished writing add a new line, type in `exit()` and press enter to save & exit\n");
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
		text[0][i]=text[0][i] ^ 'X';
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
			text[i][j]= text[i][j] ^ 'X' ;
		}
		// xor_encrypt_decrypt(&text[i][0],i,"mysecratekey");
        // reallocating memory for next line
		if (i >= n - 1)
		{
			n++;
			text = realloc(text, (n + 1) * sizeof(char *));
		}
	}
	if (text == NULL)
	{
		printf("Error: f memory ...\n");
		exit(1);
	}
     // creating a file with name of Date
	char filePath[100];
    sprintf(filePath, "./" DIARY_DIR "/%s.txt", DD_Str);
    fp = fopen(filePath, "a+");
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
	FILE *fp2 = fopen("etc/.last","w");
	if(fp2 == NULL){
		printf("Error");
		exit(1);
	}
	else{
		fputs(DD_Str,fp2);
		fclose(fp2);
	}
}

int create_diary_dir() {
 
#ifdef _WIN32
    if (CreateDirectory(DIARY_DIR, NULL)) {
        return 1; // Directory created successfully, return success
    } else if (GetLastError() == ERROR_ALREADY_EXISTS) {
        return 1; // Directory already exists, return success
    } else {
        fprintf(stderr, "Error creating directory\n");
        return 0; // Return failure
    }
#else
    struct stat st = {0};
    if (stat(DIARY_DIR, &st) == -1) {
        if (mkdir(DIARY_DIR, 0700) == -1) {
            fprintf(stderr, "Error creating directory\n");
            return 0; // Return failure
        }
        return 1; // Directory created successfully, return success
    } else if (!S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Error creating directory\n");
        return 0; // Return failure (the path exists but is not a directory)
    }

    return 1; // Directory already exists, return success
#endif
}


