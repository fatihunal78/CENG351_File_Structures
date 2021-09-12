//libraries for functions that are used in the program
//libraries that are implemented by us for only this program
#include<iostream.h>
#include<stdlib.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<iomanip>
#include"studentinfo.h"
#include"cosequential.h"
#include"ibuffering.h"
#include"obuffering.h"

using namespace std;

//file pointers for opening reading and writing from/to files
FILE *filein,*fileout;

//temporary array for reading from the input files
char recptr[100][13];

int x=0,y=0;
char ch;

int main()
{
	Heap heap(100);
	Merge merge;

	//opens the given files and writes to temporary files,in the end closes the file pointers for later accesses
	filein=fopen("sectionA.txt","r");
	fileout=fopen("sectionAsort.txt","w");
	for (y=0;y<100; y++)
	{
		x=0;
		do
		{
			ch=fgetc(filein);
			recptr[y][x]=ch;
			x++;
		}
		while(ch!='\n');
		recptr[y][12]=0;
		heap.insert(recptr[y]);
	}
	for (y=0; y<100 ;y++)
	{
		fprintf(fileout,"%s\n",heap.remove());
	}
	fclose(fileout);
	fclose(filein);
	
	
	filein=fopen("sectionB.txt","r");
	fileout=fopen("sectionBsort.txt","w");
	for (y=0;y<100; y++)
	{
		x=0;
		do
		{
			ch=fgetc(filein);
			recptr[y][x]=ch;
			x++;
		}
		while(ch!='\n');
		recptr[y][12]=0;
		heap.insert(recptr[y]);
	}
	for (y=0; y<100 ;y++)
	{
		fprintf(fileout,"%s\n",heap.remove());
	}
	fclose(fileout);
	fclose(filein);
	

	filein=fopen("sectionC.txt","r");
	fileout=fopen("sectionCsort.txt","w");
	for (y=0;y<100; y++)
	{
		x=0;
		do
		{
			ch=fgetc(filein);
			recptr[y][x]=ch;
			x++;
		}
		while(ch!='\n');
		recptr[y][12]=0;
		heap.insert(recptr[y]);
	}
	for (y=0; y<100 ;y++)
	{
		fprintf(fileout,"%s\n",heap.remove());
	}
	fclose(fileout);
	fclose(filein);
	
	
	filein=fopen("sectionD.txt","r");
	fileout=fopen("sectionDsort.txt","w");
	for (y=0;y<100; y++)
	{
		x=0;
		do
		{
			ch=fgetc(filein);
			recptr[y][x]=ch;
			x++;
		}
		while(ch!='\n');
		recptr[y][12]=0;
		heap.insert(recptr[y]);
	}
	for (y=0; y<100 ;y++)
	{
		fprintf(fileout,"%s\n",heap.remove());
	}
	fclose(fileout);
	fclose(filein);

	//calling Merge class functions
	merge.buffersortedfiles();
	merge.mergeAandB();
	merge.mergeCandD();
	merge.merge_them_all();
	
	//renames the temporary files and their names are turned into the original ones
	rename("sectionAsort.txt","sectionA.txt");
	rename("sectionBsort.txt","sectionB.txt");
	rename("sectionCsort.txt","sectionC.txt");
	rename("sectionDsort.txt","sectionD.txt");
	
	return 0;
      
}
