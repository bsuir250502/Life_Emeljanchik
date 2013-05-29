#include <stdlib.h>
#include <stdio.h>

#define LINE_NUMBER 5
#define COLUMN_NUMBER 5
#define MAX_LENGTH 3

void print_result (int ms[LINE_NUMBER][COLUMN_NUMBER])
{
    int i1, i2;
    for (i1=0; i1<LINE_NUMBER; i1++) {
        puts("");
        for (i2=0; i2<COLUMN_NUMBER; i2++)
            printf ("%2d", ms[i1][i2]);
    }
}

int life(int ms[LINE_NUMBER][COLUMN_NUMBER], int y, int x)
{
    int i=0;
    x--;
    if (x<0) x+=COLUMN_NUMBER;
    if (ms[y][x]==1) i++;
    y--;
    if (y<0) y+=LINE_NUMBER;
    if (ms[y][x]==1) i++;
    x++;
    if (x>=COLUMN_NUMBER) x-=COLUMN_NUMBER;
    if (ms[y][x]==1) i++;
    x++;
    if (x>=COLUMN_NUMBER) x-=COLUMN_NUMBER;
    if (ms[y][x]==1) i++;
    y++;
    if (y>=LINE_NUMBER) y-=LINE_NUMBER;
    if (ms[y][x]==1) i++;    
    y++;
    if (y>=LINE_NUMBER) y-=LINE_NUMBER;
    if (ms[y][x]==1) i++;
    x--;
    if (x<0) x+=COLUMN_NUMBER;
    if (ms[y][x]==1) i++;
    x--;
    if (x<0) x+=COLUMN_NUMBER;
    if (ms[y][x]==1) i++;
    y--;
    if (y<0) y+=LINE_NUMBER;
    x++;
    if (x>=COLUMN_NUMBER) x-=COLUMN_NUMBER;
    if (ms[y][x]==0)
        if (i==3) return 1;
        else return 0;
    else
        if (i==2 || i==3)
            return 1;
        else return 0;
}

int next_generation (int ms[LINE_NUMBER][COLUMN_NUMBER])
{
    int i1, i2, next_generation_ms [LINE_NUMBER][COLUMN_NUMBER];
    for (i1=0; i1<LINE_NUMBER; i1++)
        for (i2=0; i2<COLUMN_NUMBER; i2++)
            next_generation_ms[i1][i2]=life (ms, i1, i2);
    for (i1=0; i1<LINE_NUMBER; i1++)
        for (i2=0; i2<COLUMN_NUMBER; i2++)
            ms[i1][i2]=next_generation_ms[i1][i2];
    print_result (next_generation_ms);
    puts ("");
    return ms[LINE_NUMBER][COLUMN_NUMBER];
}

int main ()
{
    FILE *f;
    int generetion, i1, i2, ms[LINE_NUMBER][COLUMN_NUMBER], mas[COLUMN_NUMBER*LINE_NUMBER]={0, 0, 0, 0, 0,
                                                                                            0, 0, 1, 0, 0,
                                                                                            0, 0, 0, 1, 0,
                                                                                            0, 1, 1, 1, 0,
                                                                                            0, 0, 0, 0, 0};
    char char_n[MAX_LENGTH];
    if (!(f=fopen ("file", "w+b")))
        return 0;
    fwrite (mas, sizeof(int), COLUMN_NUMBER*LINE_NUMBER, f);
    rewind (f);
    printf ("Enter number of generations: ");
    while (1) {
        fgets (char_n, MAX_LENGTH, stdin);
        generetion=strtol (char_n, NULL, 10);
        if (generetion>0)
            break;
    }
    for (i1=0; i1<LINE_NUMBER; i1++)
        fread (ms[i1], sizeof(int), COLUMN_NUMBER, f);
    for (i1=0; i1<LINE_NUMBER; i1++)
        for (i2=0; i2<COLUMN_NUMBER; i2++)
            if (ms[i1][i2]!=0) ms[i1][i2]=1;
    for (i1=0; i1<generetion; i1++)
        ms[LINE_NUMBER][COLUMN_NUMBER]=next_generation (ms);
    fclose (f);
}
