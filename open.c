#include "open.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TimeString.h"
#include "randomD.h"

#define DIARY_DIR "entries"

// Opening Diary
// char DD_Str[12];
void open_Diary(void)
{
	FILE *fp1 = fopen("etc/.today","w");
	if(fp1 == NULL){
		printf("You have not written anything today");
		exit(1);
	}
	else{
		fputs(DD_Str,fp1);
	}
	fclose(fp1);
    
	char *file_name = malloc(sizeof(char) * 20);
	printf("Enter the Date for Dairy Entry in the following format :  DD-MM-YY \n for eg:(23-04-2023) \n");
	scanf("%s", file_name);

    if(!strcmp(file_name,"last")){
    	
    	strcpy(file_name,open_Last());
    	// char * last = open_Last();
    	// printf("%s",last);
    }
    else if(!strcmp(file_name,"today")){
    	
    	strcpy(file_name,open_Today());
    }
    else if(!strcmp(file_name,"random")){
    	
    	strcpy(file_name,randomDiary());
    }

	char filePath[100];
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
		printf("No Diary found for the date : %s", file_name);
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