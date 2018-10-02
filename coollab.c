//created by Natalia

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const float pi = 3.14159;
const int NPoints = 10;

void ReadData(double Un[], double Unk[], double k[], int numb[]);
double decriment (double  b, double c, double k);
double dobrotnost (double decr);
void ResultFile(double decr[], double dobr[],int numb[]);

int main()
{
    printf (" LABA 3.2.5 \n \n");
    printf (" Data is in the file 'laba.txt' \n");
    printf (" Results is in the file 'results.txt' \n");

    double Un[10] = {0};
    double Unk[10] = {0};
    double k[10] = {0};
    double decr[10] = {0};
    double dobr[10] = {0};
    int numb[1] = {0};

    ReadData(Un, Unk, k, numb);
    for (int i = 0; i < numb[0]; i ++)
    {
        decr[i] = decriment(Un[i], Unk[i], k[i]);
        dobr[i] = dobrotnost(decr[i]);
    }
    ResultFile(decr, dobr, numb);

    return 0;
}

void ReadData(double Un[], double Unk[], double k[], int numb[])
{
    FILE* f1 = fopen("laba.txt", "r");

    if (f1 == NULL)
    {
        printf("Cannot open file");
        return;
    }

    int line = 0;
    while (1)
    {
        int res = fscanf(f1, "%lg %lg %lg", &Un[line], &Unk[line], &k[line]);
        if (res == EOF) break;
        line++;
    }
    fclose(f1);
    numb [0] = line;
}

void ResultFile(double decr[], double dobr[],int numb[])
{
    FILE* f2 = fopen("results.txt", "w");

    fprintf(f2,"decriment   dobrotnost\n");
    for(int i = 0; i < numb[0]; i++)
    {
        fprintf(f2,"%lg   %lg\n", decr[i], dobr[i]);
    }
    fclose(f2);
}

double decriment (double  b, double c, double k)
{
  if((k == 0) || (c == 0))
    printf("Error in decr!\n");
  float a = (1/k) * log(b/c);

  return a;
}

double dobrotnost (double decr)
{
  if(decr == 0)
    printf("Error in dobr!\n");
   float a = pi/decr;

  return a;
}
