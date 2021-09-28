#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
int dotsEaten=0;
typedef struct
{
	int arr[1000];
	int i,j;
} Queue;
void enqueue(Queue *q,int a)
{
	q->arr[q->j++] = a;
}
int isEmpty(Queue *q)
{
	return q->i >=  q->j;
}
int dequeue(Queue *q)
{
	return q->arr[q->i++];
}
int isOk (char map[100][100],int column,int row,int side,int position)											//checking if this move doesen't encounter an obstacle
{
	int i=1,j=0,pacman=position;
	while(pacman>column)
	{
		pacman-=column;
		i++;
	}
	j=pacman;
	if (j==0)
	{
		j=column;
		i--;
	}
	if ((side==8&&i==1)||(side==8&&map[i-2][j-1]=='#'))
		return 0;
	if ((side==2&&i==row)||side==2&&map[i][j-1]=='#')
		return 0;
	if ((side==4&&j==1)||(side==4&&map[i-1][j-2]=='#'))
		return 0;
	if ((side==6&&j==column)||(side==6&&map[i-1][j]=='#'))
		return 0;
	return 1;
}																												//End of checking move
int oneMove(char map[100][100],int position,int column,int row,int dotsPosition[100],int dotsAtFirst)			//computer choosing a side in which to get to the nearest dot
{
	int side=0,visit[1000]={0},parents[1000] = {0},newPosition=0,currentPosition=0;
	Queue q;
	q.i = 0;
	q.j = 0;
	enqueue(&q,position);
	visit[position]=1;
	
	while (!isEmpty(&q))
	{
		currentPosition = dequeue(&q);
		int flag = 0;
		for (int i = 0;i < dotsAtFirst;i++)
			if (dotsPosition[i] == currentPosition&&dotsPosition[i]>0)
				flag = 1;
		if (flag)
		{
			while(parents[currentPosition] != position)
				currentPosition = parents[currentPosition];
			break;
		}
		for (int i = 0;i < 4;i++)
		{
			if (!isOk(map,column,row,(i + 1) * 2,currentPosition))
				continue;
			if (i==0)
				newPosition=currentPosition+column;
			if (i==1)
				newPosition=currentPosition-1;
			if (i==2)
				newPosition=currentPosition+1;
			if (i==3)
				newPosition=currentPosition-column;
			if (!visit[newPosition])
			{
				visit[newPosition] = 1;
				enqueue(&q,newPosition);
				parents[newPosition] = currentPosition;
			}
		}
	}
	if (currentPosition==position-column)
		side=8;
	if (currentPosition==position+column)
		side=2;
	if (currentPosition==position+1)
		side=6;
	if (currentPosition==position-1)
		side=4;
	
	Sleep(200);
	return side;
}																												//end of computer choosing a side
 void victory()																									//sound of victory
 {
	int x;
	Sleep(200);
	Beep(523,500);
	Sleep(50);
	Beep(659,400);
	Sleep(50);
	Beep(440,400);
	Sleep(50);
	Beep(494,400);
	Sleep(50);
	Beep(523,750);
	Sleep(400);
}																												//End of sound
int move (char map[100][100],int side,int position,int column,int row,int *dots,int *lifes)						//moving as 8 is up, 6 is right, 2 is down, 4 is left
{
	int i=1,j=0,pacman=position;
	while(pacman>column)
	{
		pacman-=column;
		i++;
	}
	j=pacman;
	if (j==0)
	{
		j=column;
		i--;
	}
	if (side==8)
	{
		if (i!=1&&map[i-2][j-1]!='#')
		{
			if (map[i-2][j-1]=='*')
			{
				(*dots)--;
				dotsEaten++;
				
			}	
			map[i-2][j-1]='0';
			map[i-1][j-1]='1';
			position-=column;
		}
		else
		{
			*lifes=*lifes-1;
			Beep(800,200);
		}
	}
	if (side==6)
	{
		if (j!=column&&map[i-1][j]!='#')
		{
			if (map[i-1][j]=='*')
			{
				(*dots)--;
				dotsEaten++;
			}
			map[i-1][j]='0';
			map[i-1][j-1]='1';
			position++;
		}
		else
		{
			*lifes=*lifes-1;
			Beep(800,200);
		}
	}
	if (side==2)
	{
		if (i!=row&&map[i][j-1]!='#')
		{
			if (map[i][j-1]=='*')
			{
				*dots=*dots-1;
				dotsEaten++;
			}
			map[i][j-1]='0';
			map[i-1][j-1]='1';
			position+=column;
		}
		else
		{
			*lifes=*lifes-1;
			Beep(800,200);
		}

	}
	if (side==4)
	{
		if (j!=1&&map[i-1][j-2]!='#')
		{
			if (map[i-1][j-2]=='*')
			{
				*dots=*dots-1;
				dotsEaten++;
				
			}
			map[i-1][j-2]='0';
			map[i-1][j-1]='1';
			position--;	
		}
		else
		{
			*lifes=*lifes-1;
			Beep(800,200);
		}
	}
	return position;
}																										//End of moving
void border (char map[100][100],int column,int row)														//making borders & printing map
{
	for (int i=0;i<column+2;i++)
	{
		printf("\033[1;34m");
		putchar(178);
		printf("\033[0m");
	}
	putchar('\n');
	for(int i=0;i<row;i++)
	{
		printf("\033[1;34m");
		putchar(178);
		printf("\033[0m");
		for (int j=0;j<column;j++)
		{
			if (map[i][j]=='1')
				putchar(' ');
			else 
				if (map[i][j]=='0')
				{
					printf("\033[01;33m");
					putchar(2);
					printf("\033[0m");
				}
				else
					if (map[i][j]=='*')
					{
						printf("\033[1;31m");
						putchar(3);
						printf("\033[0m");
					}
					else
					{
						printf("\033[1;34m");
						putchar(178);
						printf("\033[0m");
					}
		}
		printf("\033[1;34m");
		putchar(178);
		printf("\033[0m");
		putchar('\n');
 	}
 	for (int i=0;i<column+2;i++)
	{
		printf("\033[1;34m");
		putchar(178);
		printf("\033[0m");
	}
	putchar('\n');
}																										//End of making borders & printing map
int main ()
{
	while(1)
	{
		system("cls");
		printf("  Enter The LEVEL Number For Playing:\n\t\t\t\t\t\t\t\t\t\t\tExit : 0\n");				//opening the file
		int testcaseNum=1,row=0,column=0,checker=0,checkBlank=0,position=0,sizeOfColumn=0,side=1,dots=0,lifes=3,ch=0,ch2=0,cheatOn=0,dotsAtFirst=0,dotsPosition[100]={0},indexForDots=0,pDot=0;
		char Adress[100]={'\0'},map[100][100]={'\0'},tmp[1000]={'\0'};
		FILE *test;
		scanf("%d",&testcaseNum);
		if (testcaseNum==0)
		{
			printf("Exiting...\n");
			sleep(2);
			return 0;
		}
		if (testcaseNum<10)
			sprintf(Adress,"testcases\\testcase0%d.txt",testcaseNum);
		else
			sprintf(Adress,"testcases\\testcase%d.txt",testcaseNum);
		test=fopen(Adress,"r");
		while(test==NULL)
		{
			system("cls");
			printf("  LEVEL Number %d Is Not Available!\n\n\n  Please Enter Another LEVEL Number:\n\t\t\t\t\t\t\t\t\t\t\tExit : 0\n",testcaseNum);
			scanf("%d",&testcaseNum);
			if (testcaseNum==0)
			{
				printf("Exiting...\n");
				sleep(2);
				return 0;
			}
			Adress[0]='\0';
			if (testcaseNum<10)
				sprintf(Adress,"testcases\\testcase0%d.txt",testcaseNum);
			else
				sprintf(Adress,"testcases\\testcase%d.txt",testcaseNum);
			test=fopen(Adress,"r");
		}																								    //End of opening file
		system("cls");
		while (feof(test)==0)																				//reading file
		{
			fgets(tmp,1001,test);
			for (int i=0;tmp[i]!='\n'&&tmp!='\0'&&row==0;i++)
			{
				if (tmp[i]=='0'||tmp[i]=='1'||tmp[i]=='*'||tmp[i]=='#')	
				{
					sizeOfColumn++;
				}
			}
			column=0;
			checkBlank=0;
			for (checker=0;tmp[checker]!='\n'&&tmp[checker]!='\0';checker++)
			{ 
				if (tmp[checker]=='0'||tmp[checker]=='1'||tmp[checker]=='*'||tmp[checker]=='#')	
				{
					map[row][column++]=tmp[checker];
					checkBlank++;
					if (tmp[checker]=='*')
					{
						dots++;
						dotsPosition[indexForDots++]=row*sizeOfColumn+column;
					}
					if (tmp[checker]=='0')
					{
						position=row*sizeOfColumn+column;
					}
				}
			}
			if (checkBlank)
				row++;
		}																									//End of reading file
		fclose(test);
		dotsAtFirst=dots;
		while(1)																							//showing and playing
		{
			dotsEaten=0;
			side=1;
			border(map,column,row);
			printf("\nLifes : ");
			for(int i=0;i<lifes;i++) 
			{
				printf("\033[1;31m");
				printf("%c ",3);
				printf("\033[0m");
			}
			printf("\nHearts left to Achieve:\t%d",dots);
			if (cheatOn)
				printf("\n\n<<Cheat Activated>>\n\nExit : 0\n");
			else
			{
				printf("\nExit : 0\n\n\n\n\n\n\n\n\nCheat : c\n");
			}
			if (!cheatOn)
			{
				ch = getch();
				ch2 = 0;
				if (ch == 0xE0) 																		 		//if a scroll key was pressed
				{
					ch2 = getch();
					switch(ch2)
					{
					case 72: side=8; break;
					case 80: side=2; break;
					case 75: side=4; break;
					case 77: side=6; break;
					default:;
					};
				}
				else
				{
					if (ch=='c')
					{
						cheatOn=1;
					}
					else
						side=ch-'0';
				}
			}
			else
			{
				side=oneMove(map,position,column,row,dotsPosition,dotsAtFirst);
			}
			if(side==0)
			{
				printf("Exiting...\n");
				sleep(2);
				break;
			}
			pDot=dots;
			position=move(map,side,position,column,row,&dots,&lifes);
			if(pDot!=dots)																						//checks if in this position there was a dot and changes the dots position
				for(int i=0;i<dotsAtFirst;i++)
					if(dotsPosition[i] == position)
						dotsPosition[i]=-1;
			Beep(1000, 70);
			if (dotsEaten==1&&lifes<3)
			{
				lifes++;
				dotsEaten=0;
			}
			if (lifes==0)
			{
				system("cls");
				printf("\a");
				border(map,column,row);
				printf("\nLifes : ");
				for(int i=0;i<lifes;i++) 
				{
					printf("\033[1;31m");
					printf("%c ",3);
					printf("\033[0m");
				}
				printf("\nHearts left to Achieve:\t%d\n",dots);
				printf("\033[1;31m");
				printf("\t\t\t\t\t**********\n");
				printf("\t\t\t\t\t*YOU LOST*\n");
				printf("\t\t\t\t\t**********\n");
				printf("\033[0m");
				printf("Exiting...\n");
				sleep(3);
				break;
			}
			if(dots==0)
			{
				system("cls");
				border(map,column,row);
				printf("\nLifes : ");
				for(int i=0;i<lifes;i++) 
				{
					printf("\033[1;31m");
					printf("%c ",3);
					printf("\033[0m");
				}
				printf("\nHearts left to Achieve:\t%d\n",dots);
				printf("\033[1;32m");
				printf("\t\t\t\t\t*********\n");
				printf("\t\t\t\t\t*YOU WON*\n");
				printf("\t\t\t\t\t*********\n");
				printf("\033[0m");
				printf("Exiting...\n");
				victory();
				
				break;
			}
			system("cls");
		}																									//End of show and play
	}
}
