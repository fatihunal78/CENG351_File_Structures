#include"studentinfo.h"
#include<string.h>
#define TRUE  1
#define FALSE 0

//initialization
Heap::Heap(int size)
{
	totalelements= size;
	heaparray= new char * [totalelements+1];
	elementno =0;
}

//insertion of each record in heaparray
int Heap::insert(char * newkey)
{
	if (elementno== totalelements)
		return FALSE;
	elementno++;
	heaparray[elementno]= newkey;
	
	int child=elementno;
	int parent;
	while(child> 1)
	{
		parent = child/2;
		if(compare(child,parent) >= 0)
			break;
		swap(child,parent);
		child=parent;
	}
	return TRUE;
}

//swapping necessary records
void Heap::swap(int i,int j)
{
	char * temp=heaparray[i];
	heaparray[i]=heaparray[j];
	heaparray[j]=temp;
}

//removing from the heaparray and puts them in temporary array
char * Heap::remove()
{
	char * val= heaparray[1];
	heaparray[1]=heaparray[elementno];
	elementno--;
	int child=1;
	int newk;
	while (2*child <= elementno)
	{
		if(compare(2*child,2*child+1)<0)
			newk=2*child;
		
		else newk=2*child+1;
		
		if(compare(child,newk) < 0)
			break;
		swap(child,newk);
		child=newk;
	}
	return val;
}

//compares two records lexiographically 
int Heap::compare(int i,int j)
{
	if(j > elementno) 
		return -1;
	else	return strcmp(heaparray[i],heaparray[j]);
}
