#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <dirent.h>
#include <cstdlib>
#include <time.h>
#include "randomD.h"

using namespace std ;

void openDir(map<int,string> &);
char * randomDiary();


// int main(int argc, char const *argv[])
// {	
// 	char * s = (char *)malloc(12*sizeof(char));
// 	s = randomDiary();
// 	printf("%s",s);
// 	free(s);
// 	return 0;
// }

char * randomDiary()
{
	map<int,string> mpp;

	openDir(mpp);

	// for(auto i : mpp){
	// 	cout<<"Key "<<i.first<<" "<<"Val "<<i.second<<endl;
	// }

	int N = mpp.size();
	// seed to generate random more uniquely
	srand(time(0));
	int randKey = rand() % N;

	string s = mpp[randKey];
	char *temp = (char *)malloc(12*sizeof(char));
	strcpy(temp,s.c_str());
	return temp;
}

void openDir(map<int,string> &mpp){

	DIR *dr;
	struct dirent *en;
	dr = opendir("./entries");
	int i =0;
	if(dr){
		while((en = readdir(dr)) != NULL)
		{
			// printf("%s\n",en->d_name);
			if(strcmp(en->d_name,"..") && strcmp(en->d_name,".")){
				mpp.insert({i++,en->d_name});
			}
		}
		closedir(dr);
	}
}
