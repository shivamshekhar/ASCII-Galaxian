#include<stdio.h>
#include<windows.h>
int main()
{
    int bossmap[5][5]=
                {
                 { 92,  0, 30,  0, 47},
                 {126,  4,197,  4,126},
                 {126, 17,197, 16,126},
                 {126,  4,197,  4,126},
                 { 47,111,  0,111, 92}
                };
    int i,j;
    CHAR_INFO boss[25];
    COORD zerozero={0,0},bosssz={5,5};
    SMALL_RECT bossrect={5,5,10,10};
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            boss[j+5*i].Char.AsciiChar=bossmap[i][j];
            boss[j+5*i].Attributes=12;
        }
    }
    WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE),boss,bosssz,zerozero,&bossrect);
    getch();
    return 0;
}
