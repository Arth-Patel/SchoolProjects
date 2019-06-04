/*
 **********************************************
 *  CS314 Principles of Programming Languages *
 *  Fall 2018                                 *
 *  File: oneway.c                            *
 *  Date: 11/25/2018                          *
 **********************************************
 */
#include "oneway.h"
#include "utils.h"

void extend_one_hand(int threadId, int threadNum, GraphData graph,
                     int nodeNum, int *nodeToProcess,
                     int *res, int *strongNeighbor)
{	
	int workchunk=(nodeNum +threadNum-1)/threadNum;
	int firstcounter=threadId*workchunk;
	int end=firstcounter+workchunk;
	int curr;
//	printf("a\n");
	if(nodeNum<end){
		end=nodeNum;
	}
	int secondcounter=0;
	int tempstorage;
	while(firstcounter<end){
		
		curr=nodeToProcess[firstcounter];
//		printf("b %d\n",curr);
		strongNeighbor[curr]=-1;

		while((graph.degree[curr])>secondcounter){
			if(res[graph.index[secondcounter+graph.offset[curr]]]==-1){
				//printf("%d\n",curr);
				
				//	printf("%f > %f\n",graph.weight[secondcounter+graph.offset[curr]],graph.weight[strongNeighbor[curr]]);

				if(strongNeighbor[curr]<0){
					strongNeighbor[curr]=graph.index[secondcounter+graph.offset[curr]];
				}	
			}	
//			printf("%d + %d\n",curr,strongNeighbor[curr]);

			secondcounter++;
		}
		if(strongNeighbor[curr]<0){
			res[curr]=-2;
		}		
		secondcounter=0;
		firstcounter++;
	}
}

void check_handshaking(int threadId, int threadNum,
                       int nodeNum, int *nodeToProcess,
                       int *strongNeighbor, int *res)
{
	int workchunk=(nodeNum +threadNum-1)/threadNum;
	int firstcounter=threadId*workchunk;
	int end=firstcounter+workchunk;
	if(nodeNum<end){
		end=nodeNum;
	}
//	printf("stoopy\n");
	int curr=0;
	int x;
	while(firstcounter<end){
		curr=nodeToProcess[firstcounter];
//		printf("b %d\n",curr);
		x=strongNeighbor[curr];
		if(curr==strongNeighbor[x]){
			res[curr]=x;
		}
		firstcounter++;
	}
}
