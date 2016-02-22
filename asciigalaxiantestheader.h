#include<stdio.h>
#include<windows.h>
#include<time.h>
#include"alphabet.h"
#define SPACELENGTH 32
#define SPACEWIDTH 17
CHAR_INFO spacegrid[544];
COORD zerozero={0,0},spacegridsz={32,17};
//int spaceshipmap[2][3]={{0  ,30 ,0  },
//                        {200,219,188},
//                       };
int shippos=2,cpuxleft=7,cpuxright=23,cpuy=4,cpudirn=1/*1: goes right*/ /*0: goes left*/ /*-1: goes down*/;
int healthgrid[SPACEWIDTH][SPACELENGTH]=
                   {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,500,0,500,0,500,0,500,0,500,0,500,0,500,0,500,0,500,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,400,0,400,0,400,0,400,0,400,0,400,0,400,0,400,0,400,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,300,0,300,0,300,0,300,0,300,0,300,0,300,0,300,0,300,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,200,0,200,0,200,0,200,0,200,0,200,0,200,0,200,0,200,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,200,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    };
char enemy[5]="bgyr";
char spacegridmap[SPACEWIDTH][SPACELENGTH + 1]=
                       {"                                ",
                        "       b b b b b b b b b        ",
                        "       g g g g g g g g g        ",
                        "       y y y y y y y y y        ",
                        "       r r r r r r r r r        ",
                        "                                ",
                        "                                ",
                        "                                ",
                        "                                ",
                        "                                ",
                        "                                ",
                        "                                ",
                        "                                ",
                        "                                ",
                        "                                ",
                        "  s                             ",
                        "HEALTH:                         ",
                        };
typedef struct __cpustats
{
    char cpuship;
    int I,J,cpushiphealth;
}_cpustats;
FILE *savefile;
///
void printarena(void);
void fillspaceship(int);
void updateusergrid(void);
void updatecpugrid(void);
void playermove(void);
void cpumove(void);
void cpufire(void);
void printscore(void);
void collisions(void);
void cleargrid(void);
void title(void);
void help(void);
///save state functions
void readsavfile(void);
void writesavfile(void);
void writehighscore(char *name);
void readhighscore(void);
///win lose functions
int checkwinlose(void);
void winlose(void);
/*******************************************************************************************************************************/
///function definitions
void printarena()
{
    SMALL_RECT rect={24,5,56,22};
    int i,j;
    for(i=0;i<17;i++)
    {
        for(j=0;j<32;j++)
        {
            spacegrid[j+32*i].Attributes=15;
            if(spacegridmap[i][j]=='X')
                spacegrid[j+32*i].Char.AsciiChar=219;
            else if(spacegridmap[i][j]=='s')
            {
                fillspaceship(j);
                j++;
            }
            else if(spacegridmap[i][j]=='m')
            {
                spacegrid[j+32*i].Char.AsciiChar=30;
                spacegrid[j+32*i].Attributes=10;
            }
            else if(spacegridmap[i][j]=='l')
            {
                spacegrid[j+32*i].Char.AsciiChar=179;
                spacegrid[j+32*i].Attributes=10;
            }
            else if(spacegridmap[i][j]=='b')
            {
                spacegrid[j+32*i].Char.AsciiChar=210;
                spacegrid[j+32*i].Attributes=9;
            }
            else if(spacegridmap[i][j]=='g')
            {
                spacegrid[j+32*i].Char.AsciiChar=210;
                spacegrid[j+32*i].Attributes=10;
            }
            else if(spacegridmap[i][j]=='y')
            {
                spacegrid[j+32*i].Char.AsciiChar=210;
                spacegrid[j+32*i].Attributes=14;
            }
            else if(spacegridmap[i][j]=='r')
            {
                spacegrid[j+32*i].Char.AsciiChar=210;
                spacegrid[j+32*i].Attributes=12;
            }
            else if(spacegridmap[i][j]=='M')
            {
                spacegrid[j+32*i].Char.AsciiChar=15;
                spacegrid[j+32*i].Attributes=15;
            }
            else if(spacegridmap[i][j]=='L' && i!=16)
            {
                spacegrid[j+32*i].Char.AsciiChar=254;
                spacegrid[j+32*i].Attributes=15;
            }
            else
                spacegrid[j+32*i].Char.AsciiChar=spacegridmap[i][j];
        }
    }
    for(i=7;i<=(healthgrid[15][shippos]/10)+7;i++)
    {
        spacegrid[i+32*16].Char.AsciiChar=219;
        spacegrid[i+32*16].Attributes=10;
    }
    WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE),spacegrid,spacegridsz,zerozero,&rect);
}
//
void fillspaceship(int j)
{
    spacegrid[j + 15*32].Char.AsciiChar=219;
    spacegrid[j + 15*32].Attributes=10;
    spacegrid[j - 1 + 15*32].Char.AsciiChar=200;
    spacegrid[j - 1 + 15*32].Attributes=10;
    spacegrid[j + 1 + 15*32].Char.AsciiChar=188;
    spacegrid[j + 1 + 15*32].Attributes=10;
    spacegrid[j + 14*32].Char.AsciiChar=30;
    spacegrid[j + 14*32].Attributes=10;
}
//
void updatecpugrid()
{
    int i,j;
    for(i=16;i>-1;i--)
    {
        for(j=0;j<32;j++)
        {
            if(spacegridmap[i][j]=='M' && i<15)
            {
                spacegridmap[i][j]=' ';
                spacegridmap[i+1][j]='M';
            }
            if(spacegridmap[i][j]=='M' && i==15)
                spacegridmap[i][j]=' ';
            if(spacegridmap[i][j]=='L' && i<15)
            {
                spacegridmap[i][j]=' ';
                spacegridmap[i+1][j]='L';
            }
            if(spacegridmap[i][j]=='L' && i==15)
                spacegridmap[i][j]=' ';
        }
    }
}
//
void updateusergrid()
{
    int i,j;
    for(i=0;i<17;i++)
        {
            for(j=0;j<32;j++)
            {
                if(spacegridmap[i][j]=='m' && i>1)
                {
                    if(spacegridmap[i-1][j]=='b'||spacegridmap[i-1][j]=='g'||spacegridmap[i-1][j]=='y'||spacegridmap[i-1][j]=='r')
                    {
                        spacegridmap[i][j]=' ';
                        healthgrid[i-1][j]-=50;
                        if(healthgrid[i-1][j]<0)
                            spacegridmap[i-1][j]=' ';
                    }
                    else
                    {
                        spacegridmap[i][j]=' ';
                        spacegridmap[i-1][j]='m';
                    }
                }
                else if(spacegridmap[i][j]=='m' && i==1)
                    spacegridmap[i][j]=' ';
                else if(spacegridmap[i][j]=='l' && i>1)
                {
                    if(spacegridmap[i-1][j]=='b'||spacegridmap[i-1][j]=='g'||spacegridmap[i-1][j]=='y'||spacegridmap[i-1][j]=='r')
                    {
                        spacegridmap[i][j]=' ';
                        healthgrid[i-1][j]-=25;
                        if(healthgrid[i-1][j]<0)
                            spacegridmap[i-1][j]=' ';
                    }
                    else
                    {
                        spacegridmap[i][j]=' ';
                        spacegridmap[i-1][j]='l';
                    }
                }
                else if(spacegridmap[i][j]=='l' && i==1)
                    spacegridmap[i][j]=' ';
            }
        }
}
//
void playermove()
{
    int temp;
    COORD textpos={35,3};
    switch(getch())
            {
            case 'a':
                if(shippos>2)
                {
                    spacegridmap[15][shippos]=' ';
                    temp=healthgrid[15][shippos];
                    healthgrid[15][shippos]=0;
                    shippos--;
                    spacegridmap[15][shippos]='s';
                    healthgrid[15][shippos]=temp;
                }
                break;
            case 'd':
                if(shippos<29)
                {
                    spacegridmap[15][shippos]=' ';
                    temp=healthgrid[15][shippos];
                    healthgrid[15][shippos]=0;
                    shippos++;
                    spacegridmap[15][shippos]='s';
                    healthgrid[15][shippos]=temp;
                }
                break;
            case 'w':
                spacegridmap[14][shippos]='m';
                break;
            case '[':
                spacegridmap[14][shippos-1]='l';
                break;
            case ']':
                spacegridmap[14][shippos+1]='l';
                break;
            case 'o':
                spacegridmap[14][shippos-1]='l';
                spacegridmap[14][shippos+1]='l';
                break;
            case 'l':
                writesavfile();
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
                printf("game saved!");
                //Sleep(3000);
                getch();
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
                printf("           ");
                break;
            }
}
//
void cpumove()
{
    int i,j,k,temp=0;
    switch(cpudirn)
    {
    case 0: //left
        if(cpuxleft>1)
        {
            cpuxleft--;
            cpuxright--;
            for(i=16;i>-1;i--)
            {
                for(j=0;j<32;j++)
                {
                    for(k=0;k<4;k++)
                    {
                        if(spacegridmap[i][j]==enemy[k])
                        {
                            spacegridmap[i][j]=' ';
                            temp=healthgrid[i][j];
                            healthgrid[i][j]=0;
                            spacegridmap[i][j-1]=enemy[k];
                            healthgrid[i][j-1]=temp;
                        }
                    }
                }
            }
        }
        else
            cpudirn=-1;
        break;
    case 1: //right
        if(cpuxright<30)
        {
            cpuxleft++;
            cpuxright++;
            for(i=16;i>-1;i--)
            {
                for(j=31;j>-1;j--)
                {
                    for(k=0;k<4;k++)
                    {
                        if(spacegridmap[i][j]==enemy[k])
                        {
                            spacegridmap[i][j]=' ';
                            temp=healthgrid[i][j];
                            healthgrid[i][j]=0;
                            spacegridmap[i][j+1]=enemy[k];
                            healthgrid[i][j+1]=temp;
                        }
                    }
                }
            }
        }
        else
            cpudirn=-1;
        break;
    case -1: //down
        if(cpuxleft<2)
        {
            cpuxleft++;
            cpuxright++;
            cpuy++;
            cpudirn=1;
            for(i=16;i>-1;i--)
            {
                for(j=0;j<32;j++)
                {
                    for(k=0;k<4;k++)
                    {
                        if(spacegridmap[i][j]==enemy[k])
                        {
                            spacegridmap[i][j]=' ';
                            temp=healthgrid[i][j];
                            healthgrid[i][j]=0;
                            spacegridmap[i+1][j+1]=enemy[k];
                            healthgrid[i+1][j+1]=temp;
                        }
                    }
                }
            }
        }
        if(cpuxright>29)
        {
            cpuxright--;
            cpuxleft--;
            cpuy++;
            cpudirn=0;
            for(i=16;i>-1;i--)
            {
                for(j=0;j<32;j++)
                {
                    for(k=0;k<4;k++)
                    {
                        if(spacegridmap[i][j]==enemy[k])
                        {
                            spacegridmap[i][j]=' ';
                            temp=healthgrid[i][j];
                            healthgrid[i][j]=0;
                            spacegridmap[i+1][j-1]=enemy[k];
                            healthgrid[i+1][j-1]=temp;
                        }
                    }
                }
            }
        }
        break;
    }
}
void cpufire()
{
    int i,j,k;
    for(i=16;i>-1;i--)
    {
        for(j=0;j<32;j++)
        {
            for(k=0;k<4;k++)
            {
                if(spacegridmap[i][j]==enemy[k] && spacegridmap[i+1][j]==' ')
                {
                    if(rand()%3==0)
                    {
                        if(rand()%3==0)
                            spacegridmap[i+1][j]='M';
                        else
                            spacegridmap[i+1][j]='L';
                    }
                }
            }
        }
    }
}
//
void printscore()
{
    COORD textpos={60,15};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
    printf("              ");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
    printf("Health: %d",healthgrid[15][shippos]);
}
//
void collisions()
{
    int i,j;
    for(i=16;i>-1;i--)
    {
        for(j=0;j<32;j++)
        {
            /*switch(spacegridmap[i][j])
            {
            case 'M':
                if(spacegridmap[i+1][j]=='m')
                {
                    spacegridmap[i][j]=' ';
                    spacegridmap[i+1][j]==' ';
                }
                else if(spacegridmap[i+1][j]=='l')
                {
                    spacegridmap[i][j]=' ';
                    spacegridmap[i+1][j]='M';
                }
                else if(spacegridmap[i+2][j]=='s')
                {
                    spacegridmap[i][j]=' ';
                    healthgrid[15][shippos]-=40;
                }
                else if(spacegridmap[i+1][j+1]=='s' || spacegridmap[i+1][j-1]=='s')
                {
                    spacegridmap[i][j]=' ';
                    healthgrid[15][shippos]-=20;
                }
                else if(i==15)
                    spacegridmap[i][j]=' ';
                else
                {
                    spacegridmap[i][j]=' ';
                    spacegridmap[i+1][j]='M';
                }
                break;
            case 'L':
                if(spacegridmap[i+1][j]=='m')
                {
                    spacegridmap[i][j]='m';
                    spacegridmap[i+1][j]==' ';
                }
                else if(spacegridmap[i+1][j]=='l')
                {
                    spacegridmap[i][j]=' ';
                    spacegridmap[i+1][j]=' ';
                }
                else if(spacegridmap[i+2][j]=='s')
                {
                    spacegridmap[i][j]=' ';
                    healthgrid[15][shippos]-=20;
                }
                else if(spacegridmap[i+1][j+1]=='s' || spacegridmap[i+1][j-1]=='s')
                {
                    spacegridmap[i][j]=' ';
                    healthgrid[15][shippos]-=10;
                }
                else if(i==15)
                    spacegridmap[i][j]=' ';
                else
                {
                    spacegridmap[i][j]=' ';
                    spacegridmap[i+1][j]='M';
                }
                break;
            }*/
            if(spacegridmap[i][j]=='M' && spacegridmap[i+1][j]=='m')
            {
                spacegridmap[i][j]=' ';
                spacegridmap[i+1][j]=' ';
            }
            else if(spacegridmap[i][j]=='M' && spacegridmap[i+1][j]=='l')
            {
                spacegridmap[i][j]=' ';
                spacegridmap[i+1][j]='M';
            }
            else if(spacegridmap[i][j]=='L' && spacegridmap[i+1][j]=='m')
            {
                spacegridmap[i][j]='m';
                spacegridmap[i+1][j]=' ';
            }
            else if(spacegridmap[i][j]=='L' && spacegridmap[i+1][j]=='l')
            {
                spacegridmap[i][j]=' ';
                spacegridmap[i+1][j]=' ';
            }
            else if(spacegridmap[i][j]=='M' && spacegridmap[i+2][j]=='s')
            {
                spacegridmap[i][j]=' ';
                healthgrid[15][shippos]-=20;
            }
            else if(spacegridmap[i][j]=='M' && (spacegridmap[i+1][j+1]=='s' || spacegridmap[i+1][j-1]=='s'))
            {
                spacegridmap[i][j]=' ';
                healthgrid[15][shippos]-=10;
            }
            else if(spacegridmap[i][j]=='L' && spacegridmap[i+2][j]=='s')
            {
                spacegridmap[i][j]=' ';
                healthgrid[15][shippos]-=10;
            }
            else if(spacegridmap[i][j]=='L' && (spacegridmap[i+1][j+1]=='s' || spacegridmap[i+1][j-1]=='s'))
            {
                spacegridmap[i][j]=' ';
                healthgrid[15][shippos]-=5;
            }
        }
    }
}
//
void cleargrid()
{
  int i,j;
  for(i=1;i<16;i++)
  {
      for(j=1;j<31;j++)
      {
          spacegridmap[i][j]=' ';
          healthgrid[i][j]=0;
      }
  }
}
///win or lose functions
//
int checkwinlose()
{
    int i,j,noofenemies=0;
    //losing conditions
    for(i=0;i<31;i++)
    {
        if(spacegridmap[14][i]=='r'||spacegridmap[14][i]=='y'||spacegridmap[14][i]=='g'||spacegridmap[14][i]=='b')
            return -1;
    }
    if(healthgrid[15][shippos]<=0)
        return -1;
    //winning conditions
    for(i=0;i<16;i++)
    {
        for(j=0;j<32;j++)
        {
            if(spacegridmap[i][j]=='r'||spacegridmap[i][j]=='y'||spacegridmap[i][j]=='g'||spacegridmap[i][j]=='b')
                noofenemies++;
        }
    }
    if(noofenemies==0)
        return 1;
    return 0;
}
//
 void winlose()
 {
     COORD textpos={35,3};
     char name[20];
     switch(checkwinlose())
    {
    case 1:
        collisions();
        updateusergrid();
        updatecpugrid();
        printarena();
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
        printf("You Win!");
        Sleep(3000);
        textpos.Y++;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
        printf("Enter your name: ");
        scanf("%s",&name);
        writehighscore(name);
        getch();
        system("asciigalaxiantestfile.exe");
        break;
    case -1:
        collisions();
        updateusergrid();
        updatecpugrid();
        printarena();
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
        printf("You Lose!");
        Sleep(10000);
        getch();
        system("asciigalaxiantestfile.exe");
        break;
    }
}
//
void title()
{
    int spaceshipmap[2][3]={{0  ,30 ,0  },
                            {200,219,188},
                            };
    CHAR_INFO spaceship[6];
    SMALL_RECT spaceshiprect={20,5,23,7};
    COORD spaceshipsz={3,2},textpos={36,16};
    int i,j;
    char title[15]="ascii galaxian";
    SMALL_RECT titlerect={25,3,30,8};
    for(i=0;i<2;i++)
    {
        for(j=0;j<3;j++)
        {
            spaceship[j+3*i].Char.AsciiChar=spaceshipmap[i][j];
            spaceship[j+3*i].Attributes=10;
        }
    }
    for(i=0;title[i]!='\0';i++)
    {
        if(title[i]!=' ')
        {
            fillchar(title[i],219,rand()%7+9);
            printchar(title[i],titlerect);
            titlerect.Left+=6;
            titlerect.Right+=6;
        }
        else
        {
            titlerect.Top+=6;
            titlerect.Bottom+=6;
            titlerect.Left=16;
            titlerect.Right=21;
        }
    }
    WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE),spaceship,spaceshipsz,zerozero,&spaceshiprect);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
    printf("1. Start");
    textpos.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
    printf("2. Resume");
    textpos.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
    printf("3. High Scores");
    textpos.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
    printf("4. Help");
    textpos.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),textpos);
    switch(getch())
    {
    case '1':
        break;
    case '2':
        readsavfile();
        break;
    case '3':
        readhighscore();
        break;
    case '4':
        help();
        break;
    }
}
//
void help()
{
    system("cls");
}
///Save state functions
//
void readsavfile()
{
    int i,_uhealth,noofships;
    _cpustats _ships[50];
    savefile=fopen("asciigalaxian.sav","rb");
    if(savefile==NULL)
    {
        printf("\ncouldn't load save file.\n");
        fclose(savefile);
        system("pause");
    }
    else
    {
        cleargrid();
        fread(&shippos,sizeof(int),1,savefile);
        fread(&_uhealth,sizeof(int),1,savefile);
        fread(&cpuxleft,sizeof(int),1,savefile);
        fread(&cpuxright,sizeof(int),1,savefile);
        fread(&cpuy,sizeof(int),1,savefile);
        fread(&cpudirn,sizeof(int),1,savefile);
        fread(&noofships,sizeof(int),1,savefile);
        fread(&_ships,sizeof(_ships),1,savefile);
        spacegridmap[15][shippos]='s';
        healthgrid[15][shippos]=_uhealth;
        for(i=0;i<noofships;i++)
        {
            spacegridmap[_ships[i].I][_ships[i].J]=_ships[i].cpuship;
            healthgrid[_ships[i].I][_ships[i].J]=_ships[i].cpushiphealth;
        }
        fclose(savefile);
    }
}
//
void writesavfile()
{
    int _uhealth,i,j,k=0,noofships=0;
    _cpustats _ships[50];
    savefile=fopen("asciigalaxian.sav","wb");
    fwrite(&shippos,sizeof(int),1,savefile);
    _uhealth=healthgrid[15][shippos];
    fwrite(&_uhealth,sizeof(int),1,savefile);
    fwrite(&cpuxleft,sizeof(int),1,savefile);
    fwrite(&cpuxright,sizeof(int),1,savefile);
    fwrite(&cpuy,sizeof(int),1,savefile);
    fwrite(&cpudirn,sizeof(int),1,savefile);
    for(i=0;i<16;i++)
    {
        for(j=0;j<32;j++)
        {
            if(spacegridmap[i][j]=='b'||spacegridmap[i][j]=='g'||spacegridmap[i][j]=='y'||spacegridmap[i][j]=='r')
                noofships++;
        }
    }
    fwrite(&noofships,sizeof(int),1,savefile);
    for(i=0;i<16;i++)
    {
        for(j=0;j<32;j++)
        {
            if(spacegridmap[i][j]=='b'||spacegridmap[i][j]=='g'||spacegridmap[i][j]=='y'||spacegridmap[i][j]=='r')
            {
                _ships[k].cpuship=spacegridmap[i][j];
                _ships[k].cpushiphealth=healthgrid[i][j];
                _ships[k].I=i;
                _ships[k].J=j;
                k++;
            }
        }
    }
    fwrite(&_ships,sizeof(_ships),1,savefile);
    fclose(savefile);
}
//
void writehighscore(char *name)
{

}
//
void readhighscore()
{

}
