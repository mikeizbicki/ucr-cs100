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
	if(x.a!=y.a) return x.a<x.y;
	if(x.b!=y.b) return x.b>y.b;
	if(x.c!=y.c) return x.c>y.c;
}
int main()
{
	.....
	sort(array,array+n,cmp);
	return 0;
}

