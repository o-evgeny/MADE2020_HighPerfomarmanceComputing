#include "matrix.h"
#include <iostream>
#include <chrono>

bool test(){

    const Matrix matr0(5,2);
    const Matrix matr0_a(5,2);
    if (matr0!=matr0_a) return false;
    if (!(matr0==matr0_a)) return false;


    Matrix matr1(6,5);
    if (matr1.Get_Columns()!=5) return false;
    if (matr1.Get_Rows()!=6) return false;

    Matrix matr2(3,2);
    Matrix matr3(3,2);

    int counter=0;
    for(int i=0; i<matr3.Get_Rows(); ++i) {
        for (int j = 0; j < matr3.Get_Columns(); ++j) {
            matr2[i][j] = counter;
            matr3[i][j] = counter;
            counter++;
        }
    }
    if (!(matr2==matr3))return false;
    if (matr2!=matr3) return false;
    matr2[2][1]=1000000;
    if (matr2==matr3)return false;

    int constant_=10;
    counter=0;
    matr3*=constant_;
    for(int i=0; i<matr3.Get_Rows(); ++i){
        for (int j=0; j<matr3.Get_Columns();++j){
            if (matr3[i][j]!=counter * constant_) return false;
            counter++;
        }
    }
    return true;
}

bool test_mult() {

    Matrix matr1(3,3);
    for(int i=0; i<matr1.Get_Rows(); ++i) {
        for (int j = 0; j < matr1.Get_Columns(); ++j) {
            matr1[i][j] = 1;
        }
    }

    Matrix matr2(3,3);
    for(int i=0; i<matr1.Get_Rows(); ++i) {
        for (int j = 0; j < matr1.Get_Columns(); ++j) {
            matr2[i][j] = 2;
        }
    }




    Matrix check1(3,3);
    check1[0][0]=6;
    check1[0][1]=6;
    check1[0][2]=6;
    check1[1][0]=6;
    check1[1][1]=6;
    check1[1][2]=6;
    check1[2][0]=6;
    check1[2][1]=6;
    check1[2][2]=6;

    Matrix matr3=matr1*matr2;

    assert(matr3==check1);

    Matrix matr_4(2,2);
    Matrix matr_5(2,2);
    Matrix matr_6(2,2);
    Matrix check2(2,2);


    matr_4[0][0]=1;
    matr_4[0][1]=2;
    matr_4[1][0]=3;
    matr_4[1][1]=4;

    matr_5[0][0]=(int) 5;
    matr_5[0][1]=(int) 6;
    matr_5[1][0]=(int) 7;
    matr_5[1][1]=(int) 8;

    check2[0][0]=19;
    check2[0][1]=22;
    check2[1][0]=43;
    check2[1][1]=50;

    matr_6=matr_4*matr_5;

    assert(matr_6==check2);

    return true;

}

Matrix generate_matrix(size_t m,size_t n){
    Matrix matr(m,n);
    for (int i=0; i<m; ++i){
        for (int j=0; j<n;++j){
            matr[i][j]=rand();
        }
    }
    return matr;
}

int main(int argc, char *argv[]) {


    switch (argc) {
        case 1: {
            const int sizes[4] = {512, 1024, 2048, 4096};
            for (int i = 0; i < 4; ++i) {
                Matrix m1 = generate_matrix(sizes[i], sizes[i]);
                Matrix m2 = generate_matrix(sizes[i], sizes[i]);

                auto begin = std::chrono::steady_clock::now();
                Matrix m3 = m1 * m2;
                auto end = std::chrono::steady_clock::now();
                auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
                std::cout << "The time for multiple " << sizes[i] << "X" << sizes[i] << " matrix: "
                          << elapsed_ms.count() << " ms\n";

            }
            break;
        }

        case 2:
            if (!strcmp(argv[1], "test")) {
                if (test_mult() == true) std::cout << "Tests PASSED" << std::endl;
                else std::cout << "Tests: FAILED" << std::endl;
                break;
            }
            break;
    }


}