#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<stdio.h>
#include<dos.h>
#include<process.h>
union REGS in,out;
int callmouse()
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
void frame()                     // boundary maker
{
	bar(4,4,640,10);
	bar(4,4,10,446);
	bar(4,440,640,446);
	bar(634,4,640,446);
}
int bx=250,by=414,r=1,s=-1;        //global variables used
void ball()                // ball maker and mover
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
	if(bx<18||bx>626) r=-r;
	if(by<18||by>418)  s=-s;
}
void bar(int x,int color)               //bar maker and mover
{
	if(x<61) x=61;
	if (x>583) x=583;
	setfillstyle(SOLID_FILL,BLUE);
	setcolor(BLUE);
	if(color==1)
	{
		setfillstyle(SOLID_FILL,BLACK);
		setcolor(BLACK);
	}
	bar(x-50,420,x+50,430);
}
int n=21;
long int blk[21]={90050,170050,250050,330050,410050,490050,570050,90100,170100,250100,330100,410100,490100,570100,90150,170150,250150,330150,410150,490150,570150};
void checker(int x)                     // check for ball miss
{
	if((bx>x-55&&bx<x-40)) r=-1;
	else if((bx>x+40&&bx<x+55)) r=1;
	if(bx<x-55||bx>x+55) exit(0);
	else
	{
		for (int i = 0 ; i < 6 ; i++ )
		{
			sound ( 144.81 * 3 ) ;
			delay ( 5 ) ;
		}
		nosound() ;
	}
}
void block(long int x,long int y,int z=0)  //bricks maker and destroyer
{
	if(z==1)
	{
		setfillstyle(SOLID_FILL,BLACK);
		setcolor(BLACK) ;
		bar(x-20,y-10,x+20,y+10);
	}
	else
	{
		setfillstyle(SOLID_FILL,WHITE);
		setcolor(WHITE) ;
		bar(x-20,y-10,x+20,y+10);
		setfillstyle(SOLID_FILL,RED);
		setcolor(RED) ;
		bar(x-16,y-8,x+16,y+8);
	}
}
void hit()                      // ball deflection on brick hit checker
{
	for(int i=0;i<n;i++)
	{
		if((by==blk[i]%1000+14)&&s==-1||(by==blk[i]%1000-14)&&s==1)
		{
			if(bx<blk[i]/1000+24&&bx>blk[i]/1000-24)
			{
				block(blk[i]/1000,blk[i]%1000,1);
				blk[i]=600600;
				s=-s;
			}
		}
		if((bx==blk[i]/1000+24)&&r==-1||(bx==blk[i]/1000-24)&&r==1)
		{
			if(by<blk[i]%1000+14&&by>blk[i]%1000-14)
			{
				block(blk[i]/1000,blk[i]%1000,1);
				blk[i]=600600;
				r=-r;
			}
		}
	}
}
void main()
{
	int x,y,cl,a=250,b=420;
	int g=DETECT,m;
	initgraph(&g,&m,"c://tc//bgi");
	cleardevice();
	frame();
	callmouse();
	hidemouse();
	setposi(a,b);
	while(1)                //infinite loop
	{
		ball();
		bar(x,1);
		mouseposi(x,y,cl);
		bar(x,0);
		if(kbhit())       // check if any key pressed
		{
			break;
		}
		if(by>418) checker(x);
		nosound();
		for(int i=0;i<n;i++) block(blk[i]/1000,blk[i]%1000);
		hit();
		delay(2);
	}
}