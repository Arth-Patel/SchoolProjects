#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

struct node{
	int occurences;
	char * filename;
	char * word;
	struct node *next;
};

struct node *head = '\0';

	
void insert(char * file, char *word){
//	struct node *prev='\0';
	struct node *ptr=head;
	struct node *future=head;
	struct node *link=(struct node*)malloc(sizeof(struct node));
	char *newword=(char*)malloc(strlen(word)*sizeof(char));
	char *filename=(char*)malloc(strlen(file)*sizeof(char));
	strcpy(newword,word);
	strcpy(filename,file);
//	printf("%s ", word);
	link->filename=filename;
	link->word=newword;
	link->occurences=1;
	link->next='\0';
	if(head=='\0'){
		head=link;		
		return;	
	}
	if(strcmp(head->word,newword)>0){
		link->next=head;
		head=link;
		return;
	}
	while(ptr!='\0'){
//		printf("ptr is pointing to %s",ptr->word);
		future=ptr->next;
		if(!strcmp(newword,ptr->word)){
			if(!strcmp(filename,ptr->filename)){
				ptr->occurences++;
				return;
			}
			if(future!='\0'){
				if(!strcmp(word,future->word)){
					
					ptr=ptr->next;			
					continue;
				}else{
					ptr->next=link;
					link->next=future;
					return;
				}
			}else{
				ptr->next=link;
				link->next=future;
				return;
			}
		}else{
			if(future=='\0'){
				ptr->next=link;
				return;
			}
			if(strcmp(future->word, word)>0){
				link->next=ptr->next;
				ptr->next=link;
				return;
			}else{
				
				ptr=ptr->next;
				continue;
			}
		}

/*		if(!strcmp(newword,ptr->word)){
			if(!strcmp(filename,ptr->filename)){
				ptr->occurences++;
				return;
			}
			if(future!='\0'){
				if(!strcmp(newword,future->word)){
					ptr=future;
					continue;

				}
			}
			link->next=future;
			ptr->next=link;
			return;
		}
		if(future!='\0'){
			if(strcmp(newword,future->word)>0){
				prev=ptr;
				ptr=ptr->next;
					
			}else{
				link->next=future;
				future=link;
				return;
			}
		}else{
			ptr->next=link;
			return;
		}
*/
	}
	

}

	
void readfile(char *filename, FILE *fp){
	char letter='d';
	char string[100];
	int counter=0;
	while(!feof(fp)){
		fscanf(fp,"%c",&letter);
		if(isalnum(letter)){
			letter=tolower(letter);
			string[counter]=letter;
			counter++;	
		}else{
			string[counter]='\0';
		
			if(counter){
			//	printf("word:%s \n",string);
				insert(filename,string);	
		//		printlist();	
			}
			counter=0;	
		}	
	}
}

void directory(DIR *dp,char *location){
	struct dirent *search;
	char filename[100];
	while((search = readdir(dp))!='\0'){
	//	printf("inside - %s \n",search->d_name);
		strcpy(filename,search->d_name);	
		if(!strcmp(filename,".")||!strcmp(filename,"..")){
			continue;
		}
			
		char *locate=(char*)malloc((1+strlen(filename)+strlen(location))*sizeof(char));
		strcpy(locate,location);
		strcat(locate,filename);
		DIR *file=opendir(locate);

			
	//	printf("%s \n",locate);

		if(file){
			strcat(locate,"/");
			directory(file,locate);

		}else{
			FILE *fp2;
			fp2=fopen(locate,"r");
			readfile(filename,fp2);

		} 
	}

}

int arrsort(const void *pa1, const void *pa2){
	const struct node *p1=*(struct node**)pa1;
	const struct node *p2=*(struct node**)pa2;
	if(p1->occurences>p2->occurences){
		return -1;
	}else if(p1->occurences<p2->occurences){
		return 1;
	}
	if(strcmp(p1->filename,p2->filename)>0){
		return 1;
	}
	return -1;	
}

void printlist(){
	struct node *ptr=head;
	while(ptr!='\0'){
		printf("(%s: %d in %s) ",ptr->word,ptr->occurences,ptr->filename);
		ptr=ptr->next;
	}
	printf("\n");	
}

void printxml(FILE *fil){

	struct node *ptr=head;
	int counter=0;
	int total;
//	while
//	qsort(arr,counter,sizeof(struct node),arsort);
	fprintf(fil,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(fil,"<fileIndex>\n");
	while(ptr!='\0'){
		char *word=(char*)malloc(strlen(ptr->word));
		strcpy(word,ptr->word);
		struct node *store=ptr;
		while(!strcmp(word,ptr->word)){
			ptr=ptr->next;
			counter++;
			if(ptr=='\0'){
				break;
			}
		}
		total=counter;
		ptr=store;
		struct node *list[counter];
		counter=0;
		while(!strcmp(word,ptr->word)){
			list[counter]=ptr;
			ptr=ptr->next;
			counter++;
			if(ptr=='\0'){
				break;
			}
		}
		list[counter]='\0';
		qsort(list,total,sizeof(struct node*),arrsort); 
		counter=0;
		fprintf(fil,"\t<word text=\"%s\">\n",store->word);
		while(counter<total){	
			fprintf(fil,"\t\t<file name=\"%s\">%d</file>\n",list[counter]->filename,list[counter]->occurences);
			counter++;
			
		}	
		/*	
		while(!strcmp(word,ptr->word)){
			printf("\t\t<file name=\"%s\">%d</file>\n",ptr->filename,ptr->occurences);
			ptr=ptr->next;
			if(ptr=='\0'){
				break;
			}	
		}*/
		counter=0;
		fprintf(fil,"\t</word>\n");
	
	//	printf("ptr_>word =  %s\n", ptr->word);
		if(ptr=='\0'){
			break;
		}	
	}
	fprintf(fil,"</fileIndex>\n");


}

int main(int argc, char *argv[]){
	if (argc>3){//checkcs arguments
		printf("Too many arguments\n");
		return 1;
	} else if (argc<3){
		printf("not enough arguments\n");
		return 1;	
	}
	
	
	FILE *fp;
	fp=fopen(argv[1],"r");
	while(fp){
		printf("You are trying to overwrite %s. Are you sure you want to do that? Yes or No?\n",argv[1]);
		char choice[3];
		scanf("%s",choice);
		choice[0]=tolower(choice[0]);
		if(!strcmp(choice,"yes")){
			break;
		}else if(!strcmp(choice,"no")){
			printf("Enter a file you want to overwrite next time \n");
			fclose(fp);	
			return 1;	
		}
	//	printf("You are trying to overwrite %s. Are you sure you want to do that? Yes or No?\n",argv[1]);
		
	}
	char location[200];
	strcpy(location,argv[2]);
	strcat(location, "/");
	fp=fopen(argv[1],"w");
	DIR *folder=opendir(argv[2]);
	if(folder){
		
		directory(folder,location);

	}else{
		FILE *fp2;
		fp2=fopen(argv[2],"r");
		if(!fp2){
			printf("No file or directory by that name");
			fclose(fp);
			return 1;
		}
		readfile(argv[2],fp2);

	}
/*
	if(fp2==NULL){
		printf("The file you have chosen to index to does not exist\n");
		return 1;
	}
*/	
	printxml(fp);




	return 0;
}
