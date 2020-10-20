#include <stdio.h>
#include <iostream>


class Matrix {
    int *matr;
    size_t rows;
    size_t columns;
    size_t matr_size;
public:
    Matrix(size_t rows_, size_t columns_) ;
    int Get_Rows() const { return rows; };
    int Get_Columns() const { return columns; };

    class Proxy {
        Matrix &matrix;
        size_t row;
    public:
        Proxy(Matrix &matrix_, size_t row_) : matrix(matrix_), row(row_) {}
        int &operator[](size_t);
    };

    class Proxy4Const{
        const Matrix &matrix;
        size_t row;
    public:
        Proxy4Const(const Matrix &matrix_, size_t row_ ) :matrix(matrix_), row(row_) {}
        const int &operator[](size_t) const ;
    };

    Proxy operator[](size_t row) { return Proxy{*this, row}; }
    const Proxy4Const operator[](size_t row) const { return Proxy4Const{*this, row}; }
    bool operator!=(Matrix&) const;
    bool operator!=(const Matrix&) const;
    bool operator==(const Matrix&) const;
    Matrix& operator*=(int);
    Matrix operator*(Matrix& m) const;

};