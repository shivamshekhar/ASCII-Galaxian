FILE *savefile;
//
void readsavfile(void);
void writesavfile(void);
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
