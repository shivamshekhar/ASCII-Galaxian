#include"alphabet.h"
#include"background.h"
void printTitle(int);
void printsignature(void);
//
int main()
{
    int i,j,a;
    srand(time(NULL));
    SetConsoleTitle("ASCII Galaxian!");
    printTitle(1);
    printsignature();
    while(!kbhit())
    {
        generatestars();
        movestars();
        printstarfield();
        printTitle(0);
        Sleep(60);
    }
    system("asciigalaxiantestfile.exe");
    return 0;
}
//
void printTitle(int isdelay)
{
    int i;
    char title[15]="ascii galaxian";
    SMALL_RECT titlerect={25,6,30,11};
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
        if(isdelay==1)
            Sleep(300);
    }
}
//
void printsignature()
{
    COORD signpos={2,24};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),signpos);
    printf("Written By: Shivam Shekhar");
}
