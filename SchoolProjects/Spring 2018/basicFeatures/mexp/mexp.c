#include <stdlib.h>
#include <stdio.h>


int main(int argc, char** argv){
	if (argc>2){//checkcs arguments
		printf("Too many arguments");
		return 1;
	} else if (argc<2){
		printf("not enough arguments");
		return 1;	
	}
	
	
	FILE *fp;
	fp=fopen(argv[1],"r");
	if(fp==NULL){
		printf("error\n");
		return 1;
	}
	int number;	
	int push;
	int horcounter=0;
	int vertcounter=0;
	fscanf(fp, "%d \n", &number);
	int first[number][number];
	int answer[number][number];
	int temp[number][number];
	while(vertcounter<number){//sets up matrice
		while(horcounter<number){
			fscanf(fp, "%d",&push);
			first[horcounter][vertcounter]=push;
			horcounter++;
		}
		horcounter=0;
		vertcounter++;
	}
	int amount;
	fscanf(fp,"%d", &amount);
	fclose(fp);
	horcounter=0;
	vertcounter=0;
//	printf("Amount: %d \n",amount);
	int counter=0;
/*	while(vertcounter<number){//prints matrice
		while(horcounter<number){
			printf("%d ",first[horcounter][vertcounter]);
			horcounter++;
		}
		printf("\n");
		horcounter=0;
		vertcounter++;
	}
*/	horcounter=0;
	vertcounter=0;
	while(vertcounter<number){//copy first into answer
		while(horcounter<number){
			answer[horcounter][vertcounter]=first[horcounter][vertcounter];
			horcounter++;
		}
		vertcounter++;
		horcounter=0;
	}
	vertcounter=0;
	horcounter=0;
	if (amount==1){
	//	continue;
	}else if (amount==0){
		while(vertcounter<number){
			while(horcounter<number){
				answer[horcounter][vertcounter]=0;
				horcounter++;
			}
			horcounter=0;
			vertcounter++;
		}
		while(counter<number){
			answer[counter][counter]=1;
			counter++;	
		}
	}else{

		counter=1;
		int i,j,k;
		while(counter<amount){
			//temp=answer*first
			for (i = 0; i < number; i++){
       				 for (j = 0; j < number; j++){
          				 temp[i][j] = 0;
           				 for (k = 0; k < number; k++){
               					 temp[i][j] += answer[i][k]*first[k][j];
			       		 }
			  	  }
			}
			while(vertcounter<number){//move temp to answer
//				printf("funz");
				while(horcounter<number){
					answer[horcounter][vertcounter]=temp[horcounter][vertcounter];
					horcounter++;
				}
				vertcounter++;
				horcounter=0;
			}
			vertcounter=0;	
			horcounter=0;
			counter++;
		}
	}	
	vertcounter=0;
	horcounter=0;
	while(vertcounter<number){//prints matrice
		while(horcounter<number){
	
			printf("%d ",answer[horcounter][vertcounter]);
			horcounter++;
		}
		printf("\n");
		horcounter=0;
		vertcounter++;
	}
	return 0;
}
