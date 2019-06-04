#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

struct node{
	int data;
	struct node *next;
};



struct node* insert(int data,struct node *head){
	struct node *prev='\0';
	struct node *ptr=head;
	struct node *link=(struct node*)malloc(sizeof(struct node));
	link->data=data;
	if(head=='\0'){ //first entry
		head=link;
		return head;
	}
	while(ptr!='\0'){//makes sure theres no repeat
		if(ptr->data==data){
			return head;
		}
		if(data>ptr->data){
			prev=ptr;
			ptr=ptr->next;
		}else{
			if(prev=='\0'){//if its the smallest element
				link->next=ptr;
				return link;
			}
			prev->next=link;
			link->next=ptr;
			return head;
		}

	}
	prev->next=link;//if its the biggest item
	return head;
}

struct node *delete(int data,struct node *head){
	if(head=='\0'){//no nodes in the list
		return head;
	}
	if(head->data==data){//if the first node has the data
		if(head->next=='\0'){//if theres only one node
			head='\0';
			return head;	
		}
		head=head->next;//sets the new head
		return head;
	}
	struct node *ptr=head;
	struct node *prev=head;
	while(ptr->next!='\0'&&ptr->data!=data){//ggoes until the end of the list or until data is found
		prev=ptr;
		ptr=ptr->next;
	}
	if(ptr->data==data){//removes data
		prev->next=ptr->next;
	}
	return head;
}

int main(int argc, char** argv){
	if (argc>2){//checks for right argumenets
		printf("Too many arguments");
		return 1;
	} else if (argc<2){
		printf("not enough arguments");
		return 1;	
	}
	
	FILE *fp;
	fp=fopen(argv[1],"r");
	char choice;
	int number;
	if(fp==NULL){
		printf("error \n");
		return 1;
	}
	struct node *head='\0';
	while(!feof(fp)){
		fscanf(fp, "%c %d \n",&choice,&number);//grabs from the file, and figures out to insert/delete
		if(choice=='i'){
			head=insert(number,head);
		}else if(choice=='d'){
			head=delete(number,head);
		}else{
			printf("error");
			return 1;
		}
	}
	fclose(fp);
	int size=0;
	struct node *ptr=head;
	while (ptr!='\0'){
		ptr=ptr->next;
		size++;
	}
	printf("%d \n",size);
	ptr=head;
	struct node *temp=head;
	while(ptr!='\0'){//prints the list and frees it
		printf("%d ",ptr->data);
		temp=ptr->next;
		free(ptr);
		ptr=temp;
	}
	printf("\n");
	return 0;
}
