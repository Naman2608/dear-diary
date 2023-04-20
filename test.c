#include <stdio.h>

int main(){


	char text[2][9];
	int n=2;


    for (int i = 0; i < n; ++i)
    {
    	gets(text[i]);
    }

     for (int i = 0; i<n; ++i)
	{
		for (int j = 0;text[i][j]!='\0'; ++j)
		{
			text[i][j]=text[i][j]+3;
			printf("%c",text[i][j]);
		}
	}



	return 0;
}