#include "open.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TimeString.h"
#include "randomD.h"
#include <ctype.h>

#define DIARY_DIR "entries"
#define null NULL;

// Opening Diary
// char DD_Str[12];
void open_Diary(char *file_name_t)
{
	FILE *fp1 = fopen("etc/.today","w");
	if(fp1 == NULL){
		printf("You have not written anything today\n Write \n");
		exit(1);
	}
	else{
		fputs(DD_Str,fp1);
	}
	fclose(fp1);
	char *file_name = malloc(sizeof(char) * 20);
	// file_name_t = malloc(sizeof(char) * 20);
	printf("test - %s",file_name_t);
	if(!strcmp(file_name_t,"")){
	    
		printf("Enter the Date for Dairy Entry in the following format :  DD-MM-YY \n for eg:(23-04-2023) \nTry\n\tToday\n\tLast\n\tRandom\n");
		scanf("%s", file_name);

		file_name_t = malloc(sizeof(char) * 20);

		// file_name_t = strlwr(file_name);
		int i = 0;
		// conversion into lowercase --->
		for (; i < strlen(file_name); i++)
		{
			file_name_t[i] = tolower(file_name[i]);
		}
		file_name_t[i] = '\0';
	}
    if(!strcmp(file_name_t,"last")){
    	
    	strcpy(file_name,open_Last());
    	// Assigning back to original file_name from temp
    }
    else if(!strcmp(file_name_t,"today")){
    	
    	strcpy(file_name,open_Today());    	
    }	
    else if(!strcmp(file_name_t,"random")){
    	
    	strcpy(file_name,randomDiary());
    }
    
    // free(file_name_t);
    
	char filePath[100];
	// in case of Random return with .txt so don't have to write again so this is special condition.
    if(strstr(file_name,".txt")) 
    {
	    sprintf(filePath, "./" DIARY_DIR "/%s", file_name);
    }
    else{
    	sprintf(filePath, "./" DIARY_DIR "/%s.txt", file_name);
    }

    FILE *fp = fopen(filePath, "r+");
	if (fp == NULL)
	{
		if(strstr(file_name,".txt")) {
			printf("No Diary found for the date : %s\n", file_name);
		}
		else{
			printf("!!! Invalid Entry !!!\n");
		}
    
		free(file_name);
		exit(1);
	}
	else
	{
		char c;
		while ((c = fgetc(fp)) != EOF) //Read the file contents from buffer untill EOF(macro) encontered.
		{
			printf("%c", c ^ 'X'); // c-3 for decription
		}
	}
	fclose(fp);
	free(file_name);
	
}

char* open_Today(){

	FILE *fp2 = fopen("etc/.today","r");
	if(fp2 == NULL){
		printf("You have not written anything today ! No Diary found \n");
		exit(1);
	}
	else{
		char *str = malloc(sizeof(char) * 20);
		do  {
			str = str;
        }while((fgets(str, 19, fp2) != NULL));
		fclose(fp2);
		return str;
	}

}


char* open_Last(){

	FILE *fp2 = fopen("etc/.last","r");
	if(fp2 == NULL){
		printf(" No Diary found \n");
		exit(1);
	}
	else{
		char *str = malloc(sizeof(char) * 20) ;
		// fgets(str,19,fp2);
		do  {
			str = str;
        }while((fgets(str, 19, fp2) != NULL));
 		
		fclose(fp2);
		return str;
	}

}