#include<iostream>
using namespace std;
#define f first
#define s second

class Pixel
{
	int iloc,jloc;
	char ch;
public:
	Pixel(){}

	Pixel(int a,int b,char c)
	{
		iloc = a;
		jloc = b;
		ch = c;
	}

	Pixel(const Pixel &p2)
	{
		iloc = p2.iloc;
		jloc = p2.jloc;
		ch = p2.ch;
	}

	~Pixel()
	{}

	void change(char c)
	{
		ch = c;
	}

	int getx()
	{
		return iloc;
	}

	int gety()
	{
		return jloc;
	}

	char getc()
	{
		return ch;
	}
};

class Image
{
	int r,c;
	Pixel **arr;

public:
	Image(int w1, int h1)
	{
		r=w1;
		c=h1;
		arr = new Pixel*[r];
		for (int i = 0; i < r; ++i)
		{
			arr[i] = new Pixel[c];
			for(int j=0;j<c;j++)
			{
				arr[i][j] = Pixel(i,j,'o');
			}
		}
	}

	Image(const Image &im)
	{
		r = im.r;
		c = im.c;
		arr = im.arr;
	}

	~Image()
	{
		delete arr;
	}

	void transform(Pixel p, unsigned int w)
	{
		int x = p.getx();
		int y = p.gety();
		if(x>=0 && x<r && y>=0 && y<c)
			arr[x][y].change('c');
		for(int i=1;i<=w;i++)
		{
			if(x>=0 && x<r)
			{
				if(y-i>=0 && y-i<c)
					arr[x][y-i].change('*');
				if(y+i>=0 && y+i<c)
					arr[x][y+i].change('*');
			}
		}
		for(int i=1;i<=w;i++)
		{
			if(x-i>=0 && x-i<r)
			{
				if(y>=0 && y<c)
					arr[x-i][y].change('*');
				for(int j=1;j<=w-i;j++)
				{
					if(y-j>=0 && y-j<c)
						arr[x-i][y-j].change('*');
					if(y+j>=0 && y+j<c)
						arr[x-i][y+j].change('*');
				}
			}
			if(x+i>=0 && x+i<r)
			{
				if(y>=0 && y<c)
					arr[x+i][y].change('*');
				for(int j=1;j<=w-i;j++)
				{
					if(y-j>=0 && y-j<c)
						arr[x+i][y-j].change('*');
					if(y+j<c && y+j<c)
						arr[x+i][y+j].change('*');
				}
			}
		}
	}

	void print()
	{
		for(int i=0;i<r;i++)
		{
			for(int j=0;j<c;j++)
				cout<<arr[i][j].getc();
			cout<<endl;
		}
	}
};

int main()
{
	int r,c,i=0;
	cin>>r>>c;
	Image im(r,c);
	int x,y;
	unsigned int w;
	while(1)
	{
		cin>>x;
		if(x == -1)
			break;
		cin>>y>>w;
		Pixel p(x,y,'o');
		im.transform(p,w);
	}
	im.print();
	return 0;
}