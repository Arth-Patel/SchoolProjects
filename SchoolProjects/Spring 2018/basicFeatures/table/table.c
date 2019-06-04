#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


struct node{
	int data;
	struct node *next;
};

void insert(int data,struct node *hashtable[10000]){
	int key=data%10000;
	struct node *ptr=hashtable[key];
	while(ptr!='\0'){//makes sure theres no repeats
	//	printf("%d\n",ptr->data);
		if(ptr->data==data){
			printf("duplicate\n");	
			return;
		}
		ptr=ptr->next;
	}
	struct node *link=(struct node*)malloc(sizeof(struct node));
	link->data=data;
	link->next=hashtable[key];
	hashtable[key]=link;
	printf("inserted \n");
} 

void search(int data,struct node *hashtable[10000]){
//	printf("devil");
	int key=data%10000;
	struct node *ptr=hashtable[key];

	while(ptr!='\0'){
	//	printf("%d\n",ptr->data);
		if(ptr->data==data){
			printf("present\n");
			return;
		}
		ptr=ptr->next;
	}
	printf("absent\n");
	
}



int main(int argc, char** argv){
	if (argc>2){
		printf("Too many arguments");
		return 1;
	} else if (argc<2){
		printf("not enough arguments");
		return 1;	
	}
	int counter=0;
	FILE *fp;
	fp=fopen(argv[1],"r");
	char choice;
	int number;	
	if(fp==NULL){
		printf("error\n");
		return 1;
	}
	struct node *hashtable[10000];
	while(counter<10000){
		hashtable[counter]='\0';
		counter++;
	}//sets hashtable values to none
	while(!feof(fp)){
		fscanf(fp, "%c %d \n",&choice,&number);
		if(choice=='i'){
			insert(number,hashtable);
		}else if(choice=='s'){
			search(number,hashtable);
		}else{
			printf("error\n");
		}
	}
	fclose(fp);
	counter=0;
	while(counter<10000){//frees the hashtable
		struct node *ptr=hashtable[counter];
		while(ptr!='\0'){
			struct node *temp=ptr->next;
			free(ptr);
			ptr=temp;
		}
		counter++;
	}
	return 0;
}
