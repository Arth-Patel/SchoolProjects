/*
 **********************************************
 *  CS314 Principles of Programming Languages *
 *  Fall 2018                                 *
 *  File: filter.c                            *
 *  Date: 11/25/2018                          *
 **********************************************
 */

#include "filter.h"

void count_unmatched_vertices(int threadId, int threadNum, int nodeNum,
                              int *nodeToProcess, int *res,
                              int *nodeCount)
{

	int workchunk=(nodeNum +threadNum-1)/threadNum;
	int firstcounter=threadId*workchunk;
	int end=firstcounter+workchunk;
	int curr;
//	printf("a\n");
	if(nodeNum<end){
		end=nodeNum;
	}
	nodeCount[threadId]=0;
	while(firstcounter<end){
		if(res[nodeToProcess[firstcounter]]==-1){
			nodeCount[threadId]++;
		}
		firstcounter++;
	}
   /*	int workchunk=(nodeNum +threadNum-1)/threadNum;
	printf("poopy\n");
	int firstcounter=threadId*workchunk;
	int end=firstcounter+workchunk;
	nodeCount[threadId]=0;
	while(firstcounter<end){
		if(res[nodeToProcess[firstcounter]]==-2){
			nodeCount[threadId]++;
		}
		firstcounter++;
	}*/
}

void update_remain_nodes_index(int threadId, int threadNum,
                               int *nodeToProcess, int *startLocations,
                               int *res,
                               int nodeNum, int *newNodeToProcess)
							  
{
	int workchunk=(nodeNum +threadNum-1)/threadNum;
	int firstcounter=threadId*workchunk;
	int end=firstcounter+workchunk;
	int curr;
	int offset;
//	printf("a\n");
	if(nodeNum<end){
		end=nodeNum;
	}
	while(firstcounter<end){
		if(res[nodeToProcess[firstcounter]]==-1){
			offset=startLocations[threadId]++;
			newNodeToProcess[offset]=nodeToProcess[firstcounter];
		}
		firstcounter++;
	}
	
 /*	int workchunk=(nodeNum +threadNum-1)/threadNum;
	int firstcounter=threadId*workchunk;
	int end=firstcounter+workchunk;
	printf("doopy\n");
	int x=0;
	while(firstcounter<end){
		if(res[nodeToProcess[firstcounter]]==-1){
			x=startLocations[threadId]++;
			newNodeToProcess[x]=nodeToProcess[firstcounter];	
		}
		firstcounter++;
	}
*/
}
