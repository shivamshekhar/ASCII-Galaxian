#include"asciigalaxiantestheader.h"
#include"background.h"
int main()
{
    int del=70,i,j;
    clock_t start,bulletspeed,bgrefresh;;
    SetConsoleTitle("ASCII Galaxian!");
    getch();
    system("cls");
    srand(time(NULL));
    title();
    system("cls");
    printarena();
    getch();
    start=clock();
    bulletspeed=clock();
    bgrefresh=clock();
    srand(time(NULL));
    while(1)
    {
        if(kbhit())
            playermove();
        if(clock()-bgrefresh>140)
        {
            generatestars();
            movestars();
            printstarfield();
            bgrefresh=clock();
        }
        printarena();
        Sleep(del);
        if(clock()-bulletspeed>90)
        {
            collisions();
            updateusergrid();
            updatecpugrid();
            bulletspeed=clock();
        }
        //printscore();
        if(clock()-start>1000)
        {
            cpumove();
            cpufire();
            start=clock();
        }
        if(checkwinlose()!=0)
            break;
    }
    winlose();
    return 0;
}
