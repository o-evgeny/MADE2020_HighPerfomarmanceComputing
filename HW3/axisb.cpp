#include <iostream>
#include <cmath>
#include <omp.h>

const int n = 1000;//размер матрицы коэффиицентов n x n
double eps=0.000000001;//точность решений


bool bias(double* , double* , int n, double eps);//функция подсчета значения ошибки(отклонения)
double gs_omp();//время вычислений в параллельном режиме
double gs();//время вычислений в последовательном режиме


int main()
{
    double gs_time=gs();
    double gs_omp_time=gs_omp();

    std::cout<<"gs time: "<<gs()<<" ms"<<std::endl;
    omp_set_num_threads(1);
    std::cout<<"gs_omp time with 1 thread(s): "<<gs_omp()<<" ms"<<std::endl;
    omp_set_num_threads(2);
    std::cout<<"gs_omp time with 2 thread(s): "<<gs_omp()<<" ms"<<std::endl;
    omp_set_num_threads(3);
    std::cout<<"gs_omp time with 3 thread(s): "<<gs_omp()<<" ms"<<std::endl;
    omp_set_num_threads(4);
    std::cout<<"gs_omp time with 4 thread(s): "<<gs_omp()<<" ms"<<std::endl;
    omp_set_num_threads(8);
    std::cout<<"gs_omp time with 8 thread(s): "<<gs_omp()<<" ms"<<std::endl;

}

bool bias(double* cur, double* prev, int n, double eps)
{
    double norm = 0;

    for (int i = 0; i < n; i++)
        norm += (cur[i] - prev[i]) * (cur[i] - prev[i]);
    return (sqrt(norm) < eps);
}


double gs_omp(){

    double start_time, end_time;
    double a[n][n];//матрица коэффициентов
    double b[n];//вектор-столбец b (n+1)
    double cur[n];//вектор текущих значений
    double prev[n];//вектор предыдущих значений

//Генерация матрица с диагональным преобладанием(пример)
    for (int i=0;i<n;++i){
        for (int j=0; j<n;++j){
            if (i==j)
            {a[i][j]=n;}
            else
            {a[i][j]=1;}
        }
        b[i]=i;
        cur[i]=0;
        prev[i]=0;
    }

//заполним случайным начальным значением, например нулем
    for (int i = 0; i < n; i++)
        cur[i] = 0;

    start_time = omp_get_wtime();
    do {
        double t = 0;
        for (int i = 0; i < n; i++)
            prev[i] = cur[i];

//итерационный алгоритм Гаусса-Зейделя

#pragma omp parallel for private(t)
        for (int i = 0; i < n; i++) {
            t = 0;
            for (int j = 0; j < i; j++)
                t += (a[i][j] * cur[j]);
            for (int j = i + 1; j < n; j++)
                t += (a[i][j] * prev[j]);
            cur[i] = (b[i] - t) / a[i][i];
        }
    }
    while (!bias(cur, prev, n, eps));

    end_time = omp_get_wtime();
    return (end_time - start_time);

}





double gs(){

    double start_time, end_time;
    double a[n][n];//матрица коэффициентов
    double b[n];//вектор-столбец b (n+1)
    double cur[n];//вектор текущих значений
    double prev[n];//вектор предыдущих значений

//Генерация матрица с диагональным преобладанием(пример)
    for (int i=0;i<n;++i){
        for (int j=0; j<n;++j){
            if (i==j)
            {a[i][j]=n;}
            else
            {a[i][j]=1;}
        }
        b[i]=i;
        cur[i]=0;
        prev[i]=0;
    }

//заполним случайным начальным значением, например нулем
    for (int i = 0; i < n; i++)
        cur[i] = 0;

    start_time = omp_get_wtime();
    do {
        double t = 0;
        for (int i = 0; i < n; i++)
            prev[i] = cur[i];

//итерационный алгоритм Гаусса-Зейделя

        for (int i = 0; i < n; i++) {
            t = 0;
            for (int j = 0; j < i; j++)
                t += (a[i][j] * cur[j]);
            for (int j = i + 1; j < n; j++)
                t += (a[i][j] * prev[j]);
            cur[i] = (b[i] - t) / a[i][i];
        }
    }
    while (!bias(cur, prev, n, eps));

    end_time = omp_get_wtime();
    return(end_time - start_time);

}
