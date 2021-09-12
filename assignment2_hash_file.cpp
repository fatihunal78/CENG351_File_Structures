#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<iostream>
#include<iomanip>
#include<cmath>

using namespace std;

char *arg[2];

class Hashing
{
	public:
		FILE * student, * course; //file pointers for input files 
		FILE * stdhash, * crshash; //file pointers for output files
		
		int stdrecords, crsrecords; //# of records in input files
		int stdhashrecords, crshashrecords; //# of records in output files
		int stdstudentno, crsstudentno; //student ID nos
		int stdrecpos, crsrecpos; //line position of a input file pointer
		int hashedlocstd,hashedloccrs; //line position of a output file pointer
		int strstring,crsstring; //string length of input file headers
		int overflowstd,overflowcrs; //overflow area number
		int stdquery; //queried student number
		
		char studentnumber[10]; //fieled for # of records in student file
		char coursenumber[10]; //fieled for # of records in course file
		
		char stdStudentID[8];  //Student ID field for student file
		char stdStudentName[16]; //Student Name field for student file
		char stdDepartment[5]; // Department field for student file
		char stdYear[2]; //Year field
		
		char crsStudentID[8]; //Student ID fieled for course file
		char crsCourseID[8]; //Course ID field for course file
		char crsCourseGrade[2]; //Course Grade field for course file

		void querystd(void); //function that queries student file
		void querycrs(void); //function that queries course file 
		void readstudentfile(void); //reads header of student file
		void readstudentrecords(void); //reads student records one by one
		void readcoursefile(void); //reads header of course file
		void readcourserecords(void); //reads course file records one by one
		void fillstudenthashfile(void); //adds markers to student hash file
		void blankstdline(void); //adds new marked line to student hash file
		void fillcoursehashfile(void); //adds markers to course hash file
		void blankcrsline(void); //adds new marked line to course hash file
		void createstudenthash(void); //generates prime number for hashing 
		void createcoursehash(void); //generates prime number for hashing
		void insertingstd(void); //insert student file records to hash file
		void insertingcrs(void); //insert course file records to hash file 
		void menuprogram(void); //interactive menu for users
};

//this function queries the student hash file according to the student number that is given.and outputs the first result that it finds,because there is only unique student number.if it cant find the result it sends an error to user that it cant find the record for that query.Numbers that are queried must be 7 digits,otherwise program will not ask for the student number again,and turns back to the main menu
void Hashing::querystd(void)
{
	char temp1,temp2,temp3;
	int i,j,k;
	char nextlocstd[8];
	int x;
	int position;
	
	position = stdquery % stdhashrecords;
	fseek(stdhash, position*160,SEEK_SET);
	temp1=fgetc(stdhash);
	
	while(temp1!='0')
	{
		fseek(stdhash, position*160+2,SEEK_SET);
		temp2=fgetc(stdhash);
		j=0;
		
		while(temp2!='0' && j!=150)
		{
			x=0;
			fseek(stdhash, position*160+2+j,SEEK_SET);
			temp2=fgetc(stdhash);
			fseek(stdhash, position*160+4+j,SEEK_SET);
			j=j+30;
			
			for(i=0;i<7;i++)
			{
				stdStudentID[i]=fgetc(stdhash);
			}
			
			stdstudentno=atoi(stdStudentID);
			
			if(stdstudentno==stdquery)
			{
				x=1;
				for(i=0;i<15;i++)
				{
					stdStudentName[i]=fgetc(stdhash);
				}
				for(i=0;i<4;i++)
				{
					stdDepartment[i]=fgetc(stdhash);
				}
				for(i=0;i<1;i++)
				{
					stdYear[i]=fgetc(stdhash);
				}
			}
			
			if(x)
			{
		cout<<stdStudentID<<'\t'<<'\t'<<stdStudentName<<'\t'<<'\t'<<stdDepartment<<'\t'<<'\t'<<stdYear<<endl;
				return;
			}
			
		}
		
		fseek(stdhash, position*160+152,SEEK_SET);
		
		if(fgetc(stdhash)=='-')
		{
			cout<<endl;
			cout<<"for Student ID "<< stdquery <<" no matches are found!"<<endl;
			return;
		}
		else 
		{
			k=0;
			fseek(stdhash, position*160+152,SEEK_SET);
			while((temp3=fgetc(stdhash))!='$')
			{
				nextlocstd[k]=temp3;
				k++;
			}
			nextlocstd[k]=0;
			
			position=atoi(nextlocstd);
			fseek(stdhash, position*160,SEEK_SET);
			temp1=fgetc(stdhash);
		}
	}
}

//this function queries the course hash file according to the student number that is given.and outputs many result that it finds,because there are many courses that a studnt can take.if it cant find the result it sends an error to user that it cant find the record for that query.Numbers that are queried must be 7 digits,otherwise program will not ask for the student number again,and turns back to the main menu.
void Hashing::querycrs(void)
{
	char temp1,temp2,temp3;
	int i,j,k;
	char nextloccrs[8];
	int x;
	int position;
	
	position = stdquery % crshashrecords;
	fseek(crshash, position*100,SEEK_SET);
	temp1=fgetc(crshash);
	
	while(temp1!='0')
	{
		fseek(crshash, position*100+2,SEEK_SET);
		temp2=fgetc(crshash);
		j=0;
		
		while(temp2!='0' && j!=90)
		{
			x=0;
			fseek(crshash, position*100+2+j,SEEK_SET);
			temp2=fgetc(crshash);
			fseek(crshash, position*100+4+j,SEEK_SET);
			j=j+18;
			
			for(i=0;i<7;i++)
			{
				crsStudentID[i]=fgetc(crshash);
			}
			
			stdstudentno=atoi(crsStudentID);
			
			if(stdstudentno==stdquery)
			{
				x=1;
				for(i=0;i<7;i++)
				{
					crsCourseID[i]=fgetc(crshash);
				}
				for(i=0;i<1;i++)
				{
					crsCourseGrade[i]=fgetc(crshash);
				}
				
			}

			if(x)
			{
				cout<<crsCourseID<<'\t'<<'\t'<<crsCourseGrade<<endl;
			}
		}
		
		fseek(crshash, position*100+92,SEEK_SET);
		
		if(fgetc(crshash)=='-')
		{			
			return;
		}
		else
		{
			k=0;
			fseek(crshash, position*100+92,SEEK_SET);
			while((temp3=fgetc(crshash))!='$')
			{
				nextloccrs[k]=temp3;
				k++;
			}
			nextloccrs[k]=0;
			
			position=atoi(nextloccrs);
			fseek(crshash, position*100,SEEK_SET);
			temp1=fgetc(crshash);
		}
	}
}

//this function reads the header of the student input file,it turns the string to integer and finds also the length of the string.
void Hashing::readstudentfile(void)
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

//this function reads the student records one by one,sends the position of line indicator to the variable,and finds the student hash file pointer location for that record,
void Hashing::readstudentrecords(void)
{
	int i=0;
	
	 stdStudentID[7]=0;
	 stdStudentName[15]=0;
	 stdDepartment[4]=0;
	 stdYear[1]=0;
	 
	 stdrecpos=((int)ftell(student)-strlen(studentnumber))/28;
	 
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
	 
	 hashedlocstd=stdstudentno % stdhashrecords;
	 
	 fgetc(student);
	 
}

//this function reads the header of the course input file,it turns the string to integer and finds also the length of the string.
void Hashing::readcoursefile(void)
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

//this function reads the course records one by one,sends the position of line indicator to the variable,and finds the course hash file pointer location for that record,
void Hashing::readcourserecords(void)
{
	int i=0;
	
	crsStudentID[7]=0;
	crsCourseID[7]=0;
	crsCourseGrade[1]=0;

	crsrecpos=((int)ftell(course)-strlen(coursenumber))/16;

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
	
	hashedloccrs=crsstudentno % crshashrecords;

	fgetc(course);
}

//fills the hash file for students,with symbols and zeros .zeros means bucket is not full and the zero at the beginning of each level means how many buckets are full in thaht line.
void Hashing::fillstudenthashfile(void)
{
	int i=0,j=0,k=0;
	int t1=0;
	
	t1=0;
	for(j=0; j<stdhashrecords ;j++)
	{
		fprintf(stdhash,"0");
		
		for(k=0;k<5;k++)
		{
			fprintf(stdhash," ");
			fprintf(stdhash,"0");
			fprintf(stdhash," ");
			
			for(i=0;i<7;i++)
			{
				fprintf(stdhash,"$");
			}
			for(i=0;i<15;i++)
			{
				fprintf(stdhash,"$");
			}
			for(i=0;i<4;i++)
			{
				fprintf(stdhash,"$");
			}
			for(i=0;i<1;i++)
			{
				fprintf(stdhash,"$");
			}
			
		}
		
		fprintf(stdhash," ");
		fprintf(stdhash,"-");
		fprintf(stdhash,"1");
		
		for(i=0;i<5;i++)
		{
			fprintf(stdhash,"$");
		}
		
		fprintf(stdhash,"\n");
	}
	fprintf(stdhash,"\0");
	
}

//adds blank lines to student hash file,as soon as new overflow buckets are needed
void Hashing::blankstdline(void)
{
	int i=0,k=0;

	fseek(stdhash,0L, SEEK_END);
	
	fprintf(stdhash,"0");
	
	for(k=0;k<5;k++)
	{
		fprintf(stdhash," ");
		fprintf(stdhash,"0");
		fprintf(stdhash," ");
		
		for(i=0;i<7;i++)
		{
			fprintf(stdhash,"$");
		}
		for(i=0;i<15;i++)
		{
			fprintf(stdhash,"$");
		}
		for(i=0;i<4;i++)
		{
			fprintf(stdhash,"$");
		}
		for(i=0;i<1;i++)
		{
			fprintf(stdhash,"$");
		}
		
	}
	
	fprintf(stdhash," ");
	fprintf(stdhash,"-");
	fprintf(stdhash,"1");
	
	for(i=0;i<5;i++)
	{
		fprintf(stdhash,"$");
	}
	fprintf(stdhash,"\n");
	
}

//fills the hash file for courses,with symbols and zeros.zeros means bucket is not full and the zero at the beginning of each level means how many buckets are full in thaht line.
void Hashing::fillcoursehashfile(void)
{
	int i=0,j=0, k=0;
	int t2=0;

	t2=0;
	for(j=0; j<crshashrecords ;j++)
	{
		 fprintf(crshash,"0");
		 
		 for(k=0;k<5;k++)
		 {
			 fprintf(crshash," ");
			 fprintf(crshash,"0");
			 fprintf(crshash," ");
			 
			 for(i=0;i<7;i++)
			 {
				 fprintf(crshash,"$");
			 }
			 for(i=0;i<7;i++)
			 {
				 fprintf(crshash,"$");
			 }
			 for(i=0;i<1;i++)
			 {
				 fprintf(crshash,"$");
			 }
			 
		 }
		 
		 fprintf(crshash," ");
		 fprintf(crshash,"-");
		 fprintf(crshash,"1");
		 
		 for(i=0;i<5;i++)
		 {
			 fprintf(crshash,"$");
		 }
		 
		 fprintf(crshash,"\n");
	}
	
	fprintf(crshash,"\0");
	 
}

//adds blank lines to course hash file,as soon as new overflow buckets are needed
void Hashing::blankcrsline(void)
{
	int i=0,k=0;
	
	fseek(crshash,0L, SEEK_END);
	
	fprintf(crshash,"0");
	
	for(k=0;k<5;k++)
	{		
		fprintf(crshash," ");
		fprintf(crshash,"0");
		fprintf(crshash," ");
		
		for(i=0;i<7;i++)
		{
			fprintf(crshash,"$");
		}
		for(i=0;i<7;i++)
		{
			fprintf(crshash,"$");
		}
		for(i=0;i<1;i++)
		{
			fprintf(crshash,"$");
		}
		
	}
	
	fprintf(crshash," ");
	fprintf(crshash,"-");
	fprintf(crshash,"1");
	
	for(i=0;i<5;i++)
	{
		fprintf(crshash,"$");
	}
	fprintf(crshash,"\n");
}

//this function first calculates the number of hash areas in student hash file according to bucket factor and load factor
void Hashing::createstudenthash(void)
{
	int t=0,i=0;
	double sqrtno=0;
	double temp;

	stdhashrecords=(stdrecords*10/7)/5;
	
	t=1;
	while(t)
	{
		temp=stdhashrecords;
		sqrtno=sqrt(temp);
		
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

//this function first calculates the number of hash areas in course hash file according to bucket factor and load factor
void Hashing::createcoursehash(void)
{
	int i=0,t=0;
	double sqrtno=0;
	double temp;
	
	crshashrecords=(crsrecords*10/7)/5;
	
	t=1;
	while(t)
	{
		temp=crshashrecords;
		sqrtno=sqrt(temp);

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

//inserts the student input file records into student hash file areas,if a bucket is full,it inserts the next overflow address location to the end of line in order to be searched in new locations.
void Hashing::insertingstd(void)
{
	int i=0,j=0;
	int result1;
	char tmp,tmp1;
	int pos=0;
	char nextlocstd[8];
	
	overflowstd=stdhashrecords;
	for(i=0;i<stdrecords;i++)
	{
		readstudentrecords();
		pos=0;
		
		result1=fseek(stdhash, hashedlocstd*160,SEEK_SET);
		tmp1=fgetc(stdhash);
		
		while(tmp1=='5')
		{
			fseek(stdhash, hashedlocstd*160+152,SEEK_SET);
			if(fgetc(stdhash)=='-')
			{
				fseek(stdhash, hashedlocstd*160+152,SEEK_SET);
				fprintf(stdhash,"%d",overflowstd);
				hashedlocstd=overflowstd;
				blankstdline();
				overflowstd=overflowstd+1;
			}
			else
			{
				j=0;
				fseek(stdhash, hashedlocstd*160+152,SEEK_SET);
				while((tmp=fgetc(stdhash))!='$')
				{
					nextlocstd[j]=tmp;
					j++;
				}
				nextlocstd[j]=0;
				hashedlocstd=atoi(nextlocstd);
			}
			pos=1;
			
			if(pos)
			{
				result1=fseek(stdhash,hashedlocstd*160,SEEK_SET);
				tmp1=fgetc(stdhash);
			}
		}
		
		if(!result1 && tmp1 >='0' && tmp1<'5')
		{
			fseek(stdhash, hashedlocstd*160,SEEK_SET);
			fputc(tmp1+1,stdhash);
			tmp1=tmp1+1;
			fseek(stdhash, hashedlocstd*160,SEEK_SET);
			
			
			if(tmp1=='1')
			{
				fseek(stdhash, hashedlocstd*160+2,SEEK_SET);
				fputc('1',stdhash);
				fseek(stdhash, hashedlocstd*160+4,SEEK_SET);
				fprintf(stdhash,"%s%s%s%s",stdStudentID,stdStudentName,stdDepartment,stdYear);
			}
			if(tmp1=='2')
			{
				fseek(stdhash, hashedlocstd*160+32,SEEK_SET);
				fputc('1',stdhash);
				fseek(stdhash, hashedlocstd*160+34,SEEK_SET);
				fprintf(stdhash,"%s%s%s%s",stdStudentID,stdStudentName,stdDepartment,stdYear);
			}
			if(tmp1=='3')
			{
				fseek(stdhash, hashedlocstd*160+62,SEEK_SET);
				fputc('1',stdhash);
				fseek(stdhash, hashedlocstd*160+64,SEEK_SET);
				fprintf(stdhash,"%s%s%s%s",stdStudentID,stdStudentName,stdDepartment,stdYear);
			}
			if(tmp1=='4')
			{
				fseek(stdhash, hashedlocstd*160+92,SEEK_SET);
				fputc('1',stdhash);
				fseek(stdhash, hashedlocstd*160+94,SEEK_SET);
				fprintf(stdhash,"%s%s%s%s",stdStudentID,stdStudentName,stdDepartment,stdYear);
			}
			if(tmp1=='5')
			{
				fseek(stdhash, hashedlocstd*160+122,SEEK_SET);
				fputc('1',stdhash);
				fseek(stdhash, hashedlocstd*160+124,SEEK_SET);
				fprintf(stdhash,"%s%s%s%s",stdStudentID,stdStudentName,stdDepartment,stdYear);
			}
		}
	}
}

//inserts the course input file records into course hash file areas,if a bucket is full,it inserts the next overflow address location to the end of line in order to be searched in new locations.
void Hashing::insertingcrs(void)
{
	int i=0,j=0;
	int result2;
	char tmp,tmp2;
	int pos=0;
	char nextloccrs[8];
	
	overflowcrs=crshashrecords;
	for(i=0;i<crsrecords;i++)
	{
		readcourserecords();
		pos=0;
		
		result2=fseek(crshash, hashedloccrs*100,SEEK_SET);
		tmp2=fgetc(crshash);
		
		while(tmp2=='5')
		{
			fseek(crshash, hashedloccrs*100+92,SEEK_SET);
			if(fgetc(crshash)=='-')
			{
				fseek(crshash, hashedloccrs*100+92,SEEK_SET);
				fprintf(crshash,"%d",overflowcrs);
				hashedloccrs=overflowcrs;
				blankcrsline();
				overflowcrs=overflowcrs+1;
			}
			
			else
			{
				j=0;
				fseek(crshash, hashedloccrs*100+92,SEEK_SET);
				while((tmp=fgetc(crshash))!='$')
				{
					nextloccrs[j]=tmp;
					j++;
				}
				nextloccrs[j]=0;
				hashedloccrs=atoi(nextloccrs);
				
			}
			pos=1;
			
			if(pos)
			{
				result2=fseek(crshash,hashedloccrs*100,SEEK_SET);
				tmp2=fgetc(crshash);
			}
		}
		
		if(!result2 && tmp2 >='0' && tmp2<'5')
		{
			fseek(crshash, hashedloccrs*100,SEEK_SET);
			fputc(tmp2+1,crshash);
			tmp2=tmp2+1;
			fseek(crshash, hashedloccrs*100,SEEK_SET);
			
			if(tmp2=='1')
			{
				fseek(crshash, hashedloccrs*100+2,SEEK_SET);
				fputc('1',crshash);
				fseek(crshash, hashedloccrs*100+4,SEEK_SET);
				fprintf(crshash,"%s%s%s",crsStudentID,crsCourseID,crsCourseGrade);
			}
			if(tmp2=='2')
			{
				fseek(crshash, hashedloccrs*100+20,SEEK_SET);
				fputc('1',crshash);
				fseek(crshash, hashedloccrs*100+22,SEEK_SET);
				fprintf(crshash,"%s%s%s",crsStudentID,crsCourseID,crsCourseGrade);
			}
			if(tmp2=='3')
			{
				fseek(crshash, hashedloccrs*100+38,SEEK_SET);
				fputc('1',crshash);
				fseek(crshash, hashedloccrs*100+40,SEEK_SET);
				fprintf(crshash,"%s%s%s",crsStudentID,crsCourseID,crsCourseGrade);
			}
			if(tmp2=='4')
			{
				fseek(crshash, hashedloccrs*100+56,SEEK_SET);
				fputc('1',crshash);
				fseek(crshash, hashedloccrs*100+58,SEEK_SET);
				fprintf(crshash,"%s%s%s",crsStudentID,crsCourseID,crsCourseGrade);
			}
			if(tmp2=='5')
			{
				fseek(crshash, hashedloccrs*100+74,SEEK_SET);
				fputc('1',crshash);
				fseek(crshash, hashedloccrs*100+76,SEEK_SET);
				fprintf(crshash,"%s%s%s",crsStudentID,crsCourseID,crsCourseGrade);
			}
		}
	}
	
}

//menu program thaht communicates with the user,there are options,which can be understand more clearly when the program is run.it conforms with the specifications.
void Hashing::menuprogram(void)
{
	char ch3=0,ch4=0;
	int option=0;
	int printoption;
	int i,j;
	
	while(option !=5)
	{
		cout<<endl;
		cout<<"MENU:"<<endl;
		cout<<"   Select your option:"<<endl;
		cout<<'\t'<<"->Press 1 to Create a hash file for students"<<endl;
		cout<<'\t'<<"->Press 2 to Create a hash file for course registration"<<endl;
		cout<<'\t'<<"->Press 3 to Query the files"<<endl;
		cout<<'\t'<<"->Press 4 to Print the hash file"<<endl;
		cout<<'\t'<<"->Press 5 to Quit\n\nOption?:";
		cin>>option;
		cout<<endl;
		
		if(option==1)
		{
			cout<<"creating a hash file for student file..."<<endl;

			student=fopen(arg[0],"r");
			stdhash=fopen("studenthashfile.txt","wa+");
			
			readstudentfile();
			createstudenthash();
			fillstudenthashfile();
			insertingstd();
			
			fclose(student);
			fclose(stdhash);
		}
		
		if(option==2)
		{
			cout<<"creating a hash file for course registration file..."<<endl;
			
			course=fopen(arg[1],"r");
			crshash=fopen("coursehashfile.txt","wa+");
			
			readcoursefile();
			createcoursehash();
			fillcoursehashfile();
			insertingcrs();
			
			fclose(course);
			fclose(crshash);
		}
		
		if(option==3)
		{
			student=fopen(arg[0],"r");
			course=fopen(arg[1],"r");

			stdhash=fopen("studenthashfile.txt","wa+");
			crshash=fopen("coursehashfile.txt","wa+");
					
			readstudentfile();
			readcoursefile();
			
			createstudenthash();
			createcoursehash();
			
			fillstudenthashfile();
			fillcoursehashfile();
			
			insertingstd();
			insertingcrs();
			
			stdquery=1000000;
			
			while(stdquery > 999999 && stdquery < 10000000)
			{
				cout<<"please enter the studentID:";
				
				cin>>stdquery;
				
				cout<<endl;
				
				cout<<"Student ID"<<'\t'<<"Student Name"<<'\t'<<'\t'<<"Department"<<'\t'<<"Year"<<endl;
				querystd();

				cout<<endl;

				cout<<"Course ID"<<'\t'<<"Grade"<<endl;
				querycrs();
				
				cout<<endl;
			}
			cout<<endl;

			fclose(student);
			fclose(stdhash);
			
			fclose(course);
			fclose(crshash);
			
			cout<<endl;
		}
		
		if(option==4)
		{
			cout<<"Print hash file menu:"<<endl;
			cout<<'\t'<<"->for student hash file press 0"<<endl;
			cout<<'\t'<<"->for course hash file press 1"<<endl;
			cout<<endl;
			cout<<"your choice?:";
			
			cin>>printoption;
			
			stdhash=fopen("studenthashfile.txt","r");
			crshash=fopen("coursehashfile.txt","r");

			if(printoption==0)
			{
				cout<<"printing student hash file on screen ..."<<endl;
				rewind(stdhash);
				ch3=0;
				
				while((ch3=fgetc(stdhash))!=EOF)
				{
					printf("%c",ch3);
					
					cout<<endl;
					
					for(j=0;j<5;j++)
					{
						for(i=0;i<30;i++)
						{
							printf("%c",fgetc(stdhash));
							
						}
						cout<<endl;
					}

					for(j=0;j<8;j++)
						printf("%c",fgetc(stdhash));

					cout<<endl;
					cout<<endl;
							
					ch3=fgetc(stdhash);
				}
			}
			
			if(printoption==1)
			{
				cout<<"printing course hash file on screen ..."<<endl;
				rewind(crshash);
				ch4=0;

				while((ch4=fgetc(crshash))!=EOF)
				{
					printf("%c",ch4);
					
					cout<<endl;
					
					for(j=0;j<5;j++)
					{
						for(i=0;i<18;i++)
						{
							printf("%c",fgetc(crshash));
							
						}
						cout<<endl;
					}
					
					for(j=0;j<8;j++)
						printf("%c",fgetc(crshash));
					
					cout<<endl;
					cout<<endl;
					
					ch4=fgetc(crshash);
				}
				
			}
		}
		
		if(option==5)
		{
			cout<<"OK Exiting..."<<endl;
			cout<<endl;
			return;
		}
		
		cout<<endl;
		cout<<"*************************************************************************************"<<endl;
	}
}

//there are two pointer to pointer so as to store the first and second arguments given with the program,first one i s the student file second one is the course file.
int main(int argc,char *argv[])
{
	Hashing fatih;
	arg[0]=argv[1];
	arg[1]=argv[2];
	
	fatih.menuprogram();
	return 0;
}
