#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char **dstr_read()

{

    int n=10,i = 0;

 //   scanf("%*[\n]"); 
    /*this will read the \n in stdin and not store it anywhere. So the next call to 
     * scanf will not be interfered with */
    char **str;
    str = malloc(n * sizeof(char *));
     char terminate[]="exit()\n";
	int a;

    for(i = 0; i < n; i++)
    {
       str[i] = malloc(100 * sizeof(char));

	fgets(str[i],100,stdin);
	printf("%s",str[i]);
       a=strcmp (str[i],terminate);
	printf("%d",a);
        if (a==0){
		printf("????????");
		break;
	}
    }
    if (str == NULL) {
      printf("Error: out of memory ...\n");
       exit(1);

    }
	for(int j=0;j<i;j++){
	printf("%s",str[j]);
	}
       return str;

}

int main ()

{

   char **content;

   printf("Start writing here ----\n");
   content = dstr_read();

   free (content);

   return 0;

}
//Reads a string using dynamic memory allocation for strings
