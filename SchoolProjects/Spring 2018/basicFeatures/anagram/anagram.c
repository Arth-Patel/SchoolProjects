#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char** argv){
	if (argc>2){ //checks amount of arguments
		printf("Too many arguments");
		return 1;
	} else if (argc<2){
		printf("not enough arguments");
		return 1;	
	}
	int counter=0;
	int counter2=1;
	int counter3=0;
	char temp;
	while(argv[1][counter3]!='\0'){//sorts the letters by using quick sort
		while(argv[1][counter2]!='\0'){
			if (argv[1][counter2]<argv[1][counter]){
				temp=argv[1][counter2];
				argv[1][counter2]=argv[1][counter];
				argv[1][counter]=temp;
			}
			counter++;
			counter2++;
		}	
		counter=0;
		counter2=1;
		counter3++;
	}
	printf("%s \n",argv[1]);
	return 0;
}
