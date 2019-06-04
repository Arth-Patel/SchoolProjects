
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct cacheBlock{
	long long int tag;
	long long int offset;
	struct cacheBlock *next;
};

int poweroftwo(int check){//makes sure the numbers are powers of 2's
	if(check==1){
		return 0;
	}
	if(check%2){
		return 1;
	}else{
		return poweroftwo(check/2);
	}
}

int whichPower(int number){
	int counter=0;
	while(number!=1){
		number=number/2;
		counter++;
	}
	return counter;
}

int main(int argc, char *argv[]){
	if(argc!=6){//makes sure right amount of arguments
		printf("Usage ./cachesim cachesize associativity ReplacementPolicy BlockSize TraceFile\n");
		return 1;
	}
	int temp2;
	int counter=0;
	char assocnum[10];
	int lines=0;
	int sizeofarray;
	int cacheSize=atoi(argv[1]);
	int blockSize=atoi(argv[4]);
	if(!strcmp(argv[2],"direct")){//figures out the mapping
		sizeofarray=cacheSize/blockSize;
		lines=1;
	}else if(!strcmp(argv[2],"assoc")){
		sizeofarray=1;
		lines=cacheSize/blockSize;
	}else{
		temp2=strlen(argv[2])-6;
		while(counter<temp2){
			assocnum[counter]=argv[2][counter+6];
			counter++;
		}
		lines=atoi(assocnum);
		sizeofarray=cacheSize/blockSize/lines;
		counter=0;
	}
	if(poweroftwo(lines)||poweroftwo(blockSize)||poweroftwo(cacheSize)){
		printf("The numbers are not powers of 2\n");
		return 1;
	}
	FILE *fp;
	fp=fopen(argv[5],"r");
	if(fp=='\0'){//opens the file
		printf("File can't be read\n");	
		return 1;
	}
	int offsetvalue=whichPower(blockSize);
	int bitsize=blockSize-1;
	int powerofsize=whichPower(sizeofarray);
	char temp;
	int secondary;
	int linetarget;
	int hits=0;
	int misses=0;
	int writes=0;
	int reads=0;
	int nodes=0;
	int inCache=0;
	struct cacheblock* fullCache[sizeofarray];
	while(counter<sizeofarray){//creates start of hashtable
		struct cacheBlock *item = (struct cacheBlock*) malloc(sizeof(struct cacheBlock));
		fullCache[counter]=item;
		item->next=NULL;
		item->tag=-1;
		item->offset=-1;
		counter++;
	}
	char address[48];
	long long int hexa;
	while(!feof(fp)){
		fscanf(fp,"%s %c %lx",address,&temp,&hexa);
		if(!strcmp(address,"#eof")){
			break;
		}
		secondary=0;
		inCache=0;
		struct cacheBlock *ptr=fullCache[(hexa>>offsetvalue)&(sizeofarray-1)];
		nodes=0;
		while(ptr!=NULL&&nodes<lines){//checking linked list
			if(ptr->tag==(hexa>>offsetvalue>>powerofsize)){
				inCache=1;	
			}
			ptr=ptr->next;
			nodes++;
		}
		if(!inCache){
			struct cacheBlock *new=(struct cacheBlock*)malloc(sizeof(struct cacheBlock));	
			new->next=fullCache[(hexa>>offsetvalue)&(sizeofarray-1)];
			fullCache[(hexa>>offsetvalue)&(sizeofarray-1)]=new;
			new->tag=hexa>>offsetvalue>>powerofsize;
			new->offset=hexa&bitsize;
		//	struct cacheBlock *new=(struct cacheBlock*)malloc(sizeof(struct cacheBlock));	
		//	new->next=fullCache[(hexa>>offsetvalue)&(sizeofarray-1)];
		//	fullCache[(hexa>>offsetvalue)&(sizeofarray-1)]=new;
		//	new->tag=hexa>>offsetvalue>>powerofsize;
		//	new->offset=hexa&bitsize;
/*			linetarget=((hexa>>offsetvalue)&(sizeofarray-1))+1;
			if(linetarget>=sizeofarray){
				linetarget=0;	
				

			}else{	
				ptr=fullCache[linetarget];
				nodes=0;
				while(ptr!=NULL&&nodes<lines){//checking linked list
					if(ptr->tag==(hexa>>offsetvalue>>powerofsize)){
						secondary=1;	
					}
					ptr=ptr->next;
					nodes++;
				}
				if(!secondary){
					reads++;
					struct cacheBlock *flop=(struct cacheBlock*)malloc(sizeof(struct cacheBlock));	
					flop->next=fullCache[linetarget];
					fullCache[linetarget]=flop;
					flop->tag=hexa>>offsetvalue>>powerofsize;
				}
			}
*/		}	
		if(temp=='W'){
			if(inCache){
				hits++;
				writes++;
			}else{
				misses++;
				reads++;
				writes++;
			}			
			
		}else if(temp=='R'){	
			if(inCache){
				hits++;
				
			}else{
				misses++;
				reads++;
				
			}
		}else{
			printf("mistake\n");
				
		}	
	}	
	printf("no-prefetch\n");	
	printf("Cache hits: %d\n",hits);
	printf("Cache misses: %d\n",misses);
	printf("Memory reads: %d\n",reads);
	printf("Memory writes: %d\n",writes);
	hits=0;
	misses=0;
	writes=0;
	reads=0;
	counter=0;
	rewind(fp);
	while(counter<sizeofarray){//emptying the  hashtable
		struct cacheBlock *item = (struct cacheBlock*) malloc(sizeof(struct cacheBlock));
		fullCache[counter]=item;
		item->next=NULL;
		item->tag=-1;
		item->offset=-1;
		counter++;
	}
   
	while(!feof(fp)){//prefetching
		fscanf(fp,"%s %c %lx",address,&temp,&hexa);
		if(!strcmp(address,"#eof")){
			break;
		}
		inCache=0;
		struct cacheBlock *ptr=fullCache[(hexa>>offsetvalue)&(sizeofarray-1)];
		secondary=0;
		nodes=0;
		while(ptr!=NULL&&nodes<lines){//checking linked list
			if(ptr->tag==(hexa>>offsetvalue>>powerofsize)){
				inCache=1;	
			}
			ptr=ptr->next;
			nodes++;
		}
		if(!inCache){
			struct cacheBlock *new=(struct cacheBlock*)malloc(sizeof(struct cacheBlock));	
			new->next=fullCache[(hexa>>offsetvalue)&(sizeofarray-1)];
			fullCache[(hexa>>offsetvalue)&(sizeofarray-1)]=new;
			new->tag=hexa>>offsetvalue>>powerofsize;
			new->offset=hexa&bitsize;
			linetarget=((hexa+blockSize)>>offsetvalue)&(sizeofarray-1);
			if(linetarget>=sizeofarray){
				linetarget=0;
				
	//		}
			}else{	//if not in cache,check if A+B is in cache
				ptr=fullCache[linetarget];
				nodes=0;
				while(ptr!=NULL&&nodes<lines){//checking linked list
					if(ptr->tag==((hexa+blockSize)>>offsetvalue>>powerofsize)){
						secondary=1;	
					}
					ptr=ptr->next;
					nodes++;
				}
				if(!secondary){
					reads++;
					struct cacheBlock *flop=(struct cacheBlock*)malloc(sizeof(struct cacheBlock));	
					flop->next=fullCache[linetarget];
					fullCache[linetarget]=flop;
					flop->tag=(hexa+blockSize)>>offsetvalue>>powerofsize;
				}
			}
		}	
		if(temp=='W'){
			if(inCache){
				hits++;
				writes++;
			}else{
				misses++;
				reads++;
				writes++;
				/*
				ptr=fullCache[((hexa>>offsetvalue)&(sizeofarray-1))+1];
				nodes=0;
				while(ptr!=NULL&&nodes<lines){//checking linked list
					if(ptr->tag==(hexa>>offsetvalue>>powerofsize)){
						secondary=1;	
					}
					ptr=ptr->next;
					nodes++;
				}
				if(!secondary){
					reads++;
					struct cacheBlock *flop=(struct cacheBlock*)malloc(sizeof(struct cacheBlock));	
					flop->next=fullCache[(hexa>>offsetvalue)&(sizeofarray-1)+1];
					fullCache[((hexa>>offsetvalue)&(sizeofarray-1))+1]=flop;
					flop->tag=hexa>>offsetvalue>>powerofsize;
				
				}*/	


			}			
			
		}else if(temp=='R'){	
			if(inCache){
				hits++;
				
			}else{
				misses++;
				reads++;
/*				struct cacheBlock* ptr2=fullCache[(((hexa>>offsetvalue)&(sizeofarray-1))+1)];
				nodes=0;
				while(ptr2!=NULL&&nodes<lines){//checking linked list
					if(ptr2->tag==(hexa>>offsetvalue>>powerofsize)){
						secondary=1;	
					}
					ptr2=ptr2->next;
					nodes++;
				}
/				if(!secondary){
					reads++;
					struct cacheBlock *flop=(struct cacheBlock*)malloc(sizeof(struct cacheBlock));	
					flop->next=fullCache[(hexa>>offsetvalue)&(sizeofarray-1)+1];
					fullCache[(hexa>>offsetvalue)&(sizeofarray-1)+1]=flop;
					flop->tag=hexa>>offsetvalue>>powerofsize;
				
				}
*/			}
		}else{
			printf("mistake\n");
				
		}	
	}	
	printf("with-prefetch\n");	   
	printf("Cache hits: %d\n",hits);
	printf("Cache misses: %d\n",misses);
	printf("Memory reads: %d\n",reads);
	printf("Memory writes: %d\n",writes);
	   
			   
	return 0;
}

