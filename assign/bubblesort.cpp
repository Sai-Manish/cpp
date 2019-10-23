#include<bits/stdc++.h>
using namespace std;

void bubblesort(int n, int &arr)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(arr[j]>arr[j+1])
			{
				int t=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=t;
			}
		}
	}
}

int main()
{
	int n;
	cin>>n;
	int a[n];
	for (int i = 0; i < n; ++i)
	{
		/* code */cin>>a[i];
	}
	bubblesort(n,&a);
	for (int i = 0; i < n; ++i)
	{
		/* code */cout<<a[i]<<' ';
	}
	cout<<endl;
}