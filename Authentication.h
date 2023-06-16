// Created by Naman Chhabra on 15-06-2023.
// This file provides Diary Password/Key Protected Authentication.

#ifndef DIARY_AUTHENTICATION_H
#define DIARY_AUTHENTICATION_H
#endif

#ifdef WIN32

#else
    #include "HidePassEnter.h"
#endif

// Check if  password is not already set
// return true if user exist
// return false if user is new
int check_pass_status (void ){

    char chh;
    FILE *fp = fopen("etc/status.txt","r"); // opening status.txt in etc directory
    // if unsuccessful attempt then fp returns NULL
    if (fp == NULL)
	{
		printf("No File exist");
		exit(1);
	}
    
	while(1){
		chh = fgetc(fp); // getting the character from the file
		// printf("%c",chh);
		if(chh == '0' || chh == '1'){
			break;
		}
		if (chh == EOF){
			exit(1);
		}

	}
	fclose(fp); // closing the file
    
	if (chh == '0'){

		return 0;

	}
	else if(chh=='1'){
		return 1;
	}
	else{
		exit(1);
	}

}
// this  module ask key from user and store in directory 
void set_Pass(){
	
	char key[20];
	int i =0;
    printf("Set your Key\nEnter a Key for diary access within 10 characters\n");
    scanf("%s",key);
    // gets(key);
    // while(key[i]!='\0'){
    // 	key[i] = key[i] +4;

    // 	i++;
    // }
    FILE *fp = fopen("etc/.pass","w");
    fputs(key,fp); // copy the key string to the file
    // free(key);
 	fclose(fp);
 	// free(fp);
    
    // updating the password status in file status.txt
    // FILE *fp;
    char ch = '1';  
    fp = fopen("etc/status.txt","w");
	fputc(ch,fp);
	fclose(fp);


}
// This module do authentication from the stored key in file
int Authentication(char usr_key[]){

    int i=0;
    char saved_key[20];
    FILE *fy = fopen("etc/.pass","r");
    // if unsucessful attempt then fy returns NULL
     if (fy == NULL)
	{
		printf("No File exists");
		exit(1);
	}
	// accessing the key from file 
	fgets(saved_key,20,fy);
    fclose(fy);
	if (strcmp(usr_key,saved_key)==0)
	{
		return 1;
		
	}
	else
	{
		return 0;
	}        

}
/**
 * Cross-platform sleep function for C
 * @param int milliseconds
 */
void sleep_ms(int milliseconds)
{
    #ifdef WIN32
        Sleep(milliseconds);
    #elif _POSIX_C_SOURCE >= 199309L
        struct timespec ts;
        ts.tv_sec = milliseconds / 1000;
        ts.tv_nsec = (milliseconds % 1000) * 1000000;
        nanosleep(&ts, NULL);
    #else
        usleep(milliseconds * 1000);
    #endif
}
// Main Authentication Function
int mainAuthen(void){

	int status = check_pass_status();
    // printf("%d",status); // just check
    
	if (status==0)
	{
		set_Pass();
		printf("Password updated\n Rerun the diary to continue using");
		exit(EXIT_SUCCESS);
	}

	char usr_key[20];
	#ifdef WIN32
   	      printf("\nEnter Password :\n");
              int i;
              for (i = 0; i < 20; i++) {
         	 usr_key[i] = getch();
   	 	 if (usr_key[i] == '\r' || usr_key[i]=='\n') {
                        usr_key[i] = '\0';
   			   break;
                  }
               printf("*");
               }
        #else
             char *pusr_key = mainPASS();
             strcmp(usr_key,pusr_key);

        #endif
	if (!Authentication(usr_key))
	{
		printf("Invalid Key\n");
		return 0;
		
	}
	else{
		printf("\nAuthentication Successful!\n");
		return 1;
	}

}
