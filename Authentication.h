// Created by Naman Chhabra on 15-06-2023.
// This file provides Diary Password/Key Protected Authentication.

#ifndef DIARY_AUTHENTICATION_H
#define DIARY_AUTHENTICATION_H


int check_pass_status (void ); 
void set_Pass();
int Authentication(char usr_key[]);
void sleep_ms(int milliseconds);
int mainAuthen(void);
void Authenticating();


#endif