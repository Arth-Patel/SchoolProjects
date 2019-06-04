#include "libnetfiles.h"


int serverinitmode=0;

int opening(char buf[256], int socket);
int reading(char buf[256], int socket);
int writing(char buf[256], int socket);
int closing(char buf[256], int socket);

struct node{
	int beingWritten;
	int open;
	int fd;
	char *path;
	struct node *next;
 };

struct node *head='\0';

int insert(int fd,char *path,int beingWritten){//return 0 if all is well, return 1 if 
	struct node *link=(struct node*)malloc(sizeof(struct node));
	char *pathname=(char*)malloc(strlen(path)*sizeof(char));
	strcpy(pathname,path);
	link->path=pathname;
	link->fd=fd;
	link->open=1;
	link->beingWritten=beingWritten;
	link->next='\0';
	if(head=='\0'){
		head=link;	
		return 0;
	}
	struct node *ptr=head;
	while(ptr!='\0'){//the lock sysstem for Part A
		if(!strcpy(path,ptr->path)){
			if(!(ptr->open)){
				ptr->open=1;
				ptr->beingWritten=beingWritten;
				ptr->fd=fd;
				return 0;
			}else if(serverinitmode==1&&ptr->beingWritten&&beingWritten){
				return -1;
			}else if(serverinitmode==2){
				return -1;	
			}
			return 0;
		}
		ptr=ptr->next;
		
	}
	link->next=head;
	head=link;
	return 0;	
}



void *threadstart(void* param){
	int socket=*(int*) param;
	char buf[256];
	int readstatus=read(socket,buf,255);
	if(readstatus<0){
		printf("Couldn't read from socket\n");
		return NULL;
	}
	if (buf[0]=='O'){ 
		opening(buf,socket);
	}else if(buf[0]=='R'){
		reading(buf,socket);
	}else if(buf[0]=='C'){
		closing(buf,socket);
	}else if(buf[0]=='W'){
		writing(buf,socket);
	}else{
		printf("Couldn't idenitify process\n");
		return NULL;	
	}
	return NULL;
}	

int opening(char buf[256], int socket){
	int descrip;
	int insertstatus=0;
	int writing=0;
	int counter=0;
	char *path=(char*)malloc(strlen(buf)*sizeof(char));
	while(counter<strlen(buf)){
		path[counter]=buf[6+counter];	
		counter++;
	}
	if(buf[4]=='0'){
		serverinitmode=0;
	}else if(buf[4]=='1'){
		serverinitmode=1;
		
	}else if(buf[4]=='2'){
		serverinitmode=2;
	}
//	printf("Checking %s\n",path);
	if(buf[2]=='0'){
		
		descrip=open(path, O_RDONLY);	
	}else if(buf[2]=='1'){
		writing=1;
		descrip=open(path, O_WRONLY);
		
	}else if(buf[2]=='2'){
		writing=1;
		descrip=open(path, O_RDWR);
	}else {	
		printf("Can't read flags\n");
			
	}



	insertstatus=insert(descrip, path, writing);
	char sendingbuf[256];
	memset(sendingbuf, '\0', sizeof(sendingbuf));
	if(descrip==-1){
		sendingbuf[0]='%';
		printf("File doesnt exist\n");
	}else if(insertstatus==-1){
		printf("File is currently in use\n");
		close(descrip);
		sendingbuf[0]='&';
	}else{	
		sendingbuf[0]=descrip-'0';
	}
	write(socket,sendingbuf,sizeof(sendingbuf));
	return 0;
}

int closing(char buf[256], int socket){
	int descrip=buf[2]+'0';
	int writing=0;
	int counter=0;
	int status=0;
	status=close(descrip);
	struct node *ptr=head;
	while(ptr!='\0'){
		if(descrip==ptr->fd){
			ptr->open=0;
			ptr->beingWritten=0;
		}
		ptr=ptr->next;	
		
	}
	char sendingbuf[256];
	memset(sendingbuf, '\0', sizeof(sendingbuf));
	sendingbuf[0]=status-'0';
	write(socket,sendingbuf,sizeof(sendingbuf));
	return 0;
}

int reading(char buf[256], int socket){
	int filedes=buf[2]+'0';
	int amounttopull=buf[4]+'0';
//	printf("Pulling %d bytes\n",amounttopull);
	char sendingbuf[amounttopull+3];
	memset(sendingbuf, '\0', sizeof(sendingbuf));
	int amount=read(filedes,sendingbuf+2,amounttopull);
	if(filedes>0){
		sendingbuf[0]=amount-'0';
	}else{
		sendingbuf[0]=filedes-'0';
	}
	sendingbuf[1]=' ';
//printf("got%s\n",sendingbuf);	
	write(socket,sendingbuf,sizeof(sendingbuf));

	return 0;
}

int writing(char buf[256], int socket){
	int filedes=buf[2]+'0';
	struct node *ptr=head;

	int amounttopull=buf[4]+'0';
//	printf("Pulling %d bytes\n",amounttopull);
	char sendingbuf[amounttopull+5];
	memset(sendingbuf, '\0', sizeof(sendingbuf));
	int amount=write(filedes,sendingbuf+2,amounttopull);
	if(filedes!=-1){
		sendingbuf[0]=amount-'0';
	}else{
		printf("file is closed\n");
		sendingbuf[0]=filedes-'0';
	}
	sendingbuf[1]=' ';
	//printf("got%s\n",sendingbuf);	
	write(socket,sendingbuf,sizeof(sendingbuf));


	return 0;
}
int main(){
	int recSock;//sets up the receiving socket
	recSock=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in comingTo;
	struct sockaddr_in incoming;
	memset(&comingTo, 0, sizeof(comingTo));
	comingTo.sin_family=AF_INET;
	comingTo.sin_port=htons(PORT);
	comingTo.sin_addr.s_addr= INADDR_ANY;
	int bindStatus=bind(recSock,(struct sockaddr*)&comingTo,sizeof(comingTo));
	int statusofaccept;
	if(bindStatus<0){
		printf("Bind has failed\n");
		return -1;	
	}
	int threadcounter=0;
	char buf[256];
	memset(buf, '\0', sizeof(buf));
	listen(recSock,20);
	int readstatus;
	int threadstatus;
	pthread_t threads[20];
	int sockSize=sizeof(incoming);
	while(1){//takes requets, threads them and creates new sockets for them
		statusofaccept=accept(recSock,(struct sockaddr*)&incoming,&sockSize);
		
		if(statusofaccept<0){
			printf("error on accept\n");
			return -1;
		}
		pthread_create(&threads[threadcounter],NULL, threadstart, &statusofaccept);
		pthread_join(threads[threadcounter],NULL);
		threadcounter++;
		
/*		if(threadstatus<0){
			printf("Thread failed to open\n");
			return 1;
		}
*/	}	
    
}

