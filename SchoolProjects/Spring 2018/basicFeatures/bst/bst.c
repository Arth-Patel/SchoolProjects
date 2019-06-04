#include <stdlib.h>
#include <stdio.h>


struct node{
	int data;
	struct node *left;
	struct node *right;
};


struct node* insert(int data,struct node *head){
	struct node *ptr=head;
	struct node *prev=head;
	struct node *link=(struct node*)malloc(sizeof(struct node));
	int direction=0;//0 for left, 1 for right
	link->data=data;
	if (head=='\0'){
		head=link;
		printf("inserted\n");
		return head;
	}
	while(ptr!='\0'){//makes sure theres no repeats
	//	printf("%d",ptr->data);
		if(ptr->data==data){
			printf("duplicate \n");
			return head;
		}else if(data<ptr->data){
			prev=ptr;
			ptr=ptr->left;
			direction=0;
		}else{
			prev=ptr;
			ptr=ptr->right;
			direction=1;
		}
	}
	printf("inserted\n");
	if(direction==0){
		prev->left=link;
	}else{
		prev->right=link;
	}
	return head;
}

struct node *delete(int data, struct node *head){
	struct node *ptr=head;
	struct node *prev=head;
	int direction=0;
	while(ptr!='\0'){//makes sure theres no repeats
		if(ptr->data==data){
			printf("deleted \n");
			if(ptr->data==head->data &&head->right=='\0'&&head->left=='\0' ){
				head='\0';
			}else if(ptr->right=='\0'&&ptr->left=='\0'){//no child
				if(direction==0){
					prev->left='\0';
				}else if(direction==1){
					prev->right='\0';
				}
			}else if((ptr->right=='\0'&&ptr->left!='\0')||(ptr->right!='\0'&&ptr->left=='\0')){//onechild
				if(ptr->right=='\0'){
					if(direction==0){
						prev->left=ptr->left;
					}else{
						prev->right=ptr->left;
					}
				}else{
					if(direction==0){
						prev->left=ptr->right;
					}else{	
						prev->right=ptr->right;	
					}
				}
			}else{//two children
				struct node *setup=ptr->left;
				struct node *prev=ptr->left;
				while(setup->right!='\0'){
					prev=setup;
					setup=setup->right;
				}
				ptr->data=setup->data;
				prev->right=setup->left;
			}				
			return head;
		}else if(data<ptr->data){
			prev=ptr;
			ptr=ptr->left;
			direction=0;
		}else{
			prev=ptr;
			ptr=ptr->right;
			direction=1;
		}
	}
	printf("absent \n");
	return head;
}

void search(int data,struct node *head){
	struct node *ptr=head;
	while(ptr!='\0'){//searches
		if(ptr->data==data){
			printf("present \n");
			return;
		}else if(data<ptr->data){
			ptr=ptr->left;
		}else{
			ptr=ptr->right;
		}
	}
	printf("absent \n");
	return;
}

void printtree(struct node *ptr){
	if(ptr=='\0'){
		return;
	}
	printf("(");
	printtree(ptr->left);
	printf("%d", ptr->data);
	printtree(ptr->right);
	printf(")");
	return;
}

void freetree(struct node *ptr){
	if(ptr=='\0'){
		return;
	}
	struct node *tempright=ptr->right;
	struct node *templeft=ptr->left;
	freetree(templeft);
	freetree(tempright);
	return;
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
	if(fp==NULL){
		printf("error\n");
		return 1;
	}
	struct node *head='\0';
	char choice;
	int number;	
	while(!feof(fp)){
		fscanf(fp, "%c %d \n",&choice,&number);//grabs from the file, and figures out to insert/delete
		if(choice=='i'){
			head=insert(number,head);
		}else if(choice=='d'){
			head=delete(number,head);
		}else if(choice=='s'){
			search(number,head);
		}else if(choice=='p'){
			printtree(head);
			printf("\n");
		}else{
			printf("error");
		}
	}
	fclose(fp);
	freetree(head);
	return 0;
}
