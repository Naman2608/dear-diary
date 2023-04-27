#include <stdio.h>

int main(){

char chh;
    FILE *fp = fopen("etc/status.txt","r");
    if (fp == NULL)
	{
		printf("No File exist");
		exit(1);
	}
	while(1){
		chh = fgetc(fp);
		if(chh == '0' || chh == '1'){
			break;
		}
		if (chh == EOF){
			exit(1);
		}

	}
	fclose(fp);
    
	if (chh == '0'){

		printf("%c",chh);

	}
	else if(chh=='1'){

		printf("%c",chh);
		
	}
	else{
		exit(1);
	}



	return 0;
}