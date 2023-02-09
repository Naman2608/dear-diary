#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <math.h>

void mainMenu(char[]);
void accountMenu();
int login(char[], char[]);
int validateMenuSelection(char[], int, int);
int validateReadSelection(char[], int, int);
int checkUserExists(void);
void writeUserToFile(char[], char[], char[]);
void writeDiaryEntryToFile(char[]);
void createEntry(void);
void getEntries(void);
int getNumEntries(void);
void displayDiaryEntry(char[]);
void resetPasswordOrUsername(int);

char *userDir = "user.txt";
char userName[20];
DIR *dir;
struct dirent *ent;

void displayDiaryEntry(char entry[])
{
    FILE *file = fopen(entry, "r");
    if (file == NULL)
    {
        printf("%s\n", "null");
    }
    else
    {
        printf("\n");
        char c;
        int count = 0;
        while ((c = fgetc(file)) != EOF) //Read the file contents and print them.
        {
            printf("%c", c);
            count++;
            if (count >= 200 && isspace(c)) //Go to a new line when over 200 characters have been printed and a free space appears.
            {
                printf("\n");
                count = 0;
            }
        }
    }
    fclose(file);
    char selection[64];
    printf("\n%s\n", "Enter 1 to return to diary entries: ");
    fgets(selection, 63, stdin);
    getEntries();
}

void getEntries(void)
{
    int numFiles = getNumEntries();
    if (numFiles > 0) //If there are files to read
    {
        printf("\n%s\n", "Select Diary Entry;");
        if ((dir = opendir("entries/")) != NULL)
        {
            char **files = (char **)calloc(numFiles, sizeof(char *)); // allocate memory for the number of diary entries that exist
            int k = 0;
            while ((ent = readdir(dir)) != NULL) // while there is a new entry execute
            {
                if (strcmp(".", ent->d_name) != 0 && strcmp("..", ent->d_name)) // filter of non text files
                {
                    files[k] = (char *)calloc(strlen(ent->d_name), sizeof(char *)); // allocate memory for the file name
                    strcpy(files[k], ent->d_name);                                  // copy the file name to the array
                    printf("%d%s%s\n", k + 1, ": ", files[k]);                      // print the file name as a menu option. k+1 is so 0 can be an exit option
                    k++;
                }
            }
            int check = -1;                                                 // -1 if the fail state
            char *selection = (char *)calloc(numFiles + 1, sizeof(char *)); //Allocate memory based on the number of possible selections there are
            printf("%s\n", "(Enter 0 to return to main menu)");
            while (check == -1) //Get input for which file to read
            {
                fgets(selection, (numFiles + 2), stdin);
                check = validateReadSelection(selection, check, k);
            }
            selection[strcspn(selection, "\n")] = '\0'; //Remove the newline
            if (strcmp(selection, "0") == 0)            //Return to the main menu
            {
                for (int j = 0; j < numFiles; j++)
                {
                    free(files[j]);
                }
                free(selection);
                free(files);
                closedir(dir);
                mainMenu(userName);
            }
            char entryDir[] = "entries/";
            strcat(entryDir, files[check - 1]); //Create the directory to read
            displayDiaryEntry(entryDir);
            for (int j = 0; j < numFiles; j++)
            {
                free(files[j]);
            }
            free(selection);
            free(files);
            closedir(dir);
        }
        else
        {
            perror("");
            exit(0);
        }
    }
    else
    {
        printf("%s\n", "No diary entries could be found");
        mainMenu(userName);
    }
}

int validateReadSelection(char selection[], int check, int numSelections)
{
    int tmp = numSelections;
    int digits = 0;
    while (tmp != 0) // Get the amount of digits in numSelections
    {
        tmp = tmp / 10;
        digits++;
    }

    if ((strlen(selection) - 1) > digits) //Check if input has more digits than diary entries
    {
        check = -1;
    }

    if (sscanf(selection, "%d", &check) != 1) //Check if input is not a number
    {
        check = -1;
    }

    if (check > numSelections || check < 0) //Check if input is out of bounds
    {
        check = -1;
    }

    if (check == -1) //Print error if one of the above triggered
    {
        printf("%s\n", "Invalid input try again:\n");
    }
    return check;
}

int getNumEntries(void)
{
    int numFiles = 0;
    int i = 0;
    if ((dir = opendir("entries/")) != NULL)
    {
        while ((ent = readdir(dir)) != NULL) //Get files within the given directory
        {
            if (strcmp(".", ent->d_name) != 0 && strcmp("..", ent->d_name) != 0) //Ignore the non diary entry files and count the rest
            {
                numFiles++;
            }
            else
            {
                if (i >= 2) //If there are not diary entries return
                {
                    closedir(dir);
                    return numFiles;
                }
            }
            i++;
        }
    }
    closedir(dir);
    return numFiles;
}

void writeUserToFile(char name[], char pw[], char printMsg[])
{
    FILE *file = fopen(userDir, "w");

    if (file == NULL)
    {
        perror("file can't be opened \n");
        exit(0);
    }
    else
    {
        fprintf(file, "%s%s", name, pw); //Append the user file
        fclose(file);
        printf("%s\n", printMsg); //Print a message specific to whether a new account is created, password is changes or username is changed
        mainMenu(userName);
    }
}

void writeDiaryEntryToFile(char entry[])
{
    char path[] = "entries/";
    int tmp = getNumEntries();
    if (tmp != 0) //Create the start of the file name. Assigns an id to each file at the beginning and increments
    {
        char *numEntries = malloc(sizeof(char) * (int)(tmp));
        sprintf(numEntries, "%d", tmp);
        strcat(path, "[");
        strcat(path, numEntries);
        free(numEntries);
    }
    else
    {
        strcat(path, "[");
        strcat(path, "0");
    }
    strcat(path, "]");
    strcat(path, "-");
    //Get the current date and append to the file name >>
    time_t mytime;
    mytime = time(NULL);
    char *ct = ctime(&mytime);
    ct[strcspn(ct, "\n")] = '\0';
    while (ct[strcspn(ct, ":")] != NULL)
    {
        ct[strcspn(ct, ":")] = '-';
    }
    while (ct[strcspn(ct, " ")] != NULL)
    {
        ct[strcspn(ct, " ")] = '-';
    }
    strcat(path, ct);
    strcat(path, ".txt");
    FILE *file2 = fopen(path, "w");

    if (file2 == NULL)
    {
        perror("file can't be opened");
        exit(0);
    }
    else
    {
        fprintf(file2, "%s", entry); //Create the new diary entry file
        fclose(file2);
        printf("%s\n", "Entry saved :)");
        mainMenu(userName);
    }
}

void createEntry(void)
{
#define CHUNK 200
    char tempBuf[CHUNK]; //initial size of the entry buffer
    char *input = NULL;
    size_t inputlen = 0, templen;
    printf("%s\n", "Enter Diary Entry Below:");
    do
    {
        templen = 0;
        fgets(tempBuf, CHUNK, stdin);                   // get user entry into tmpBuf
        templen = strlen(tempBuf);                      // get length of tmpBuf
        input = realloc(input, inputlen + templen + 1); // set input size to that of the temp input array
        if (input == NULL)
        {
            printf("Error reading input please exit and restart Diary Bee");
            free(input);
            mainMenu(userName);
        }
        strcpy(input + inputlen, tempBuf);                        // concat the input string
        inputlen += templen;                                      // get the full input length
    } while (templen == CHUNK - 1 && tempBuf[CHUNK - 2] != '\n'); // if we reach the end of the available string space loop back
    writeDiaryEntryToFile(input);
    free(input);
}

int login(char name[], char pw[])
{
    FILE *file = fopen(userDir, "r");
    char fileContents[2][20];

    int i = 0;
    if (file == NULL)
    {
        perror("file can't be opened \n");
        exit(0);
    }
    else
    {
        char line[100];
        int i = 0;
        while (fgets(line, sizeof(line), file)) //Copy the contents of the user file to an array
        {
            strcpy(fileContents[i], line);
            i++;
        }

        if (strcmp(fileContents[0], name) == 0 && strcmp(fileContents[1], pw) == 0) //Check the user input against the file contents. Return 1 if they match and 0 if not
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int checkUserExists(void)
{
    FILE *file = fopen(userDir, "r");
    char ch;

    if (file == NULL)
    {
        perror("file can't be opened \n");
        exit(0);
    }
    else
    {
        char line[100];
        int i = 0;
        while (fgets(line, sizeof(line), file)) //Read how many lines are in the user file
        {
            i++;
        }

        fclose(file);

        if (i >= 1) //If the file has been written to return 1. If its empty return 0
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int validateMenuSelection(char selection[], int num, int numSelections)
{
    if (strlen(selection) != 2) //Check if the input is not 0-9
    {
        num = -1;
    }

    if (sscanf(selection, "%d", &num) != 1) //Check if the input if not a number
    {
        num = -1;
    }

    if (num > numSelections || num < 0) //Check if the input is out of the bounds of the options
    {
        num = -1;
    }

    if (num == -1) //Print an error if one of the about triggered
    {
        printf("%s\n", "Invalid input try again:\n");
    }
    return num;
}

void mainMenu(char name[])
{
    char selection[64];
    int num = -1;

    while (num == -1)
    {
        name[strcspn(name, "\n")] = 0;
        printf("\n");
        printf(" ,--.\n");
        printf(" \\ /     ,-------------------,\n");
        printf("{|||)< --   Hi %s              \n", name);
        printf(" / \\     `-------------------`\n");
        printf(" `--^\n");
        printf("\n%s\n", "Main Menu");
        printf("%s\n", "1: Read");
        printf("%s\n", "2: Write");
        printf("%s\n", "3: Reset password");
        printf("%s\n", "4: Reset username");
        printf("%s\n", "0: Exit");
        fgets(selection, 63, stdin);
        num = validateMenuSelection(selection, num, 5);
    }

    switch (num)
    {
    case 1:
        getEntries();
        break;

    case 2:
        createEntry();
        break;
    case 3:
        resetPasswordOrUsername(0);
    case 4:
        resetPasswordOrUsername(1);
    case 0:
        exit(0);
        break;

    default:
        break;
    }
}

void resetPasswordOrUsername(int pwOrUser)
{
    FILE *file = fopen(userDir, "r");
    char fileContents[2][20];

    int i = 0;
    if (file == NULL)
    {
        perror("file can't be opened \n");
        exit(0);
    }
    else
    {
        char line[100];
        int i = 0;
        while (fgets(line, sizeof(line), file)) //Read the lines of user file into an array. 0 index is username, 1 index is password.
        {
            strcpy(fileContents[i], line);
            i++;
        }
    }
    if (pwOrUser == 0) //if pwOrUser == 0 change password. if not change username
    {
        char pw[20];
        printf("%s\n", "Enter new password:");
        fgets(pw, 19, stdin);
        writeUserToFile(fileContents[0], pw, "Password updated :)");
    }
    else
    {
        char name[20];
        printf("%s\n", "Enter new username:");
        fgets(name, 19, stdin);
        writeUserToFile(name, fileContents[1], "Username updated :)");
        memset(userName, 0, 20); //Clear the old username
        strcpy(userName, name);  //Assign the new username
    }
    fclose(file);
    mainMenu(userName);
}

void accountMenu(void)
{
    char selection[64];
    int num = -1;                      //-1 is the fail state for user selections
    int checkUser = checkUserExists(); //Check if there is already a user saved
    int numSelections = 2;
    while (num == -1)
    {
        printf("%s\n", "1: Create Account");
        if (checkUser == 1) //if there is a user saved then provide the option to login
        {
            printf("%s\n", "2: Login");
            numSelections = 3;
        }
        printf("%s\n", "0: Exit");
        fgets(selection, 63, stdin);
        num = validateMenuSelection(selection, num, numSelections);
        if (checkUser == 1 && num == 1) //If an account exists user cannot create another
        {
            printf("%s\n", "An account already exists!");
            num = -1;
        }
    }
        int checkLog = 0;
    char name[20];
    char pw[20];

    switch (num)
    {
    case 1:
        printf("%s\n", "Enter new username:");
        fgets(name, 19, stdin);
        printf("%s\n", "Enter new password:");
        fgets(pw, 19, stdin);
        strcpy(userName, name);
        writeUserToFile(name, pw, "Account created :)");
        break;
    case 2:
        do
        {
            printf("%s\n", "Enter username:");
            fgets(name, 19, stdin);
            printf("%s\n", "Enter password:");
            fgets(pw, 19, stdin);
            checkLog = login(name, pw);
            if (checkLog == 1)
            {
                strcpy(userName, name);
                mainMenu(name);
            }
            else
            {
                printf("%s\n", "Incorrect login details. Try again:");
            }
        } while (checkLog == 0);
        break;
    case 0:
        printf("Goodbye!");
        exit(0);
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    printf("%s\n", "---------------WELCOME TO DIARY BEE---------------");
    printf("\n");
    printf("%s\n", "           __         .' '.");
    printf("%s\n", "        _//__)        .   .       .");
    printf("%s\n", "       (8|)_}}-..      .        .");
    printf("%s\n", "        `\\__)   '. . ' ' .  . ");
    printf("\n");
    accountMenu();
    return 0;
}