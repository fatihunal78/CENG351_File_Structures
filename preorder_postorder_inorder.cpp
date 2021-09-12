#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>

#define INPUTROW 1000
#define INPUTCOLUMN 100

using namespace std;

FILE *input;
char ch;
char inputarray[INPUTROW][INPUTCOLUMN];
char indexarray1[INPUTROW][INPUTCOLUMN];
char indexarray2[INPUTROW][INPUTCOLUMN];
char indexarray3[INPUTROW][INPUTCOLUMN];
int dedectinput[INPUTROW];
int ilkharf[26];
int p,q,r;
int i;

class node
{
	public:
		char *name;
		char *data1;
		char *data2;
		char *data3;
		struct node *left;
		struct node *right;
};


class functions
{
	public:
		void insert(class node * np,int p,int i);
		void preorder(class node *parent);
		void postorder(class node *parent);
		void inorder(class node *parent);
		void dedector(void);
		char converter(int q);
		void reading(void);
		int convert(char x);
		void findfirst(void);
};


void functions::insert(struct node * np,int p,int i)
{
	class node * npt;
	
	if(!strncmp(inputarray[ilkharf[i]],inputarray[p],1) && strcmp(np->name,inputarray[p])==0)
	{
		if(indexarray1[p] && np->data1[0]!='<')
			np->data1=indexarray1[p];
		else 
			if(indexarray1[p] && np->data1[0]=='<')
				np->data1=strcat(np->data1,indexarray1[p]);
		
		if(indexarray2[p] && np->data2[0]!='>')
			np->data2=indexarray2[p];
		else
			if(indexarray2[p] && np->data2[0]=='>')
				np->data2=strcat(np->data2,indexarray2[p]);
		
		if(indexarray3[p])
			np->data3=strcat(np->data3,indexarray3[p]);
				
		return;
	}
	

	if(!strncmp(inputarray[ilkharf[i]],inputarray[p],1) && strcmp(np->name,inputarray[p])>0) 
		{
			if(np->left!=0)
			{
				insert(np->left,p,i);
			}
			else
			{
				npt=(class node *) malloc(sizeof(class node));
				npt->name=inputarray[p];
				
				npt->data1=indexarray1[p];
				npt->data2=indexarray2[p];
				npt->data3=indexarray3[p];
				
				npt->left=npt->right=NULL;
				np->left=npt;
				return;
			}
				
			
		}
		
		if(!strncmp(inputarray[ilkharf[i]],inputarray[p],1) && strcmp(np->name,inputarray[p])<0) 
		{

			if(np->right!=0 )
				insert(np->right,p,i);
			else
			{
				npt=(class node *) malloc(sizeof(class node));
				npt->name=inputarray[p];
				
				 npt->data1=indexarray1[p];
				 npt->data2=indexarray2[p];
				 npt->data3=indexarray3[p];
				
				npt->left=npt->right=NULL;
				np->right=npt;
				return;
			}
		}

}

void functions::preorder(class node *parent)
{

	if(parent)
	{
		cout<<parent->name<< parent->data1<<parent->data2<<parent->data3<<endl;
		preorder(parent->left);
		preorder(parent->right);
	}

}

void functions::inorder(class node *parent)
{
	char *p1;
	char *p2;
	char *p3;
	char *p4;
	char *tmp;
	char *tmp2;
	char *tmp3;
	
	int i,j,k,t;
	int t1,t2;
	int x,y;
	int z1,z2;
	
	if(parent)
	{
		inorder(parent->left);
				
		p1=(char *) malloc(sizeof(parent->name));
		p1=parent->name;
		p2=(char *) malloc(sizeof(parent->data1));
		p2=parent->data1;
		p3=(char *) malloc(sizeof(parent->data2));
		p3=parent->data2;
		p4=(char *) malloc(sizeof(parent->data3));
		p4=parent->data3;
		
		k=0;
		for(i=0;i<(int)strlen(p1);i++)
		{
			if(p1[i]=='!')
				k++;
		}
		
		if(k==0)
			cout<<p1<<": ";
		
		tmp=(char *) malloc(sizeof(p1));
		
		if(k)
		{
			while(k)
			{
				tmp=strchr(p1,33);
				p1=tmp+1;
				k--;
				cout<<"\t";
			}
			cout<<p1<<": ";
		}
		
		i=0;
		j=0;
		z1=0;
		z2=0;
		t=0;
		
		p2[strlen(p2)]=0;
		p3[strlen(p3)]=0;

		while(p2[i]!=0 || p3[j]!=0)
		{
			tmp2=(char *) malloc(sizeof(p1));
			tmp3=(char *) malloc(sizeof(p1));
			
			x=0;
			y=0;
			
			if(i==0)
				i++;
			if(j==0)
				j++;

			t1=0;
			while(p2[i]=='<')
			{
				i++;
			}
			
			while(p2[i]!='<' && p2[i]!=0)
			{
				tmp2[t1]=p2[i];
				t1++;
				i++;
				x++;
			}
			p2=p2+i;
			
			t2=0;
			while(p3[j]=='>')
			{
				j++;
			}
			while(p3[j]!='>' && p3[j]!=0)
			{
				tmp3[t2]=p3[j];
				t2++;
				j++;
				y++;
			}
			p3=p3+j;
			
			if(t1 && t2)
			{
				tmp2[x]=0;
				tmp3[y]=0;

				if(strcmp(tmp2,tmp3))
				{
					if(z1 || z2)
						cout<<", ";
					cout<<tmp2<<"-"<<tmp3;
					z1++;
				}
								
			
				if(!strcmp(tmp2,tmp3))
				{
					if(z1 || z2)
						cout<<", ";
					cout<<tmp3;
					z2++;
				}
			}
			i=0;
			j=0;

			free(tmp2);
			free(tmp3);
		}
		
		if(parent->data1[0]=='<' && parent->data2[0]=='>')
		{
			t=1;
			if(p4[0]=='*')
			{
				cout<<", ";
				while(p4[t]!=0)
				{
					if(p4[t]!='*')
						cout<<p4[t];
					if(p4[t]=='*')
						cout<<", ";
					t++;
				}
				
			}
		}	
	
		if(parent->data1[0]=='<' && parent->data2[0]=='>' && t>=1)
			cout<<endl;
			

		
		if(p4[0]=='*' && !t)
		{
			i=1;
			while(p4[i]!=0)
			{
				if(p4[i]!='*')
					cout<<p4[i];
				if(p4[i]=='*')
					cout<<", ";
				i++;
			}
			cout<<endl;
		}
		inorder(parent->right);
	}	
}

void functions::postorder(class node *parent)
{
	
	if(parent)
	{
		
		postorder(parent->left);
		postorder(parent->right);
		cout<<parent->name<< parent->data1<<parent->data2<<parent->data3<<endl;
	}
	
}

void functions::dedector(void)
{
	int i;
	for(i=0;i<r;i++)
	{
		
		if(inputarray[i][0]=='a' || inputarray[i][0]=='A') dedectinput[i]=0;
		if(inputarray[i][0]=='b' || inputarray[i][0]=='B') dedectinput[i]=1;
		if(inputarray[i][0]=='c' || inputarray[i][0]=='C') dedectinput[i]=2;
		if(inputarray[i][0]=='d' || inputarray[i][0]=='D') dedectinput[i]=3;
		if(inputarray[i][0]=='e' || inputarray[i][0]=='E') dedectinput[i]=4;
		if(inputarray[i][0]=='f' || inputarray[i][0]=='F') dedectinput[i]=5;
		if(inputarray[i][0]=='g' || inputarray[i][0]=='G') dedectinput[i]=6;
		if(inputarray[i][0]=='h' || inputarray[i][0]=='H') dedectinput[i]=7;
		if(inputarray[i][0]=='i' || inputarray[i][0]=='I') dedectinput[i]=8;
		if(inputarray[i][0]=='j' || inputarray[i][0]=='J') dedectinput[i]=9;
		if(inputarray[i][0]=='k' || inputarray[i][0]=='K') dedectinput[i]=10;
		if(inputarray[i][0]=='l' || inputarray[i][0]=='L') dedectinput[i]=11;
		if(inputarray[i][0]=='m' || inputarray[i][0]=='M') dedectinput[i]=12;
		if(inputarray[i][0]=='n' || inputarray[i][0]=='N') dedectinput[i]=13;
		if(inputarray[i][0]=='o' || inputarray[i][0]=='O') dedectinput[i]=14;
		if(inputarray[i][0]=='p' || inputarray[i][0]=='P') dedectinput[i]=15;
		if(inputarray[i][0]=='q' || inputarray[i][0]=='Q') dedectinput[i]=16;
		if(inputarray[i][0]=='r' || inputarray[i][0]=='R') dedectinput[i]=17;
		if(inputarray[i][0]=='s' || inputarray[i][0]=='S') dedectinput[i]=18;
		if(inputarray[i][0]=='t' || inputarray[i][0]=='T') dedectinput[i]=19;
		if(inputarray[i][0]=='u' || inputarray[i][0]=='U') dedectinput[i]=20;
		if(inputarray[i][0]=='v' || inputarray[i][0]=='V') dedectinput[i]=21;
		if(inputarray[i][0]=='w' || inputarray[i][0]=='W') dedectinput[i]=22;
		if(inputarray[i][0]=='x' || inputarray[i][0]=='X') dedectinput[i]=23;
		if(inputarray[i][0]=='y' || inputarray[i][0]=='Y') dedectinput[i]=24;
		if(inputarray[i][0]=='z' || inputarray[i][0]=='Z') dedectinput[i]=25;
	}
	return;

}

char functions::converter(int q)
{
	if(q==0) return 'a';
	if(q==1) return 'b';
	if(q==2) return 'c';
	if(q==3) return 'd';
	if(q==4) return 'e';
	if(q==5) return 'f';
	if(q==6) return 'g';
	if(q==7) return 'h';
	if(q==8) return 'i';
	if(q==9) return 'j';
	if(q==10) return 'k';
	if(q==11) return 'l';
	if(q==12) return 'm';
	if(q==13) return 'n';
	if(q==14) return 'o';
	if(q==15) return 'p';
	if(q==16) return 'q';
	if(q==17) return 'r';
	if(q==18) return 's';
	if(q==19) return 't';
	if(q==20) return 'u';
	if(q==21) return 'v';
	if(q==22) return 'w';
	if(q==23) return 'x';
	if(q==24) return 'y';
	if(q==25) return 'z';
	else return 0;
}

int functions::convert(char x)
{
	if(x=='a' || x=='A')	return 0;
	if(x=='b' || x=='B')	return 1;
	if(x=='c' || x=='C')	return 2;
	if(x=='d' || x=='D')	return 3;
	if(x=='e' || x=='E')	return 4;
	if(x=='f' || x=='F')	return 5;
	if(x=='g' || x=='G')	return 6;
	if(x=='h' || x=='H')	return 7;
	if(x=='i' || x=='I')	return 8;
	if(x=='j' || x=='J')	return 9;
	if(x=='k' || x=='K')	return 10;
	if(x=='l' || x=='L')	return 11;
	if(x=='m' || x=='M')	return 12;
	if(x=='n' || x=='N')	return 13;
	if(x=='o' || x=='O')	return 14;
	if(x=='p' || x=='P')	return 15;
	if(x=='q' || x=='Q')	return 16;
	if(x=='r' || x=='R')	return 17;
	if(x=='s' || x=='S')	return 18;
	if(x=='t' || x=='T')	return 19;
	if(x=='u' || x=='U')	return 20;
	if(x=='v' || x=='V')	return 21;
	if(x=='w' || x=='W')	return 22;
	if(x=='x' || x=='X')	return 23;
	if(x=='y' || x=='Y')	return 24;
	if(x=='z' || x=='Z')	return 25;
	else return -1;
}

void functions::findfirst(void)
{
	int i,j,k=0;
	for(i=0;i<26;i++)
	{
		k=0;
		for(j=0;j<r;j++)
			{
				if(k==0)
				{		
					if(dedectinput[j]==i)
					{
						ilkharf[i]=j;
						k++;
					} else 
						ilkharf[i]=-1;
				
				}
			}
	}

}

void functions::reading(void)
{

	input= fopen("input.txt","r");
	
        while(ch!=EOF && ch!='\n')
	{
		while((ch=fgetc(input)) !='{') {}
		q=0;          
	
		while((ch=fgetc(input)) !='}' && ch!='<' && ch!='>')
		{
			if(q==0)
			{
				inputarray[p][0]=toupper(ch);
				q++;
			}
			else 
			{
				inputarray[p][q]=ch;
				q++;
			}
		}
		
		if(ch=='<')
		{
			indexarray1[p][0]='<';
		}
		
		if(ch=='>')
		{
			indexarray2[p][0]='>';
		}
		
		if(ch=='}')
		{
			indexarray3[p][0]='*';
		}
		
		q=0;

		while((ch=fgetc(input)) !='{') {}
		
		ch=fgetc(input);
		do
		{
			if(indexarray1[p][0]=='<')
			{
				indexarray1[p][1+q]=ch;
				ch=fgetc(input);
				q++;
			}
			
			if(indexarray2[p][0]=='>')
			{
				indexarray2[p][1+q]=ch;
				ch=fgetc(input);
				q++;
			}
			
			if(indexarray3[p][0]=='*')
			{
				indexarray3[p][1+q]=ch;
				ch=fgetc(input);
				q++;			
			}
			
		}
		while(ch!='}');
		
		while((ch=fgetc(input)) !='\n') {}
		
		if(ch=='\n')
		{
			p++;
		}
		ch=fgetc(input);
		r++;
	}
}

int main (int argc,char *argv[])
{
	node *tp1[26];
	functions fatih; 
	
	fatih.reading();
	fatih.dedector();
	fatih.findfirst();

	
for(i=0;i<26;i++)
{
	tp1[i]=(class node *) malloc(sizeof(class node));
	
	if(ilkharf[i]!=-1)
	{	
	p=ilkharf[i];
	tp1[i]->name=inputarray[p];
	
	tp1[i]->data1=indexarray1[p];
	tp1[i]->data2=indexarray2[p];
	tp1[i]->data3=indexarray3[p];
	
	tp1[i]->left=tp1[i]->right=NULL;
	
	for(p=ilkharf[i]+1;p<r;p++)
	{
		fatih.insert(tp1[i],p,i);
	}
	}
}

if(argc==1)
{
	for(i=0;i<26;i++)
	{
		if(tp1[i]->name)
		{
			fatih.inorder(tp1[i]);
		}
	}
}

if(argc!=1 && argv[argc-1]!=NULL)
{
	if(tp1[fatih.convert(argv[2][0])]->name==NULL)
		cout<<"NO enrties"<<endl;
	else 
		if(argv[1][0]=='-' && argv[1][1]=='o')
			fatih.inorder(tp1[fatih.convert(argv[2][0])]);
		else 
			cout<<"unexpected command"<<endl;

}

return 0;
}


