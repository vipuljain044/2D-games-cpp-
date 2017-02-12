#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<dos.h>
void game_end(int x,int y)     // end if snake hit bountary
{
	if(x<12||x>632||y<12||y>438)
	{
		cleardevice();
		outtextxy(250,250,"GAME END......!");
		delay(1000);
		exit(0);
	}
}
void frame()                     // boundary maker
{
	bar(4,4,640,10);
	bar(4,4,10,446);
	bar(4,440,640,446);
	bar(634,4,640,446);
}
void hit(int i[10000],int j[10000],int size,int n,int x,int y)  // if bite
{
	for(int u=n-2;u>=n-100-20*size;u--)
	{
		if(x==i[u]&&y==j[u])
		{
			cleardevice();
			outtextxy(250,250,"shake bite itself");
			delay(1000);
			exit(0);
		}
	}
}
void dot(int a,int b,int x)                    // food maker
{
	if(x)
	{
		setfillstyle(SOLID_FILL,BLACK);
		setcolor(BLACK);
	}
	pieslice(a,b,0,360,3);
	setfillstyle(SOLID_FILL,WHITE);
	setcolor(WHITE);
}
int evolution(int x,int y,int a0,int a1)  // func to increment snake
{
	if(abs(x-a0)<4&&abs(y-a1)<4)
	{
		return 1;
	}
	else
	return 0;
}
void main()
{
	int gd=DETECT,gm,x,y,sx=250,sy=250,size=0,r=0,s=0,ai[10000],aj[10000];
	int n=0,a0,a1,flag=0,start=0;
	char ch;
	initgraph(&gd,&gm,"c://tc//bgi");
	cleardevice();
	frame();
	srand(time(0));
	a0=rand()%500+20;
	a1=rand()%400+20;
	while(1)                //infinite loop
	{
		dot(a0,a1,0);
		game_end(sx,sy);              //snake boundary hit checker
		pieslice(sx+r,sy+s,0,360,2);        //snake constuctor
		if(kbhit())                // check key press
		{
			start=1;
			ch=getch();
			if(ch==72&&s!=1) //move up
			{
				s=-1;r=0;
			}
			if(ch==75&&r!=1) //more left
			{
				r=-1;s=0;
			}
			if(ch==77&&r!=-1)//move right
			{
				r=1;s=0;
			}
			if(ch==80&&s!=-1)//move down
			{
				s=1;r=0;
			}
			if(ch==29) //exit
			{
				exit(0);
			}
			if(ch==13) //pause
			{
				r=0;s=0;
			}
		}
		if(start==1)
		sx+=r;sy+=s;                       //snake motion
		ai[n]=sx;aj[n]=sy;	     //snake motion recoder
		n++;
		if(n>100)                           //initial size snake
		{
			flag=1;
		}
		if(flag)                                 //snake size decider
		{
			setcolor(BLACK);
			pieslice(ai[n-100-20*size],aj[n-100-20*size],0,360,3);
			setcolor(WHITE);
			if(r!=0||s!=0)
			hit(ai,aj,size,n,sx,sy);
		}
		if(evolution(sx,sy,a0,a1))
		{
			size++;
			dot(a0,a1,1);
			a0=rand()%500+20;     //random position
			a1=rand()%400+20;     //of dot
			dot(a0,a1,0);
		}
		delay(5);
	}
}