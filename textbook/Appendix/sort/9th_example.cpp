#include <iostream>
#include <algorithm>
using namespace std;
struct data
{
	int a;
	int b;
	int c;
}; 
bool cmp(data x,data y)
{
	if(x.a!=y.a)
	{
		return x.a<y.a;
	}
	else if(x.b!=y.b)
	{
		return x.b>y.b;
	}
	else
	{
		return x.c>y.c;
	}
}
void output(struct data tst)
{
	cout<<"a="<<tst.a<<" b="<<tst.b<<" c="<<tst.c<<endl;
}
int main()
{
	struct data tst[4];
	tst[0]={3,4,2};
	tst[1]={2,4,5};
	tst[2]={2,5,5};
	tst[3]={2,5,6};
	cout<<"Before sort:"<<endl;
	for(int i=0;i<4;i++)
		output(tst[i]);
	sort(tst,tst+4,cmp);
	cout<<"After sort:"<<endl;
	for(int i=0;i<4;i++)
		output(tst[i]);
	return 0;
}
