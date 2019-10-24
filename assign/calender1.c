#include<stdio.h>
struct time
{
	int yr,mon,date,day,hr,min,sec,dif;
	char ch;
};

void year(struct time *t)
{
	if(t->ch=='+')
	{
		for(int i=0;i<(t->dif);i++)
		{
			t->day=(t->day+365)%7;
			t->yr++;
		}
	}
	else
	{
		for(int i=0;i<t->dif;i++)
		{
			t->day=(t->day-365)%7;
			t->yr--;
		}
	}
}

void month(struct time *t)
{
	int m=t->dif%12;
	t->dif=t->dif/12;
	year(t);
	int a[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	t->mon--;
	if(t->ch=='+')
	{
		for(int i=0;i<m;i++)
		{
			t->day=(t->day+a[t->mon])%7;
			t->mon++;
			if(t->mon==12)
			{
				t->mon=0;
				t->yr++;
			}
		}
	}
	else
	{
		for(int i=0;i<m;i++)
		{
			t->mon--;
			if(t->mon==-1)
			{
				t->mon=11;
				t->yr--;
			}
			t->day=(t->day-a[t->mon]);
		}
		t->day=t->day%7;
		if(t->day<0)
			t->day+=7;
	}
	t->mon++;
}

void days(struct time *t)
{
	int d=t->dif%365;
	t->dif=t->dif/365;
	year(t);
	int a[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	if(t->ch=='+')
	{
		for(int i=0;i<d;i++)
		{
			t->day=(t->day +1)%7;
			t->date++;
			if((t->date)>a[(t->mon)-1])
			{
				t->date=1;
				t->mon++;
				if(t->mon==13)
				{
					t->mon=1;
					t->yr++;
				}
			}
		}
	}
	else
	{
		for(int i=0;i<d;i++)
		{
			t->day--;
			if(t->day==-1)
				t->day=6;
			t->date--;
			if(t->date==0)
			{
				t->mon--;
				if(t->mon==0)
				{
					t->mon=12;
					t->yr--;
				}
				t->date=a[(t->mon)-1];
			}
		}
	}
}

void hour(struct time *t)
{
	int h=t->dif%24;
	t->dif=t->dif/24;
	days(t);
	if(t->ch=='+')
	{
		for(int i=0;i<h;i++)
		{
			t->hr++;
			if((t->hr)==24)
			{
				t->hr=0;
				t->dif=1;
				days(t);
			}
		}
	}
	else
	{
		for(int i=0;i<h;i++)
		{
			t->hr--;
			if((t->hr)==-1)
			{
				t->hr=23;
				t->dif=1;
				days(t);
			}
		}
	}
}

void minute(struct time *t)
{
	int m=t->dif%60;
	t->dif=t->dif/60;
	hour(t);
	if(t->ch=='+')
	{
		for(int i=0;i<m;i++)
		{
			t->min++;
			if(t->min==60)
			{
				t->min=0;
				t->dif=1;
				hour(t);
			}
		}
	}
	else
	{
		for(int i=0;i<m;i++)
		{
			t->min--;
			if(t->min==-1)
			{
				t->min=59;
				t->dif=1;
				hour(t);
			}
		}
	}
}

int main()
{
	struct time t;
	t.yr=0;t.mon=0;t.date=0;t.day=0;t.hr=0;t.min=0;t.sec=0;t.dif=0;	char s[100];
	scanf("%[^\n]%*c",s);
	int i=0;
	for(int j=i;j<i+4;j++)
	{
		t.yr=(t.yr*10)+(s[j]-'0');
	}
	i+=5;
	for(int j=i;j<i+2;j++)
	{
		t.mon=(t.mon*10)+(s[j]-'0');
	}
	i+=3;
	for(int j=i;j<i+2;j++)
	{
		t.date=(t.date*10)+(s[j]-'0');
	}
	i+=3;
	if(s[i]=='M')
		t.day=0;
	else if(s[i]=='T')
	{
		if(s[i+1]=='u')
			t.day=1;
		else
			t.day=3;
	}
	else if(s[i]=='W')
		t.day=2;
	else if(s[i]=='F')
		t.day=4;
	else
	{
		if(s[i+1]=='a')
			t.day=5;
		else
			t.day=6;
	}
	while(s[i]!='/')
		i++;
	i++;
	for(int j=i;j<i+2;j++)
	{
		t.hr=(t.hr*10)+(s[j]-'0');
	}
	i+=3;
	for(int j=i;j<i+2;j++)
	{
		t.min=(t.min*10)+(s[j]-'0');
	}
	i+=3;
	for(int j=i;j<i+2;j++)
	{
		t.sec=(t.sec*10)+(s[j]-'0');
	}
	while(s[i]!=' ')
		i++;
	i++;
	t.ch=s[i];
	i+=2;
	while(s[i]!=' ')
	{
		t.dif=(t.dif*10)+(s[i]-'0');
		i++;
	}
	if(s[i+1]=='M')
	{
		if(s[i+2]=='N')
			minute(&t);
		else
			month(&t);
	}
	else if(s[i+1]=='H')
		hour(&t);
	else if(s[i+1]=='D')
		days(&t);
	else
		year(&t);
	printf("%d-%2d-%d/",t.yr,t.mon,t.date);
	if(t.day==0)
		printf("Monday/");
	else if(t.day==1)
		printf("Tuesday/");
	else if(t.day==2)
		printf("Wednesday/");
	else if(t.day==3)
		printf("Thursday/");
	else if(t.day==4)
		printf("Friday/");
	else if(t.day==5)
		printf("Saturday/");
	else if(t.day==6)
		printf("Sunday/");
	printf("%d:%d:%d/IST\n",t.hr,t.min,t.sec);
}
