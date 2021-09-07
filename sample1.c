//c knowledge enhancement project
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int length,bend_no,len,life;
char key;
//screen functions
void screen1();
void screen11a();
void screen11b();
void screen11c();
void screen11d();
void screen111();
//additional functions
void Delay(long double);
void gotoxy(int x, int y);
void GotoXY(int x,int y);
//game operating functions
void Bend();
void Up();
void Down();
void Left();
void Right();
void ExitGame();
int Score();
int Scoreonly();

struct coordinate
{
    int x,y,direction;
};
typedef struct coordinate coordinate;
coordinate head, bend[500],food,body[30];
int main()
{
    char key;life=2;
    screen1();//main menu
    system("cls");
    length=5;
    head.x=25;
    head.y=20;
    head.direction=RIGHT;
    screen11b();//displaying border and food.
    screen11c();//generating food coordinates
    bend[0]=head;
    screen11d();//moving the snake towards food.
    return 0;
}
void screen1()//main menu to start and exit.
	{
	 char choice;
       gotoxy(45,6);
       printf("Welcome to the SNAKE XENZIA");
       gotoxy(52,12);printf("START GAME");
       gotoxy(55,15);printf("EXIT");
       gotoxy(39,20);printf("Press [S/s] to START GAME or [E/e] to EXIT \n");gotoxy(55,22);printf("Choice: ");
       for(;;){
       choice=getch();
       if (choice=='S'|| choice=='s'){
		   system("cls");
		   screen11a();//loading game...
		   break;}
       	else if (choice=='E'||choice=='e'){
		   system("cls");
       	printf("BYE BYE!");
		   	exit(0);}
       	else{
		   gotoxy(44,25);printf("INVALID Choice....Try Again!");gotoxy(63,22);}
	   }
}
void screen11a()//loading game...
{
    int row,col,r,c,q;
    gotoxy(52,14);
    printf("Loading Game...!");
    gotoxy(45,15);
    for(r=1; r<=25; r++)
    {
        for(q=0; q<=100000000; q++); //to display the character slowly
        printf("%c",177);
    }
}
void screen11b()//displaying border and food.
{
    system("cls");
    int i;
    GotoXY(food.x,food.y); //displaying food
    printf("$");
    for(i=11; i<70; i++)
    {
        GotoXY(i,10);
        printf("_");
        GotoXY(i,30);
        printf("_");
    }
    for(i=11; i<31; i++)
    {
        GotoXY(10,i);
        printf("|");
        GotoXY(70,i);
        printf("|");
    }
}
void screen11c()//generating food coordinates
{
    if(head.x==food.x&&head.y==food.y)
    {
        length++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)

            food.y+=11;
    }
    else if(food.x==0)//creating food for the first time
    {
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
}
void screen11d()//moving the snake towards food.
{
    int a,i;
    do
    {
        screen11c();
        fflush(stdin);
        len=0;
        for(i=0; i<30; i++)
        {
            body[i].x=0;
            body[i].y=0;
            if(i==length)
                break;
        }
        Delay(length);
        screen11b();
        if(head.direction==RIGHT)
            Right();
        else if(head.direction==LEFT)
            Left();
        else if(head.direction==DOWN)
            Down();
        else if(head.direction==UP)
            Up();
        ExitGame();
    }while(!kbhit());
    a=getch();
    if(a==27)
    {
        system("cls");
        exit(0);
    }
    key=getch();
    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||(key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))
    {
        bend_no++;
        bend[bend_no]=head;
        head.direction=key;
        if(key==UP)
            head.y--;
        if(key==DOWN)
            head.y++;
        if(key==RIGHT)
            head.x++;
        if(key==LEFT)
            head.x--;
        screen11d();
    }
    else if(key==27)
    {
        system("cls");
        exit(0);
    }
    else
    {
        printf("\a");
        screen11d();
    }
}
int isValidName(char *name){//function to validate name
	int i=0;
	if(!(strlen(name)>=5 && strlen(name)<=50))
	{
		return 0;
	}
	
	while(name[i]){
		if(!(isalpha(name[i]) || name[i]==' ' || name[i]=='.')) 
		{
			return 0;
		}
		i++;
	}
	
	return 1;
}
void screen111()
{
    char plname[51],nplname[51],cha,c;
    int i,j,px;
    FILE *info;
    info=fopen("screen111.txt","a+");
    getch();
    system("cls");
    gotoxy(45,5);
    printf("Your name : ");
    for(;;){
		fflush(stdin);
		gets(plname);
		if(isValidName(plname)){
			break;
		}
		else
		gotoxy(45,6J ); 
		printf("Invalid Name... Try Again: ");
	}
    
    for(j=0; plname[j]!='\0'; j++) //to convert the first letter after space to capital
    {
        nplname[0]=toupper(plname[0]);
        if(plname[j-1]==' ')
        {
            nplname[j]=toupper(plname[j]);
            nplname[j-1]=plname[j-1];
        }
        else nplname[j]=plname[j];
    }
    nplname[j]='\0';
    fprintf(info,"Player Name :%s\n",nplname);
    //for date and time

    time_t mytime;
    mytime = time(NULL);
    fprintf(info,"Played Date:%s",ctime(&mytime));
    fprintf(info,"Score:%d\n",px=Scoreonly());
    for(i=0; i<=50; i++)
        fprintf(info,"%c",'_');
    fprintf(info,"\n");
    fclose(info);
    gotoxy(45,5);
    printf("HIGH SCORE LIST: [Y/N] || Play Again: [P]");
    gotoxy(45,6);printf("Choice: ");
    for(;;){
		cha=getch();
    	if(cha=='y'||cha=='Y')
    	{
        	system("cls");
			info=fopen("screen111.txt","r");
        	do
        	{
            	putchar(c=getc(info));
        	}	
        	while(c!=EOF);
        	break;
    	}
    	else if(cha=='p'||cha=='P')
    	{
    		system("cls");
			main();		
		}
    	else if (cha=='N'||cha=='n'){
			system("cls");
	   		printf("BYE BYE!");
	   		exit(0);}
    	else{
			gotoxy(45,10);printf("INVALID Choice....Try Again!");gotoxy(53,6);   
		}
	}
	fclose(info);
}
void Delay(long double k)
{
    Score();
    long double i;
    for(i=0; i<=(10000000); i++);
}
void Bend()
{
    int i,j,diff;
    for(i=bend_no; i>=0&&len<length; i--)
    {
        if(bend[i].x==bend[i-1].x)
        {
            diff=bend[i].y-bend[i-1].y;
            if(diff<0)
                for(j=1; j<=(-diff); j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y+j;
                    GotoXY(body[len].x,body[len].y);
                    printf("O");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff; j++)
                {
                    /*GotoXY(bend[i].x,(bend[i].y-j));
                    printf("O");*/
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y-j;
                    GotoXY(body[len].x,body[len].y);
                    printf("O");
                    len++;
                    if(len==length)
                        break;
                }
        }
        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1; j<=(-diff)&&len<length; j++)
                {
                    /*GotoXY((bend[i].x+j),bend[i].y);
                    printf("O");*/
                    body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("O");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff&&len<length; j++)
                {
                    /*GotoXY((bend[i].x-j),bend[i].y);
                    printf("O");*/
                    body[len].x=bend[i].x-j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("O");
                    len++;
                    if(len==length)
                        break;
                }
        }
    }
}
void Left()
{
    int i;
    for(i=0; i<=(bend[bend_no].x-head.x)&&len<length; i++)
    {
        GotoXY((head.x+i),head.y);
        {
            if(len==0)
                printf("<");
            else
                printf("O");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit())
        head.x--;

}
void Up()
{
    int i;
    for(i=0; i<=(bend[bend_no].y-head.y)&&len<length; i++)
    {
        GotoXY(head.x,head.y+i);
        {
            if(len==0)
                printf("^");
            else
                printf("O");
        }
        body[len].x=head.x;
        body[len].y=head.y+i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y--;
}
void Down()
{
    int i;
    for(i=0; i<=(head.y-bend[bend_no].y)&&len<length; i++)
    {
        GotoXY(head.x,head.y-i);
        {
            if(len==0)
                printf("v");
            else
                printf("O");
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y++;
}
void Right()
{
    int i;
    for(i=0; i<=(head.x-bend[bend_no].x)&&len<length; i++)
    {
        //GotoXY((head.x-i),head.y);
        body[len].x=head.x-i;
        body[len].y=head.y;
        GotoXY(body[len].x,body[len].y);
        {
            if(len==0)
                printf(">");
            else
                printf("O");
        }
        /*body[len].x=head.x-i;
        body[len].y=head.y;*/
        len++;
    }
    Bend();
    if(!kbhit())
        head.x++;
}
void ExitGame()
{
    int i,check=0;char c1;
    for(i=4; i<length; i++)//starts with 4 because it needs minimum 4 element to touch its own body
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)
        {
            check++;//check's value increases as the coordinates of head is equal to any other body coordinate
        }
        if(i==length||check!=0)
            break;
    }
    if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0)
    {
        life--;
        if(life>=0)
        {
            head.x=25;
            head.y=20;
            bend_no=0;
            head.direction=RIGHT;
            screen11d();
        }
        else
        {
            system("cls");
            gotoxy(40,12);
            printf("All LIVES Exhausted...Better Luck Next Time!!!");
			gotoxy(44,14);
			printf("Press any key to continue..");
            screen111();
            exit(0);
        }
    }
}
int Score()
{
    int score;
    GotoXY(20,8);
    score=length-5;
    printf("SCORE: %d",(length-5));
    score=length-5;
    GotoXY(50,8);
    printf("LIFE: %d",life);
    return score;
}
int Scoreonly()
{
    int score=Score();
    system("cls");
    return score;
}
void gotoxy(int x, int y)
{

    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}
