#include <iostream>
#include <random>
#include <omp.h>
#include <stdlib.h>
#include <chrono>
#define Threads_Num 8

int main()
{

    const unsigned N = 1000000000  ;
    const unsigned side  = 1000  ;
    int cnt = 0;

    unsigned tid,t;

unsigned seeds [Threads_Num];
for (int i=0; i<Threads_Num;++i){
    auto t = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());
    auto value = t.time_since_epoch();
    int now = value.count();
    unsigned int seedq = now * i;
    seeds[i]=seedq;
}



omp_set_num_threads(8);
#pragma omp parallel for reduction(+:cnt)
    for(unsigned i = 0; i < N;  ++i)
    {   tid=omp_get_thread_num();

        unsigned x = rand_r(&seeds[tid])%side;
      unsigned  y = rand_r(&seeds[tid])%side;

       if ( x*x + y*y  < side*side) {cnt+=1;}


    }

    printf("%f", 4.*cnt/N);
}