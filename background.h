#include<windows.h>
char _starfieldmap[22][79]=
                                {"                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              ",
                                 "                                                                              "
                                };


//
void generatestars(void);
void movestars(void);
void printstarfield(void);
//
void generatestars()
{
    int i;
    for(i=0;i<78;i++)
        if(_starfieldmap[0][i]==' ' && rand()%40==1)
        {
            switch(rand()%2)
            {case 1:
            _starfieldmap[0][i]='.';
            break;
            case 0:
            _starfieldmap[0][i]='*';
            break;}
        }

}
//
void movestars()
{
    int i,j;
    for(i=21;i>-1;i--)
    {
        for(j=0;j<78;j++)
        {
            if((_starfieldmap[i][j]=='.' || _starfieldmap[i][j]=='*') && i<21)
            {
                _starfieldmap[i+1][j]=_starfieldmap[i][j];
                _starfieldmap[i][j]=' ';
            }
            if((_starfieldmap[i][j]=='.' || _starfieldmap[i][j]=='*')&& i==21)
                _starfieldmap[i][j]=' ';
        }
    }
}
//
void printstarfield(void)
{
    int i,j;
    CHAR_INFO _starfield[1716];
    SMALL_RECT _starfieldrect={1,2,79,24};
    COORD zerozero={0,0},_starfieldsz={78,22};
    for(i=0;i<22;i++)
    {
        for(j=0;j<78;j++)
        {
            _starfield[j+78*i].Char.AsciiChar=_starfieldmap[i][j];
            _starfield[j+78*i].Attributes=15;
        }
    }
    WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE),_starfield,_starfieldsz,zerozero,&_starfieldrect);
}
