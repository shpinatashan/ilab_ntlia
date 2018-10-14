//created by Natalia

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double Tolerance = 3e-8;
const double MinValue = 0.0;
const double MaxValue = 100.0;
const int NPoints = 10;


void ReadData(double Un[], double Unk[], double k[], int numb[]);
double Measurement_Error(double Un[], int numb[]);
double decriment (double  b, double c, double k);
double quality (double decr);
void ResultFile(double decr[], double arr_quality[],int numb[]);

int main()
{
    printf (" LABA 3.2.5 \n \n");
    printf (" Data is in the file 'laba.txt' \n");
    printf (" Results is in the file 'results.txt' \n");

    double Un[10] = {0};
    double Unk[10] = {0};
    double k[10] = {0};
    double decr[10] = {0};
    double arr_quality[10] = {0};
    int numb[1] = {0};

    ReadData(Un, Unk, k, numb);
    for (int i = 0; i < numb[0]; i ++)
    {
        decr[i] = decriment(Un[i], Unk[i], k[i]);
        arr_quality[i] = quality(decr[i]);
    }
    ResultFile(decr, arr_quality, numb);
    double errrUn = Measurement_Error( Un, numb);
    printf("\nUn measurement error: ");
    printf("%lg\n", errrUn);

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

double Measurement_Error(double Un[], int numb[])
{
    double sum1 = 0;
    double sum2 = 0;
    for (int i = 0; i < numb[0]; i++)
    {
        sum1 = sum1 + Un[i];
    }
    double   average = sum1/numb[0];
    for (int k = 0; k < numb[0]-1; k++)
    {

      sum2 = sum2 + ((Un[k] - average) * (Un[k] - average));
    }
    double err = sqrt (sum2 / (numb[0] * (numb[0] - 1)));
    return err;
}

void ResultFile(double decr[], double arr_quality[],int numb[])
{
    FILE* f2 = fopen("results.txt", "w");

    fprintf(f2,"decriment   quality\n");
    for(int i = 0; i < numb[0]; i++)
    {
        fprintf(f2,"%lg   %lg\n", decr[i], arr_quality[i]);
    }
    fclose(f2);
}

double decriment (double  b, double c, double k)
{

        if (k > MinValue - Tolerance && k < MaxValue - Tolerance)
    {
        if (k > 0.0 - Tolerance && k < 0.0 + Tolerance)
        {
           printf("Error in decr!\n");
        }
    }


        if (c > MinValue - Tolerance && c < MaxValue - Tolerance)
    {
        if (c > 0.0 - Tolerance && c < 0.0 + Tolerance)
        {
           printf("Error in decr!\n");
        }
    }

    float a = (1/k) * log(b/c);

    return a;
}

double quality (double decr)
{
        if (decr > MinValue - Tolerance && decr < MaxValue - Tolerance)
    {
        if (decr > 0.0 - Tolerance && decr < 0.0 + Tolerance)
        {
           printf("Error in quality!\n");
        }
    }
    float a = M_PI/decr;

    return a;
}
