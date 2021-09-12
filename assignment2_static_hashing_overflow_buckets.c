#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

FILE * student, * course, * stdhash, * crshash;

int stdrecords, crsrecords;
int stdhashrecords, crshashrecords;
int stdstudentno, crsstudentno;
int stdrecpos, crsrecpos;
int hashedlocstd,hashedloccrs;
int strstring,crsstring;

char studentnumber[10];
char coursenumber[10];

char stdStudentID[8];
char stdStudentName[16];
char stdDepartment[5];
char stdYear[2];

char crsStudentID[8];
char crsCourseID[8];
char crsCourseGrade[2];

void menuprogram(void)
{
	char ch3=0,ch4=0;
	int option=0;
	int printoption;
	int stdquery;
	
	while(option !=5)
	{
		printf("\n");
		printf("MENU:\n   Select your option:\n\t->Press 1 to Create a hash file for students\n\t->Press 2 to Create a hash file for course registration\n\t->Press 3 to Query the files\n\t->Press 4 to Print the hash file\n\t->Press 5 to Quit\n\nOption?:");
		scanf("%d",&option);
		printf("\n");
		
		if(option==1)
		{
			printf("creating a hash file for student file...\n");
			fclose(student);
			fclose(stdhash);
		}
		
		if(option==2)
		{
			printf("creating a hash file for course registration file...\n");
			fclose(course);
			fclose(crshash);
		}
		
		if(option==3)
		{
			
			stdquery=1000000;
			
			while(stdquery > 999999 && stdquery < 10000000)
			{
				printf("please enter the studentID:");
				scanf("%d",&stdquery);
				printf("\n");
				printf("Student ID\tStudent Name\tDepartment\tYear\n");
				printf("Course ID\t Grade\n");
			}
			printf("\n");
		}

		if(option==4)
		{
			printf("Print hash file menu:\n\t->for student hash file press 0\n\t->for course hash file press 1\n\nyour choice?:");
			scanf("%d",&printoption);
			
			if(printoption==0)
			{
				printf("printing student hash file on screen ...\n");
				rewind(stdhash);
				ch3=0;
				
				while(ch3!=EOF)
					printf("%c",ch3=fgetc(stdhash));
			}
			
			if(printoption==1)
			{
				printf("printing course hash file on screen ...\n");
				rewind(crshash);
				ch4=0;
				
				while(ch4!=EOF)
					printf("%c",ch4=fgetc(crshash));
			}
		}
		
		if(option==5)
		{
			printf("OK Exiting...\n");
			return;
		}
		
		printf("\n");
		printf("*************************************************************************************\n");
	}
}

void readstudentfile(void)
{
	char ch1=0;
	int i1=0;
	
	do
	{
		ch1=fgetc(student);
		studentnumber[i1]=ch1;
		i1++;
	}
	while(ch1 !='\n');
	studentnumber[i1-1]=0;

	stdrecords=atoi(studentnumber);
	strstring=strlen(studentnumber);
}

void readstudentrecords(void)
{
	int i=0;
	
	 stdStudentID[7]=0;
	 stdStudentName[15]=0;
	 stdDepartment[4]=0;
	 stdYear[1]=0;
	 
	 
	 for(i=0;i<7;i++)
	 {
		 stdStudentID[i]=fgetc(student);
	 }
	 
	 stdstudentno=atoi(stdStudentID);
	 
	 for(i=0;i<15;i++)
	 {
		 stdStudentName[i]=fgetc(student);
	 }
	 for(i=0;i<4;i++)
	 {
		 stdDepartment[i]=fgetc(student);
	 }
	 for(i=0;i<1;i++)
	 {
		 stdYear[i]=fgetc(student);
	 }
	 
	 stdrecpos=((int)ftell(student)-strlen(studentnumber))/28;
	 
	 hashedlocstd=stdstudentno % stdhashrecords;
	 printf("%d %d\n",hashedlocstd,stdrecpos);
	 
	 fgetc(student);
	 
}

void readcoursefile(void)
{
	char ch2=0;
	int i2=0;
	
	do
	{
		ch2=fgetc(course);
		coursenumber[i2]=ch2;
		i2++;
	}
	while(ch2 !='\n');
	coursenumber[i2-1]=0;
	
	crsrecords=atoi(coursenumber);
	crsstring=strlen(coursenumber);
}

void readcourserecords(void)
{
	int i=0;
	
	crsStudentID[7]=0;
	crsCourseID[7]=0;
	crsCourseGrade[1]=0;

	for(i=0;i<7;i++)
	{
		crsCourseID[i]=fgetc(course);
	}
	for(i=0;i<7;i++)
	{
		crsStudentID[i]=fgetc(course);
	}
	
	crsstudentno=atoi(crsStudentID);
	
	for(i=0;i<1;i++)
	{
		crsCourseGrade[i]=fgetc(course);
	}
	
	crsrecpos=((int)ftell(course)-strlen(coursenumber))/16;
	
	hashedloccrs=crsstudentno % crshashrecords;
	printf("%d %d\n",hashedloccrs,crsrecpos);

	
	fgetc(course);
	
}

void fillstudenthashfile(void)
{
	int i=0,j=0,k=0;
	int t1=0;
	
	t1=0;
	for(j=0; j<stdhashrecords ;j++)
	{
		fprintf(stdhash,"$");
		t1++;
		
		for(k=0;k<5;k++)
		{
			fprintf(stdhash," ");
			t1++;
			fprintf(stdhash,"$");
			t1++;
			fprintf(stdhash," ");
			t1++;
			
			for(i=0;i<7;i++)
			{
				fprintf(stdhash,"$");
				t1++;
			}
			for(i=0;i<15;i++)
			{
				fprintf(stdhash,"$");
				t1++;
			}
			for(i=0;i<4;i++)
			{
				fprintf(stdhash,"$");
				t1++;
			}
			for(i=0;i<1;i++)
			{
				fprintf(stdhash,"$");
				t1++;
			}
			
		}
		
		fprintf(stdhash," ");
		t1++;
		
		for(i=0;i<7;i++)
		{
			fprintf(stdhash,"$");
			t1++;
		}
		
		fprintf(stdhash,"\n");
	}
	fprintf(stdhash,"\0");
	
}

void fillcoursehashfile(void)
{
	int i=0,j=0, k=0;
	int t2=0;

	t2=0;
	for(j=0; j<crshashrecords ;j++)
	{
		 fprintf(crshash,"$");
		 t2++;
		 
		 for(k=0;k<5;k++)
		 {
			 fprintf(crshash," ");
			 t2++;
			 fprintf(crshash,"$");
			 t2++;
			 fprintf(crshash," ");
			 t2++;
			 
			 for(i=0;i<7;i++)
			 {
				 fprintf(crshash,"$");
				 t2++;
			 }
			 for(i=0;i<7;i++)
			 {
				 fprintf(crshash,"$");
				 t2++;
			 }
			 for(i=0;i<1;i++)
			 {
				 fprintf(crshash,"$");
				 t2++;
			 }
			 
		 }
		 
		 fprintf(crshash," ");
		 t2++;
		 
		 for(i=0;i<7;i++)
		 {
			 fprintf(crshash,"$");
			 t2++;
		 }
		 
		 fprintf(crshash,"\n");
	 }
	 fprintf(crshash,"\0");
	 
}

void createstudenthash(void)
{
	int t=0,i=0;
	int sqrtno=0;

	stdhashrecords=(stdrecords*10/7)/5;
	printf("%d\n",stdhashrecords);
	
	t=1;
	while(t)
	{
		sqrtno=(int)sqrt(stdhashrecords);
		for (i=2;i<=sqrtno;i++)
		{
			t=0;
			if(stdhashrecords%i==0)
			{
				t=1;
				stdhashrecords=stdhashrecords+1;
				break;
			}
		}
	}
	
}

void createcoursehash(void)
{
	int i=0,t=0;
	int sqrtno;
	
	crshashrecords=(crsrecords*10/7)/5;
	printf("%d\n",crshashrecords);
	
	t=1;
	while(t)
	{
		sqrtno=(int)sqrt(crshashrecords);
		for (i=2;i<=sqrtno;i++)
		{
			t=0;
			if(crshashrecords%i==0)
			{
				t=1;
				crshashrecords=crshashrecords+1;
				break;
			}
		}
	}
}


int main(int argc,char *argv[])
{
	int i=0;
	int result;
	char tmp;
	
	student=fopen(argv[1],"r");
	course=fopen(argv[2],"r");
	stdhash=fopen("studenthashfile.txt","wa+");
	crshash=fopen("coursehashfile.txt","wa+");
	
	readstudentfile();
	readcoursefile();
	
	createstudenthash();
	createcoursehash();

	printf("%d %d\n",stdhashrecords,crshashrecords);
	
	fillstudenthashfile();
	fillcoursehashfile();

	
	for(i=0;i<stdrecords;i++)
	{
		printf("(%d)",i);
		readstudentrecords();
		
		result=fseek(stdhash, hashedlocstd*160,SEEK_SET);
		if(!result && (tmp=fgetc(stdhash))!='$' && tmp >='0' && tmp<'5')
		{
			fseek(stdhash, hashedlocstd*160,SEEK_SET);
			fputc(tmp+1,stdhash);
		}
		fseek(stdhash, hashedlocstd*160,SEEK_SET);
		if(!result && fgetc(stdhash)=='$')
		{
			fseek(stdhash, hashedlocstd*160,SEEK_SET);
			fputc('0',stdhash);
		}
	
	}
	
	for(i=0;i<crsrecords;i++)
	{
		printf("(%d)",i);
		readcourserecords();

		fseek(crshash, hashedloccrs*100,SEEK_SET);
		if((tmp=fgetc(crshash))!='$' && tmp >='0' && tmp<'5')
		{
			fseek(crshash, hashedloccrs*100,SEEK_SET);
			fputc(tmp+1,crshash);
		}
		fseek(crshash, hashedloccrs*100,SEEK_SET);
		if(fgetc(crshash)=='$')
		{
			fseek(crshash, hashedloccrs*100,SEEK_SET);
			fputc('0',crshash);
		}		
	}

	menuprogram();
	return 0;
}
