#include<stdio.h>
#include<windows.h>
#include<time.h>
CHAR_INFO spacegrid[544];
COORD zerozero={0,0},spacegridsz={32,17};
//int spaceshipmap[2][3]={{0  ,30 ,0  },
  //                      {200,219,188},
    //                   };
int shippos=2,cpuxleft=7,cpuxright=23,cpuy=4,cpudirn=1/*1: goes right*/ /*0: goes left*/ /*-1: goes down*/;
int healthgrid[17][32]=
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
                    {0,0,1000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    };
char enemy[5]="bgyr";
char spacegridmap[17][33]=
                       {"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
                        "X      b b b b b b b b b       X",
                        "X      g g g g g g g g g       X",
                        "X      y y y y y y y y y       X",
                        "X      r r r r r r r r r       X",
                        "X                              X",
                        "X                              X",
                        "X                              X",
                        "X                              X",
                        "X                              X",
                        "X                              X",
                        "X                              X",
                        "X                              X",
                        "X                              X",
                        "X                              X",
                        "X s                            X",
                        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
                        };
///
void printarena(void);
void fillspaceship(int);
void updategrid(void);
void playermove(void);
void cpumove(void);
///
int main()
{
    int del=70,i,j;
    clock_t start;
    SetConsoleTitle("ASCII Galaxian!");
    printarena();
    getch();
    start=clock();
    while(1)
    {
        if(kbhit())
            playermove();
        printarena();
        Sleep(del);
        updategrid();
        if(clock()-start>1000)
        {
            cpumove();
            start=clock();
        }
    }
    return 0;
}
///
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
            else
                spacegrid[j+32*i].Char.AsciiChar=spacegridmap[i][j];
        }
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
void updategrid()
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
                if(spacegridmap[i][j]=='m' && i==1)
                    spacegridmap[i][j]=' ';
                if(spacegridmap[i][j]=='l' && i>1)
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
                if(spacegridmap[i][j]=='l' && i==1)
                    spacegridmap[i][j]=' ';
            }
        }
}
//
void playermove()
{
    int temp;
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
