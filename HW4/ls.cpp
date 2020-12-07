#include <stdio.h>
#include <chrono>
#define Threads_Num 8
int main(){

    unsigned seeds [Threads_Num];
    for (int i=0; i<Threads_Num;++i){
        auto t = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());
        auto value = t.time_since_epoch();
        int now = value.count();
        unsigned int seedq = now * i;
        seeds[i]=seedq;
    }
}