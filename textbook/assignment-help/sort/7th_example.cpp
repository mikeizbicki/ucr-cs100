#include <iostream>
#include <algorithm>
#include <string.h>
#define MAXLINE 10
using namespace std; 

char* convert(char a[])//remain only a~z and 0~9
{
	for(int k=0;k<strlen(a);k++)
	{
		if((a[k]>='A'&&a[k]<='Z'))
		{
			a[k]=a[k]+'a'-'A';
		}
	}
	char *q=&a[0];
	return q;
}

bool compare(const char *p1,const char *p2)//sort alphabetically
{
	char q1[MAXLINE];
	char q2[MAXLINE];
	strcpy(q1,p1);
	strcpy(q2,p2);
	
	char *q3;
	q3=convert(q1);

	char *q4;
	q4=convert(q2);

	if (strcmp(q3,q4)<0) return true;
	else return false;
}


int main() 
{
	char array[][10] = { "abc", "pab", "slm", "dfp", "ktw", "b", "bac","DFq","Z"};
	int elements = 9; 
	char *p[10];
	for(int i=0;i<9;i++)
	{
		p[i]=array[i];
	}
	sort(p, p+elements,compare);
	for (int i = 0; i < elements; ++i) 
		cout << p[i] << ' ';
	cout<<endl;
	return 0;
}
