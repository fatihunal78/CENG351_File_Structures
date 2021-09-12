#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include"cosequential.h"

//file pointers for opening reading and writing from/to files
FILE *opentext;
FILE *mergedlist;
FILE *statistics;

//temporary sorted arrays for the A B C and D sections,these files will be used
//in merging
char sortedA[100][13];
char sortedB[100][13];
char sortedC[100][13];
char sortedD[100][13];

//temporary sorted arrays for merging A and B & C and D sections.
char step1_1[200][13];
char step1_2[200][13];

//temporary sorted array for the total merged file
char step2[400][13];

int a,b,c,d,e,f;
int i=0,j=0;

//variables for statistics about average grade of each year of graduation
int grad2007=0;
int aver2007=0;
int final2007=0;
int total2007=0;

int grad2008=0;
int aver2008=0;
int final2008=0;
int total2008=0;

int grad2009=0;
int aver2009=0;
int final2009=0;
int total2009=0;

//reads the temporary files for each section and assigns values to the temporary arrays for merging 

void Merge::buffersortedfiles(void)
{
	//section A
	opentext=fopen("sectionAsort.txt","r");
	for(i=0;i<100;i++)
	{
		for(j=0;j<13;j++)
			sortedA[i][j]=fgetc(opentext);
		sortedA[i][12]=0;
	}
	
	//section B
	opentext=fopen("sectionBsort.txt","r");
	for(i=0;i<100;i++)
	{
		for(j=0;j<13;j++)
			sortedB[i][j]=fgetc(opentext);
		sortedB[i][12]=0;
	}
	
	//section C
	opentext=fopen("sectionCsort.txt","r");
	for(i=0;i<100;i++)
	{
		for(j=0;j<13;j++)
			sortedC[i][j]=fgetc(opentext);
		sortedC[i][12]=0;
	}
	
	//section D
	opentext=fopen("sectionDsort.txt","r");
	for(i=0;i<100;i++)
	{
		for(j=0;j<13;j++)
			sortedD[i][j]=fgetc(opentext);
		sortedD[i][12]=0;
	}
}

//merges sorted section A and B arrays.compares each record one by one and assigns values to temporary arrays
void Merge::mergeAandB(void)
{
	a=0;
	b=0;
	for(i=0;i<200;i++)
	{
		if(b==100 && a<100)
		{
			for(j=0;j<12;j++)
			{
				step1_1[i][j]=sortedA[a][j];
			}
			step1_1[i][12]=0;
			a++;
			continue;
		}
		
		if(a==100 && b<100)
		{
			for(j=0;j<12;j++)
			{
				step1_1[i][j]=sortedB[b][j];
			}
			step1_1[i][12]=0;
			b++;
			continue;
		}
		
		if(strcmp(sortedA[a],sortedB[b])>0 && (a<100) && (b<100))
		{
			for(j=0;j<12;j++)
			{
				step1_1[i][j]=sortedB[b][j];
			}
			step1_1[i][12]=0;
			b++;
			continue;
		}
		
		if(strcmp(sortedA[a],sortedB[b])<0  && (a<100) && (b<100))
		{
			for(j=0;j<12;j++)
			{
				step1_1[i][j]=sortedA[a][j];
			}
			step1_1[i][12]=0;
			a++;
			continue;
		}
	}
	
}

//merges sorted section C and D arrays.compares each record one by one and assigns values to temporary arrays
void Merge::mergeCandD(void)
{
	c=0;
	d=0;
	for(i=0;i<200;i++)
	{
		if(d==100 && c<100)
		{
			for(j=0;j<12;j++)
			{
				step1_2[i][j]=sortedC[c][j];
			}
			step1_2[i][12]=0;
			c++;
			continue;
		}
		
		if(c==100 && d<100)
		{
			for(j=0;j<12;j++)
			{
				step1_2[i][j]=sortedD[d][j];
			}
			step1_2[i][12]=0;
			d++;
			continue;
		}
		
		if(strcmp(sortedC[c],sortedD[d])>0 && (c<100) && (d<100))
		{
			for(j=0;j<12;j++)
			{
				step1_2[i][j]=sortedD[d][j];
			}
			step1_2[i][12]=0;
			d++;
			continue;
		}
		
		if(strcmp(sortedC[c],sortedD[d])<0  && (c<100) && (d<100))
		{
			for(j=0;j<12;j++)
			{
				step1_2[i][j]=sortedC[c][j];
			}
			step1_2[i][12]=0;
			c++;
			continue;
		}
	}
	
}

//merges sorted the two temporary arrays.compares each record one by one and assigns values to the biggest temporary array
//and also computes the average value for every graduation year during the merging process
void Merge::merge_them_all(void)
{
	mergedlist=fopen("mergedlist.txt","w");
	statistics=fopen("statistics.txt","w");
	
	e=0;
	f=0;
	for(i=0;i<400;i++)
	{
		if(f==200 && e<200)
		{
			for(j=0;j<12;j++)
			{
				step2[i][j]=step1_1[e][j];
			}
			step2[i][12]=0;
			e++;
			fprintf(mergedlist,"%s\n",step2[i]);
			
			//prints the first 15 value of the mergedlist.txt file in every if statement like this
			if(i<15)
				fprintf(statistics,"%s\n",step2[i]);
			
			//controls the graduation year and does the necessary computations in every if statement
			if (step2[i][8]=='7')
			{
				grad2007++;
				final2007=100*(step2[i][9]-48)+10*(step2[i][10]-48)+(step2[i][11]-48);
				total2007+=final2007;
				aver2007=total2007/grad2007;
			}
			
			if (step2[i][8]=='8')
			{
				grad2008++;
				final2008=100*(step2[i][9]-48)+10*(step2[i][10]-48)+(step2[i][11]-48);
				total2008+=final2008;
				aver2008=total2008/grad2008;
			}
			
			if (step2[i][9]=='9')
			{
				grad2009++;
				final2009=100*(step2[i][9]-48)+10*(step2[i][10]-48)+(step2[i][11]-48);
				total2009+=final2009;
				aver2009=total2009/grad2009;
			}
			
			continue;
			
		}

		if(e==200 && f<200)
		{
			for(j=0;j<12;j++)
			{
				step2[i][j]=step1_2[f][j];
			}
			step2[i][12]=0;
			f++;
			fprintf(mergedlist,"%s\n",step2[i]);
			
			if(i<15)
				fprintf(statistics,"%s\n",step2[i]);
			
			if (step2[i][8]=='7')
			{
				grad2007++;
				final2007=100*(step2[i][9]-48)+10*(step2[i][10]-48)+(step2[i][11]-48);
				total2007+=final2007;
				aver2007=total2007/grad2007;
			}
			
			if (step2[i][8]=='8')
			{
				grad2008++;
				final2008=100*(step2[i][9]-48)+10*(step2[i][10]-48)+(step2[i][11]-48);
				total2008+=final2008;
				aver2008=total2008/grad2008;
			}
			
			if (step2[i][8]=='9')
			{
				grad2009++;
				final2009=100*(step2[i][9]-48)+10*(step2[i][10]-48)+(step2[i][11]-48);
				total2009+=final2009;
				aver2009=total2009/grad2009;
			}
			
			continue;
		}
		
		if((strcmp(step1_1[e],step1_2[f])>0) && (e<200) && (f<200))
		{
			for(j=0;j<12;j++)
			{
				step2[i][j]=step1_2[f][j];
			}
			
			step2[i][12]=0;
			f++;
			fprintf(mergedlist,"%s\n",step2[i]);
			
			if(i<15)
				fprintf(statistics,"%s\n",step2[i]);
			
			if (step2[i][8]=='7')
			{
				grad2007++;
				final2007=100*(step2[i][9]-48)+10*(step2[i][10]-48)+(step2[i][11]-48);
				total2007+=final2007;
				aver2007=total2007/grad2007;
			}
			
			if (step2[i][8]=='8')
			{
				grad2008++;
				final2008=100*(step2[i][9]-48)+10*(step2[i][10]-48)+(step2[i][11]-48);
				total2008+=final2008;
				aver2008=total2008/grad2008;
			}
			
			if (step2[i][8]=='9')
			{
				grad2009++;
				final2009=100*(step2[i][9]-48)+10*(step2[i][10]-48)+(step2[i][11]-48);
				total2009+=final2009;
				aver2009=total2009/grad2009;
			}
			
			continue;
		}

		if((strcmp(step1_1[e],step1_2[f])<0)  && (e<200) && (f<200))
		{
			for(j=0;j<12;j++)
			{
				step2[i][j]=step1_1[e][j];
			}
			
			step2[i][12]=0;
			e++;
			fprintf(mergedlist,"%s\n",step2[i]);
			
			if(i<15)
				fprintf(statistics,"%s\n",step2[i]);
			
			
			if (step2[i][8]=='7')
			{
				grad2007++;
				final2007=100*(step2[i][9]-48)+10*(step2[i][10]-48)+(step2[i][11]-48);
				total2007+=final2007;
				aver2007=total2007/grad2007;
			}
			
			if (step2[i][8]=='8')
			{
				grad2008++;
				final2008=100*(step2[i][9]-48)+10*(step2[i][10]-48)+(step2[i][11]-48);
				total2008+=final2008;
				aver2008=total2008/grad2008;
			}
			
			if (step2[i][8]=='9')
			{
				grad2009++;
				final2009=100*(step2[i][9]-48)+10*(step2[i][10]-48)+(step2[i][11]-48);
				total2009+=final2009;
				aver2009=total2009/grad2009;
			}
			
			continue;
		}
		
	}
	
	
	//prints the average values to the statistics.txt file
	fprintf(statistics,"The average grade of students graduating in year 2007 is: %d\n",aver2007);
	fprintf(statistics,"The average grade of students graduating in year 2008 is: %d\n",aver2008);
	fprintf(statistics,"The average grade of students graduating in year 2009 is: %d\n",aver2009);
	
}
