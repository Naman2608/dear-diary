#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define MAX_PASSWORD_LENGTH 20

void disableEcho() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void enableEcho() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

char* mainPASS() {
    char password[MAX_PASSWORD_LENGTH + 1];
    char storedPassword[] = "mysecretpassword";  // Change this to your desired password

    printf("Enter the password: ");
    fflush(stdout);

    disableEcho();

    int i = 0;
    char ch;
    while ((ch = getchar()) != '\n' && i < MAX_PASSWORD_LENGTH) {
        if (ch == '\b' && i > 0) {
            printf("\b \b");  // Move back, erase the character, move back again
            i--;
        } else {
            password[i++] = ch;
            printf("*");  // Print asterisk instead of the character
        }
    }
    password[i] = '\0';

    enableEcho();

    printf("\n");
    char *pass= &password[0];

    return pass;

    // if (strcmp(password, storedPassword) == 0) {
    //     printf("Access granted!\n");
    //     // Add your code here for what to do after successful authentication
    // } else {
    //     printf("Access denied!\n");
    //     // Add your code here for what to do after unsuccessful authentication
    // }

    // return 0;
}
