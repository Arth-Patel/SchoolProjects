#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char** argv){
	if (argc>2){//gets right amount of arguments
		printf("Too many arguments");
		return 1;
	} else if (argc<2){
		printf("not enough arguments");
		return 1;	
	}
	int counter=0;
	while (argv[1][counter]!='\0'){
		if(!islower(argv[1][counter])){
			printf("%c",argv[1][counter]);
		}else{	
			//uppercases the letters
			printf("%c",toupper(argv[1][counter]));
		}
		counter++;
	}
	printf("\n");
	return 0;
}
