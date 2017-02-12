#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
int blue=0,red=0,yy=200;
union REGS in,out;
int setmouse()
{
	in.x.ax=1;
	int86(51,&in,&out);
	return 1;
}
int hidemouse()
{
	in.x.ax=2;
	int86(51,&in,&out);
	return 1;
}
void mouseposi(int &xpos,int &ypos,int &click)
{
	in.x.ax=3;
	int86(51,&in,&out);
	click=out.x.bx;
	xpos=out.x.cx;
	ypos=out.x.dx;
}
void setposi(int &xpos,int &ypos)// set an initial position of mouse
{
	in.x.ax=4;
	in.x.cx=xpos;
	in.x.dx=ypos;
	int86(51,&in,&out);
}
void vertical_limit(int &xpos,int &ypos)
{
	in.x.ax=8;
	in.x.cx=xpos;
	in.x.dx=ypos;
	int86(51,&in,&out);
}
void frame()                     // boundary maker
{
	bar(14,10,620,16);
	bar(14,10,20,446);
	bar(14,440,620,446);
	bar(614,10,620,446);
}
void red_bar()          // playing bar
{
	setfillstyle(SOLID_FILL,RED);
	setcolor(RED);
	bar(600,yy,606,yy+100);
}
int bx=250,by=250,r=2,s=2;
void ball()                             //ball controller
{
	setcolor(BLACK) ;
	setfillstyle(SOLID_FILL,BLACK);
	circle(bx,by,4);
	pieslice(bx,by,0,360,4);
	bx+=r;by+=s;
	setfillstyle(SOLID_FILL,WHITE);
	setcolor(WHITE);
	circle(bx,by,4);
	pieslice(bx,by,0,360,4);
	if(bx<34||bx>600) r=-r;
	if(by<24||by>432)  s=-s;
}
int br=150;
void bar_blue()                             // computer bar
{
	setfillstyle(SOLID_FILL,BLACK);
	setcolor(BLACK) ;
	bar(26,br,32,br+100);
	setfillstyle(SOLID_FILL,BLUE);
	setcolor(WHITE);
	if ((br+50>by)&&br>30) br-=4;
	if ((br+50<by)&&br<330) br+=4;
	bar(26,br,32,br+100);
}
void score_bar1(int x)                  //blue score counter
{
	if(bx==600)
	{
		if(by>yy&&by<yy+100)
		{
			r=-abs(r);
		}
		else if(r==abs(r)) blue++;
	}
}
void score_bar2()                        // red score counter
{
	if(bx==32)
	{
		if(by>br&&by<br+100)
		{
			r=abs(r);
		}
		else if(r==abs(r))red++;
	}
}
void display_score()                   // score display
{
	for(int i=1;i<=blue;i++)
	{
		setcolor(WHITE);
		setfillstyle(SOLID_FILL,BLUE);
		pieslice(6,20+20*i,0,360,5);
	}
	for(i=1;i<=red;i++)
	{
		setcolor(WHITE);
		setfillstyle(SOLID_FILL,RED);
		pieslice(630,20+20*i,0,360,5);
	}
}
void main()                           // main body of game
{
	int gd=DETECT,gm,x=150,xx,cl,a=600,b=200;
	initgraph(&gd,&gm,"c://tc//bgi");
	char ch;
	frame();
	bar_blue();
	setmouse();
	hidemouse();
	setposi(a,b);
	while(1)
	{
		ball();
		setfillstyle(SOLID_FILL,BLACK);
		setcolor(BLACK);
		bar(600,yy,606,yy+100);
		vertical_limit(20,335);
		mouseposi(xx,yy,cl);
		red_bar();
		if(kbhit())  break;                    //check if key pressed
		if(bx<120) bar_blue();
		score_bar1(x);
		score_bar2();
		display_score();
		delay(.5);
	}
}