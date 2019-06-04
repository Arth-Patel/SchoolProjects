#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
 
int main(int argc, char**argv)
{
        if (argc <2){
                printf("Not Enough Arguments \n");
                return 1;
        }
        if (argc > 2){
                printf("TOO MANY ARGUMENTS \n");
                return 1;
        }
        int lastnon=1; //Boolean for checking if last char was a nonalpha
        int wordcounter=0; //Amount of words
        int counter=0;
        char *word=argv[1];
        int maxlength=0;
        int length=0;
        while(word[counter]!='\0'){ //Finding Maxlength and amount of words to figure out array details
                if (isalpha(word[counter])){
                        length++;
                        lastnon=0;
                }else if(lastnon==0){
                        lastnon=1;
                        if (length > maxlength){
                                maxlength=length;
                        }
                        length=0;
                        wordcounter++;
                }
                counter++;
                }
        if (length > maxlength){
                maxlength=length;
        }
        if (length >0){
                wordcounter++;
        }
	if (wordcounter==0){
		return 0;
	}
//      printf("Word count:%d,Longest Word:%d \n",wordcounter,maxlength);
        char *newwords[wordcounter]; //all the words put in 
        counter=0;
        while (counter < wordcounter){ //alocates for the string arrays
                newwords[counter]= (char*) malloc(maxlength);
                counter++;
        }
        counter=0;
        int tempcounter=0;
        char tempword[maxlength];
        int arrcounter=0;
        lastnon=1;
        while (word[counter]!='\0'){//adds the words to newwords
                if(isalpha(word[counter])){
                        tempword[tempcounter]=word[counter];
                        tempcounter++;
                        //printf("%c",word[counter]);
                        lastnon=0;
                }else if (lastnon==0){
                          lastnon=1;
                        tempword[tempcounter]='\0';
                        strcpy(newwords[arrcounter],tempword);
                        tempcounter=0;
                        arrcounter++;
 
                }
                counter++;
 
        }
        if(lastnon==0){
                tempword[tempcounter]='\0';
                strcpy(newwords[arrcounter],tempword);
        }
        int printcounter=0;
//	printf("The words are: ");
        while ( printcounter <  wordcounter){
//      printf("%s,", newwords[printcounter]);
        printcounter++;
        }
//	printf("\n");
	//Sort
	char temp[maxlength];
	int x;
	int y;
	for(x = 0; x < wordcounter - 1; x++){
		for(y = 0; y < wordcounter - 1; y++){
			if(strcmp(newwords[y],newwords[y+1]) > 0){
				strcpy(temp,newwords[y]);
				strcpy(newwords[y],newwords[y+1]);
				strcpy(newwords[y+1],temp);
			}
		}
	}
	printcounter = 0;
	while ( printcounter <  wordcounter){
        	printf("%s \n", newwords[printcounter]);
        	printcounter++;
        }
	free(*newwords);
        return 0;
}
