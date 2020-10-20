
#include "matrix.h"


Matrix::Matrix(size_t rows_, size_t columns_):rows(rows_),columns(columns_) {
    matr_size=rows*columns;
    matr = new int[matr_size];
    std::memset(matr,0,sizeof(int)*matr_size);
}

int &Matrix::Proxy::operator[](size_t column) {
    if (row >= matrix.rows || column >= matrix.columns)
        throw std::out_of_range("");
    else{
        return matrix.matr[row*matrix.columns + column];}
}


const int &Matrix::Proxy4Const::operator[](size_t column)  const {
    if (row >= matrix.rows || column >= matrix.columns)
        throw std::out_of_range("");
    else{
        return matrix.matr[row*matrix.columns + column];}
}

bool Matrix::operator!=( Matrix &r) const {
    return !(*this == r);
}


Matrix& Matrix::operator*=(int r)  {
    for (int i = 0; i < matr_size; ++i)
        matr[i] *= r;

    return *this;
}


bool Matrix::operator!=(const Matrix& r) const{
    return !(*this == r);

}


bool Matrix::operator==(const Matrix& r) const{
    if (this == &r) {
        return true;
    }

    for (int i = 0; i < matr_size; i++) {
        if (matr[i] != r.matr[i]) {
            return false;
        }
    }
    return true;
}

Matrix Matrix::operator*(Matrix& mt) const
{
    if (columns != mt.Get_Rows())
        throw std::out_of_range("wrong size");

    Matrix mult(rows, mt.Get_Columns());

    for(int i = 0; i < mult.Get_Rows(); ++i) {
        for (int j = 0; j < mult.Get_Columns(); ++j) {
            for (int k = 0; k < columns; ++k) {
                mult[i][j] += matr[i * mult.Get_Rows() +  k] * mt[k][j];
                ///std::cout<<t<<" "<<l<<" "<<u<<" ";
            }
            ///std::cout<<std::endl;

        }
    }

    return mult;
}