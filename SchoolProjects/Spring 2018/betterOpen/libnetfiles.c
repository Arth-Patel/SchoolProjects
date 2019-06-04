#include "libnetfiles.h"


int hostFound=-1;
int fileAccess=0;
char *globalHost; //stores ip if valid


int netserverinit(char *hostname, int filemode){
	struct hostent *IP=gethostbyname(hostname);
	if(IP=='\0'){
		printf("Host not found\n");
		h_errno = HOST_NOT_FOUND;
		return -1;	
	}
	fileAccess=filemode;
	hostFound=0;
	globalHost=(char*)malloc(strlen(hostname)*sizeof(char));
	strcpy(globalHost,hostname);
	return 0;
	
}

int sockOpen(){
	
	int sendSock;
	
	sendSock=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in goingTo;
	memset(&goingTo, 0, sizeof(goingTo));
	goingTo.sin_family=AF_INET;
	goingTo.sin_port=htons(PORT);
	struct hostent *IP=gethostbyname(globalHost)	;
	memcpy(&(goingTo.sin_addr.s_addr), IP->h_addr, IP->h_length);
	int status=connect(sendSock,(struct sockaddr*)&goingTo,sizeof(goingTo));
	if(status==-1){
		printf("Connection failed during socket\n");
		return -1;
	}
	return sendSock;
}

int netopen(const char* pathname, int flags){
	if(hostFound){
		h_errno = HOST_NOT_FOUND;
		return -1;
			
	}
	int sockInUse=sockOpen();
	if(sockInUse==-1){
		return -1;	
	}
	char buf[strlen(pathname)+20];
	memset(buf, '\0', sizeof(buf));
	buf[0]='O';
	buf[1]=' ';
	buf[2]=flags+'0';
	buf[3]=' ';
	buf[4]= fileAccess+'0';
	buf[5]=' ';
	int counter=0;
	while(counter<strlen(pathname)){
		buf[6+counter]=pathname[counter];	
		counter++;
	}
	buf[counter+6]='\0';
//	printf("Whats being sent %s\n",buf);
	int sendStatus=write(sockInUse, buf,sizeof(buf));
	if(sendStatus==-1){
	//	perror(sendStatus);
		printf("Send failed during open\n");
		return -1;	
	}
	char recbuf[256];
	memset(recbuf, '\0', sizeof(recbuf));
	read(sockInUse,recbuf,sizeof(recbuf));
//	printf("Whats being returned %s\n",recbuf);
	if(recbuf[0]=='%'){
		printf("No file found\n");
		return -1;	
	}else if(recbuf[0]=='&'){
		return -1;
	}
	return recbuf[0]+'0';
	
}

ssize_t netread(int fildes, void* buf, size_t nbyte){
	if(hostFound){
		h_errno = HOST_NOT_FOUND;
		return -1;		
	}
	int sockInUse=sockOpen();
	if(sockInUse==-1){
		return -1;	
	}
	char *array=(char*)buf;
	if(fildes==-1){
		return -1;
		
	}
	int counter=0;
	char newbuf[2+2+1];
	memset(newbuf, '\0', sizeof(newbuf));
	newbuf[0]='R';
	newbuf[1]=' ';
	newbuf[2]=fildes-'0';
	newbuf[3]=' ';
//	buf[4]= mode+'0';
	newbuf[4]=nbyte-'0';
/*	int counter=0;
	while(counter<strlen()){
		buf[4+counter]=pathname[counter];	
		counter++;
	}
	newbuf[counter]='\0';
*/	int sendStatus=send(sockInUse, newbuf,sizeof(newbuf),0);
	if(sendStatus==-1){
		printf("Send failed\n");
		return -1;	
	}
	
//	int x;
	char recbuf[nbyte+3];
	
	memset(recbuf, '\0', sizeof(recbuf));
	//int x=recbuf[0];
//	printf("String:%s\n","Waiting");
	read(sockInUse,recbuf,sizeof(recbuf));
//	printf("did u get stuxkhere\n");
	int x=recbuf[0]+'0';
	while(counter<x){
		if(recbuf[counter]=='\0'){
			break;
		}
		array[counter]=recbuf[counter+2];
		counter++;
	}
//	printf("String:%s\n",array);
	return x;
	
	
}	
ssize_t netwrite(int fildes, const void* buf, size_t nbyte){
	if(hostFound){
		h_errno = HOST_NOT_FOUND;
		return -1;		
	}
	int sockInUse=sockOpen();
	if(sockInUse==-1){
		return -1;	
	}
	char *array=(char*)buf;
	int counter=0;
	char newbuf[2+2+2+nbyte];
	memset(newbuf, '\0', sizeof(newbuf));
	newbuf[0]='W';
	newbuf[1]=' ';
	newbuf[2]=fildes-'0';
	newbuf[3]=' ';
	newbuf[4]=nbyte-'0';
	while(counter<(nbyte-5)){
		newbuf[counter+5]=array[counter];
		counter++;
	}	
	int sendStatus=send(sockInUse, newbuf,sizeof(newbuf),0);
	char recbuf[256];
	read(sockInUse,recbuf,sizeof(recbuf));
	//	printf("did u get stuxkhere\n");
	int x=recbuf[0]+'0';
//	printf("Put this many characters ing:%d\n",x);
	return x;	
}

int netclose(int fildes){
	if(hostFound){
		h_errno = HOST_NOT_FOUND;
		return -1;
			
	}
	int sockInUse=sockOpen();
	if(sockInUse==-1){
		return -1;	
	}
	char newbuf[256];
	newbuf[0]='C';
	newbuf[1]=' ';
	newbuf[2]=fildes-'0';
	int sendStatus=send(sockInUse, newbuf,sizeof(newbuf),0);
	if(sendStatus==-1){
		printf("Send failed\n");
		return -1;	
	}
	memset(newbuf, '\0', sizeof(newbuf));
	char recbuf[256];
	memset(recbuf, '\0', sizeof(recbuf));
	read(sockInUse,recbuf,sizeof(recbuf));
	return recbuf[0]+'0';

}
int main(){
	netserverinit("top.cs.rutgers.edu",0);	
	int x=	netopen("fun.txt",O_RDWR);
	char buf[64];
//	printf("Got this many bytes:%d\n",netread(x,buf,63));
	netclose(x);
//	printf("stuckhere?\n");

	int y=netopen("pop.txt",O_RDWR);
	netwrite(y,buf,63);
	netread(y,buf,63);
	netclose(y);
	return 0;

}
