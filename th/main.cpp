#include "stdafx.h"
#include "iostream"
#include "math.h"
#include "stdlib.h"
#include "locale.h"
#include "conio.h"
using namespace std;
const int n = 3;
bool converge(double*, double*, double);
int main()
{
    double start_time, end_time;
    start_time = omp_get_wtime();
    setlocale(LC_ALL, "rus");
    double a[n][n] = { { 2.39, -0.46, 1.08 },
                       { 0.54, 1.82, 0.73 },
                       { 1.18, 0.52, 2.95 } };
    double b[n] = { 4.13, 2.42, 1.48 };
    double x[n] = { 0, 0, 0 };
    double p[n] = { 0, 0, 0 };
    double eps = 0.001;
    /*
    Ход метода, где:
    a[n][n] - Матрица коэффициентов
    b[n] - Столбец правых частей
    x[n], p[n] - Текущее и предыдущее решения
    */
    do
    {
        for (int i = 0; i < n; i++)
            p[i] = x[i];

        for (int i = 0; i < n; i++)
        {
            double var = 0;
            for (int j = 0; j < i; j++)
                var += (a[i][j] * x[j]);
            for (int j = i + 1; j < n; j++)
                var += (a[i][j] * p[j]);
            x[i] = (b[i] - var) / a[i][i];
        }
    } while (!converge(x, p, eps));

    //Выводим решения
    cout << "Решение: " << endl;
    for (int i = 0; i<n; i++)
        cout << "x" << i << ": " << x[i] << endl;
    cout << endl;

    end_time = omp_get_wtime();
    printf("Time %lf\n", end_time - start_time);

    _getch();
    return 0;
}
bool converge(double *xk, double *xkp, double eps)
{
    double norm = 0;
    for (int i = 0; i < n; i++)
    {
        norm += (xk[i] - xkp[i])*(xk[i] - xkp[i]);
    }
    if (sqrt(norm) >= eps)
        return false;
    return true;
}