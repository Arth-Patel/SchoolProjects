#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char** argv){
	if (argc>2){
		printf("Too many arguments");
		return 1;
	} else if (argc<2){
		printf("not enough arguments");
		return 1;	
	}
	int counter=0;
	int repeat=0;
	while(argv[1][counter]!='\0'){//removes any arguments with digits
		if(isdigit(argv[1][counter])){
			printf("error \n");
			return 0;
		}
		counter++;
	}
	counter=0;
	char compareto='0';
	while(argv[1][counter]!='\0'){	
		if(argv[1][counter]==compareto){	
			repeat++;//checks if its a repeat and stores it
		}else {
			if(repeat!=0){
				printf("%d",repeat);
			}
			repeat=1;
			compareto=argv[1][counter];
			printf("%c",compareto);
		}
		counter++;//prints the number
		if(argv[1][counter]=='\0'){
			printf("%d",repeat);
		}
	}
	printf("\n");
	return 0;
}
