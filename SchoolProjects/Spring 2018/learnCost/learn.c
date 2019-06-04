#include <stdio.h>
#include <stdlib.h>
#define DEBUG 0

double **multiply(double **one, double **two, int shared, int first, int second){
	int counter=0;
	double **sol = (double **)malloc(first* sizeof(double *));
	while(counter<first){
		sol[counter]=(double *)malloc(second*sizeof(double));
		counter++;
	}
	int i=0;
	int j=0;
	int k=0;
	for(i=0;i<first;i++){
		for(j=0;j<second;j++){
			sol[i][j]=0;
			for(k=0;k<shared;k++){
				sol[i][j]+=one[i][k]*two[k][j];	
		//		printf("one by one %f  ", one[i][k]*two[k][j]);
			}	
		}
	}
					
	return sol;
}
int main(int argc, char ** argv){
	if(argc>3){//checking arguments
		printf("Too many argumenets");
		return 1;
	}else if (argc<3){
		printf("not enough arguments");
		return 1;
	}
	FILE *fp1;
	FILE *fp2;
	fp1=fopen(argv[1],"r");
	fp2=fopen(argv[2],"r");
	if(fp1==NULL||fp2==NULL){//checking the files
		printf("error\n");
		return 1;
	}
	char determine[6]="";
	int counter=0;
	int horcounter=0;
	int vertcounter=0;
	double tempstore;
	double storage;
	int houses;
	int attributes;
	fscanf(fp1,"%s %d %d", determine, &attributes, &houses);
	double *prices=(double*)malloc(houses*sizeof(double));
	double **first=(double**)malloc((attributes+1)*sizeof(double*));
	double **transpose=(double**)malloc((houses)*sizeof(double*));
	double **identity=(double**)malloc((attributes+1)*sizeof(double*));
	while(counter<attributes+1){
		first[counter]=(double*)malloc((houses)*sizeof(double));
		identity[counter]=(double*)malloc((attributes+1)*sizeof(double));
		counter++;
	}
	counter=0;
	while(counter<houses){
		transpose[counter]=(double*)malloc((attributes+1)*sizeof(double));
		counter++;
	}
	while(houses>vertcounter){//setting up prices, identity, and training matrix
		while(attributes+1>horcounter){
			if(horcounter==0){
				transpose[vertcounter][horcounter]=1;
				first[horcounter][vertcounter]=1;
			}else{
				fscanf(fp1,"%lf ", &tempstore);
				transpose[vertcounter][horcounter]=tempstore;
				first[horcounter][vertcounter]=tempstore;
			}
		//	printf("%f ", transpose[vertcounter][horcounter]);
		//	printf("%f ", first[horcounter][vertcounter]);
			horcounter++;
		}
		fscanf(fp1, "%lf ", &prices[vertcounter]);

		horcounter=0;
	//	printf("\n");
			
		vertcounter++;
	}

	
	//printf("\n");
	horcounter=0;
	vertcounter=0;
	while(attributes+1>vertcounter){//printing transpose
		while(horcounter<houses){
	//		printf("t%f ", transpose[horcounter][vertcounter]);
			horcounter++;
		}
	//	printf("\n");
		horcounter=0;
		vertcounter++;
	}		
	horcounter=0;
	vertcounter=0;
	int level=0;
	double storage2;
	double **matandtran;
	matandtran=multiply(first,transpose,houses,attributes+1,attributes+1);
	counter=0;
	while(horcounter<attributes+1){//setting up identity matrix
		while(vertcounter<attributes+1){
			identity[horcounter][vertcounter]=0;
			if(vertcounter==horcounter){
			identity[horcounter][vertcounter]=1;
			}
			vertcounter++;
		}
		vertcounter=0;
		horcounter++;
		
	}
	horcounter=0;
	vertcounter=0;

	while(attributes+1>vertcounter){//printing
		while(attributes+1>horcounter){
//			printf("%f ",matandtran[horcounter][vertcounter]);
			horcounter++;
		}	
		horcounter=0;	
		vertcounter++;
//		printf("\n");
	}
	
/*	
	printf("\n");
	horcounter=0;
	vertcounter=0;
	while(attributes+1>vertcounter){//printing
		while(attributes+1>horcounter){
			printf("%f ",identity[horcounter][vertcounter]);
			horcounter++;
		}	
		horcounter=0;	
		vertcounter++;
		printf("\n");
	}
		*/
	vertcounter=0;
	horcounter=0;
	while(level<attributes+1){//GAUSS ELIMINATION
		if(matandtran[horcounter][vertcounter]!=1){//making the pivot 1
			storage=matandtran[horcounter][vertcounter];
			horcounter=0;
			while(horcounter<attributes+1){
				matandtran[horcounter][vertcounter]=matandtran[horcounter][vertcounter]/storage;
				identity[horcounter][vertcounter]=identity[horcounter][vertcounter]/storage;
				horcounter++;
					
			}
				
			
		}
		horcounter=level;
		if(matandtran[horcounter][vertcounter]==1){
			vertcounter=0;
			while(vertcounter<attributes+1){
				if(vertcounter!=level){//not removing the line being used
					storage2=matandtran[horcounter][vertcounter];
					horcounter=0;
					while(horcounter<attributes+1l){
						matandtran[horcounter][vertcounter]=matandtran[horcounter][vertcounter] - (matandtran[horcounter][level]*storage2);
						identity[horcounter][vertcounter]=identity[horcounter][vertcounter] - (identity[horcounter][level]*storage2);
						horcounter++;
					}
					horcounter=level;
				}
				vertcounter++;
			}
		}
		level++;
		horcounter=level;
		vertcounter=level;
	}
	horcounter=0;
	vertcounter=0;
//	printf("finished identity\n");
	while(attributes+1>vertcounter){//printing
		while(attributes+1>horcounter){
//			printf("%f ",matandtran[horcounter][vertcounter]);
			horcounter++;
		}	
		horcounter=0;	
		vertcounter++;
//		printf("\n");
	}
/*
	
	printf("\n");
	horcounter=0;
	vertcounter=0;
	while(attributes+1>vertcounter){//printing
		while(attributes+1>horcounter){
			printf("%f ",identity[horcounter][vertcounter]);
			horcounter++;
		}	
		horcounter=0;	
		vertcounter++;
		printf("\n");
	}

	horcounter=0;
	vertcounter=0;
	while(attributes+1>vertcounter){//printing transpose
		while(horcounter<houses){
			printf("t%f ", transpose[horcounter][vertcounter]);
			horcounter++;
		}
		printf("\n");
		horcounter=0;
		vertcounter++;
	}*/	
	horcounter=0;
	vertcounter=0;
	double **invandtran;
	invandtran=multiply(identity,first, attributes+1, attributes+1,houses);

	counter=0;	

	double sol[attributes+1];
	while(attributes+1>horcounter){//multiplying the inverse*tran by the price to get the weights
		sol[horcounter]=0;
		while(houses>vertcounter){
//			printf("%.0f ",invandtran[horcounter][vertcounter]);
			sol[horcounter]+=invandtran[horcounter][vertcounter]*prices[vertcounter];
			vertcounter++;
		}
//		printf("\n");
		vertcounter=0;
		horcounter++;	
	}
	counter=0;
//	printf("weights\n");	
	while(attributes+1>counter){
//		printf("%f ",sol[counter]);
		
		counter++;
	}
//	printf("\n");
	//printing


	fscanf(fp2,"%s", determine);
	fscanf(fp2,"%d", &attributes);
	fscanf(fp2,"%d", &houses);
	double **newstuff=(double**)malloc((attributes+2)*sizeof(double *));
	horcounter=0;
	vertcounter=0;
	counter=0;

	while(counter<attributes+1){//allocating memory thru the multidimensional array
		newstuff[counter]=(double*)malloc((houses)*sizeof(double));
		counter++;
	}
	
	while(houses>vertcounter){//setting up the data matrixes 
		while(attributes+1>horcounter){
			if(horcounter==0){
				newstuff[horcounter][vertcounter]=1;
			}else{
			fscanf(fp2,"%lf ", &newstuff[horcounter][vertcounter]);
//			printf("%f ", newstuff[horcounter][vertcounter]);
			}

			horcounter++;
		}

		horcounter=0;
//		printf("\n");
			
		vertcounter++;
	}
	double final[houses];//=multiply(weights,newstuff,houses,1,1);		
	fclose(fp1);
	fclose(fp2);
	horcounter=0;
	vertcounter=0;
	while(houses>horcounter){//multiplying the weights with the attributes of the new house
		final[horcounter]=0;
		while(attributes+1>vertcounter){
//			printf("%.0f ",invandtran[horcounter][vertcounter]);
			final[horcounter]+=sol[vertcounter]*newstuff[vertcounter][horcounter];
			vertcounter++;
		}
//		printf("\n");
		vertcounter=0;
		horcounter++;	
	}
	horcounter=0;
	while (houses>horcounter){
		printf("%.0f\n", final[horcounter]);
		horcounter++;
	}
	free(invandtran);
	free(newstuff);
	free(transpose);
	free(first);
	return 0;
}


