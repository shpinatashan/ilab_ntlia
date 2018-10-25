//created by Natalia

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double Tolerance = 3e-8;
const double MinValue = 0.0;
const double MaxValue = 100.0;
const int NPoints = 10;

int check(double* ptr);
void ReadData(double Un[], double Unk[], double k[], int numb[]);
double Measurement_Error(double Un[], int numb[]);
void Error(double value);
double decriment (double  b, double c, double k);
double quality (double decr);
void ResultFile(double decr[], double arr_quality[],int numb[]);
void MyFree(double** arr);


int main()
{
    printf (" LABA 3.2.5 \n \n");
    printf (" Data is in the file 'laba.txt' \n");
    printf (" Results is in the file 'results.txt' \n");

    double* Un   = (double*)calloc(10, sizeof(double));
    double* Unk  = (double*)calloc(10, sizeof(double));
    double* k    = (double*)calloc(10, sizeof(double));
    double* decr = (double*)calloc(10, sizeof(double));
    double* arr_quality = (double*)calloc(10, sizeof(double));
    int numb[1] = {0};

    check(Un);
    check(Unk);
    check(k);
    check(decr);
    check(arr_quality);

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

    MyFree(&Un);
    MyFree(&Unk);
    MyFree(&k);
    MyFree(&decr);
    MyFree(&arr_quality);

    return 0;
}

int check(double* ptr)
{
    if (ptr == NULL)
     {
        printf ("error in calloc");
        return -1;
     }
}

void ReadData(double Un[], double Unk[], double k[], int numb[])
{
    printf("the name of the data file: ");
    char fname[20] = {};
    scanf("%s",fname);
    FILE* f1 = fopen(fname, "r");

    if (f1 == NULL)
    {
        printf("Cannot open datafile");
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
    printf("the name of the results file: ");
    char fname[20] = {};
    scanf("%s",fname);
    FILE* f2 = fopen(fname, "w");
    if (f2 == NULL)
    {
        printf("Cannot open resfile");
        return;
    }

    fprintf(f2,"decriment   quality\n");
    for(int i = 0; i < numb[0]; i++)
    {
        fprintf(f2,"%lg   %lg\n", decr[i], arr_quality[i]);
    }
    fclose(f2);
}

double decriment (double  b, double c, double k)
{

    Error(k);
    Error(c);
    float a = (1/k) * log(b/c);

    return a;
}

double quality (double decr)
{
    Error(decr);
    float a = M_PI/decr;

    return a;
}

void Error(double value)
{

    if (value > MinValue - Tolerance && value < MaxValue - Tolerance)
    {
        if (value > 0.0 - Tolerance && value < 0.0 + Tolerance)
        {
            printf("Error!");
        }
    }
}

void MyFree(double** arr)
{
    free(*arr);
    *arr = NULL;
}
