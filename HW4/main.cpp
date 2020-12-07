
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <random>
#include <vector>

#include <Eigen/Dense>

Eigen::Matrix<typename MatT::Scalar, MatT::ColsAtCompileTime, MatT::RowsAtCompileTime>
pseudoinverse(const MatT &mat, typename MatT::Scalar tolerance = typename MatT::Scalar{1e-4}) // choose appropriately
{
    typedef typename MatT::Scalar Scalar;
    auto svd = mat.jacobiSvd(Eigen::ComputeFullU | Eigen::ComputeFullV);
    const auto &singularValues = svd.singularValues();
    Eigen::Matrix<Scalar, MatT::ColsAtCompileTime, MatT::RowsAtCompileTime> singularValuesInv(mat.cols(), mat.rows());
    singularValuesInv.setZero();
    for (unsigned int i = 0; i < singularValues.size(); ++i) {
        if (singularValues(i) > tolerance)
        {
            singularValuesInv(i, i) = Scalar{1} / singularValues(i);
        }
        else
        {
            singularValuesInv(i, i) = Scalar{0};
        }
    }
    return svd.matrixV() * singularValuesInv * svd.matrixU().adjoint();
}


const int n=5;
const int m=5;
const int steps=10000;
const double lr=0.001;

const int maxValue=100;
const int bMax=10;
const int noiseMax=5;

double** getData(const int n, const int m){
    double arr[n][m];
    double noise[n];
    double b[n];
    for (int i=0; i<n; ++i){
        noise[i]=rand()%noiseMax;
        b[i]=rand()%bMax;
        for (int j=0; j<m; ++j){
            arr[i][j]=rand()%maxValue;
        }
    }

}

int main(){
//y=Xb+noise

    double arr[n][m];
    double noise[n];
    double b[n];
    double y[n];
    for (int i=0; i<n; ++i){
        noise[i]=rand()%noiseMax;
        b[i]=rand()%bMax;
        for (int j=0; j<m; ++j){
            arr[i][j]=rand()%maxValue;
        }
    }

}