#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
int front()                      // start page
{
	char ch;
	settextstyle(1,HORIZ_DIR,8);
	outtextxy(100,40,"GUESS_GAME");
	settextstyle(2,HORIZ_DIR,7);
	outtextxy(150,200,"press enter to play");
	outtextxy(150,240,"press escape to exit");
	ch=getch();
	if(ch==13) return 1;
	else exit(0);
}
void intro()                       // give intro about game
{
	cout<<"you have to guess a number which is randomly selected between 1 to 100";
	cout<<endl;
	cout<<"you will have 5 tries to guess it and win"<<endl;
}
void decide(int x,int y)   // check guess is greater/lesser than x
{
	if(x>y)
	cout<<"number is greater than "<<y<<endl;
	else if(x<y)
	cout<<"number is lesser than "<<y<<endl;
}
int guess(int x)                 //check the input
{
	int i=0,y=101;
	while(y!=x)
	{
		cout<<endl;
		cout<<"guess the number";
		cin>>y;
		decide(x,y);
		i++;
		if(i==5)
		{
			cleardevice();
			cout<<"you failed to guess .....!"<<endl;
			cout<<"number was "<<x;
			getch();
			return 1;
		}
	}
	cleardevice();
	settextstyle(3,HORIZ_DIR,5);
	outtextxy(70,100,"CONGRATZ....YOU WON...!");
	getch();
	return 1;
}
void main()                       // main body of game
{
	int gd=DETECT,gm,x,i;
	initgraph(&gd,&gm,"c://tc//bgi");
	if(front())
	{
		cleardevice();
		intro();
		srand(time(0));
		x=rand()%99+1;             // random number creation
		guess(x);
	}
}