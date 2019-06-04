#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef struct {
	int horizontal;
	int vertical;
} coord;

void solvability(char puzzle[9][9] ){
	int horcounter=0;
	int vertcounter=0;
	int firstdeclared=0;//boolean to see declared
	int seconddeclared=0;
	coord first={-1,-1};
	coord second={-1,-1};
	while(horcounter<9){//grabs the locations of the missing spaces
		while(vertcounter<9){
			if(!isdigit(puzzle[horcounter][vertcounter])){
				if(firstdeclared==0){
					firstdeclared=1;
					first.horizontal=horcounter;
					first.vertical=vertcounter;
				}else if(seconddeclared==0){
					seconddeclared=1;
					second.horizontal=horcounter;
					second.vertical=vertcounter;
				}else {
					printf("error\n");			
					return;
				}
			}
			
			vertcounter++;
		}
		
		vertcounter=0;
		horcounter++;
	}
//	printf("Horcounter=%d, Vertcounter=%d", first.horizontal,second.vertical);
	horcounter=0;
	vertcounter=0;
	char check[9];
	int x=0;
	int incheck=0;
	int solcount=1;
	int secondsolcount=1;
	int solvable=0;//boolean changed to 1, when a solution is proved unsolvable
	while(secondsolcount<10){//suns thru the second numbers if it can be solved
		if(seconddeclared==1){
			puzzle[second.horizontal][second.vertical]=secondsolcount;
		}else{
			secondsolcount=10;
		}
		while(solcount<10){//runs all numbers thru an empty space to see if it works
			puzzle[first.horizontal][first.vertical]=solcount;
			while(horcounter<9){//checks to see if it works on the horizontal
				while(vertcounter<9){
				
					while(x<incheck){
				//	printf("%c",puzzle[horcounter][vertcounter]);
						if(check[x]==puzzle[horcounter][vertcounter]){
							
							solvable=1;
						}
						x++;
					}
					check[incheck]=puzzle[horcounter][vertcounter];
					x=0;
					incheck++;
					vertcounter++;
				}
				incheck=0;
				vertcounter=0;
				horcounter++;
			}
			vertcounter=0;
			horcounter=0;
			x=0;
			incheck=0;
			while(vertcounter<9){//check if it works on the vertical
				while(horcounter<9){
					while(x<incheck){
					//	printf("%c",puzzle[horcounter][vertcounter]);
						if(check[x]==puzzle[horcounter][vertcounter]){
							solvable=1;			
						}
						x++;
					}
					check[incheck]=puzzle[horcounter][vertcounter];
					x=0;
					incheck++;
					horcounter++;
				}
				incheck=0;
				horcounter=0;
				vertcounter++;
			}
			vertcounter=0;
			x=0;
			incheck=0;
			horcounter=0;
			int counter=0;
			int horbottom=0;
			int hortop=3;
			int verbottom=0;
			int vertop=3;
			int seccounter=0;
			while(seccounter<3){ //Check if it works in a 3x3
				while(counter<3){	
					while(vertcounter<vertop){
						while(horcounter<hortop){
							while(x<incheck){
		//						printf("%d %d",horcounter,vertcounter);
								if(check[x]==puzzle[horcounter][vertcounter]){
									solvable=1;		
								}
			
								x++;
							}	
							check[incheck]=puzzle[horcounter][vertcounter];
							x=0;
							incheck++;
							horcounter++;
						}
						horcounter=horbottom;
						vertcounter++;
					}
					incheck=0;
					vertcounter=verbottom;
					counter++;
					horbottom=horbottom+3;
					hortop=hortop+3;
					horcounter=horbottom;
				}
				seccounter++;
				counter=0;
				horbottom=0;		
				hortop=3;
				verbottom=verbottom+3;
				vertop=vertop+3;
				vertcounter=verbottom;
			}
			solcount++;
			if(solvable==0){
				printf("solvable \n");
				return;
			}
			solvable=0;
		}
		solcount=0;
		secondsolcount++;
		
	}
	printf("unsolvable\n");
}

int main(int argc, char** argv){
	if (argc>2){
		printf("Too many arguments");
		return 1;
	} else if (argc<2){
		printf("not enough arguments");
		return 1;	
	}
	
	
	FILE *fp;
	fp=fopen(argv[1],"r");
	char puzzle[9][9];
	int counter=0;
	if(fp==NULL){
		printf("error\n");
		return 1;
	}
	while(counter<9){//gets sudoku #'s
		fgets(puzzle[counter],11,fp);
//		printf("%s \n",puzzle[counter]);	
		counter++;
	}
	fclose(fp);
	int horcounter=0;
	int vertcounter=0;
	char check[9];
	int x=0;
	int incheck=0;
	while(horcounter<9){//checks to see if it works on the horizontal
		while(vertcounter<9){
			if(!isdigit(puzzle[horcounter][vertcounter])){
				solvability(puzzle);
					//printf("placeholderforunsovalble");	
				return 1;
			}
			while(x<incheck){
			//	printf("%c",puzzle[horcounter][vertcounter]);
				if(check[x]==puzzle[horcounter][vertcounter]){
					printf("incorrect \n");
					return 0;				
				}

				x++;
			}
			check[incheck]=puzzle[horcounter][vertcounter];
			x=0;
			incheck++;
			vertcounter++;
		}
		incheck=0;
		vertcounter=0;
		horcounter++;
	}
	vertcounter=0;
	horcounter=0;
	x=0;
	incheck=0;
	while(vertcounter<9){//check if it works on the vertical
		while(horcounter<9){
			while(x<incheck){
			//	printf("%c",puzzle[horcounter][vertcounter]);
				if(check[x]==puzzle[horcounter][vertcounter]){
					printf("incorrect \n");
					return 1;				
				}
				x++;
			}
			check[incheck]=puzzle[horcounter][vertcounter];
			x=0;
			incheck++;
			horcounter++;
		}
		incheck=0;
		horcounter=0;
		vertcounter++;
	}
	vertcounter=0;
	x=0;
	incheck=0;
	horcounter=0;
	counter=0;
	int horbottom=0;
	int hortop=3;
	int verbottom=0;
	int vertop=3;
	int seccounter=0;
	while(seccounter<3){ //Check if it works in a 3x3
		while(counter<3){	
			while(vertcounter<vertop){
				while(horcounter<hortop){
					while(x<incheck){
//						printf("%d %d",horcounter,vertcounter);
						if(check[x]==puzzle[horcounter][vertcounter]){
							printf("incorrect \n");
							return 0;				
						}
	
						x++;
					}	
					check[incheck]=puzzle[horcounter][vertcounter];
					x=0;
					incheck++;
					horcounter++;
				}
				horcounter=horbottom;
				vertcounter++;
			}
			incheck=0;
			vertcounter=verbottom;
			counter++;
			horbottom=horbottom+3;
			hortop=hortop+3;
			horcounter=horbottom;
		}
		seccounter++;
		counter=0;
		horbottom=0;		
		hortop=3;
		verbottom=verbottom+3;
		vertop=vertop+3;
		vertcounter=verbottom;
	}
	printf("correct \n");
	return 0;
}
