// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H


#define UNUSED(x) (void)(x)
#define LAMBDA(fun)  void (*fun)(float&, void *, int, int) = \
        [] (float& s, void * args, int i, int j)


#define UNUSED_LAMBDA() \
        UNUSED(args); \
        UNUSED(i); \
        UNUSED(j)


#include <ostream>
#include <fstream>
#include <iostream>
#include <string>


/**
 * @struct MatrixDims
 * @brief Matrix dimensions container
 */
typedef struct MatrixDims {
    int rows, cols;
} MatrixDims;

// Insert Matrix class here...




class Matrix {


private:
    int rows = 0;
    int cols = 0;

    float ** matrix = nullptr;


    void init(int rows, int cols);

    void init();

public:
    void forEach(void (*fun)(float &, void *, int, int), void *args);

    void freeMatrix();

    void ones();

    Matrix(int rows, int cols);

    Matrix();

    Matrix(const Matrix &other);

//    Matrix& copy( Matrix  &other);

    ~Matrix();

    int getRows() const;

    int getCols() const;

    Matrix &vectorize();

    void plainPrint();

    // Matrix& transpose( ) const;
    // matrixIter& iterator() const;

    Matrix &operator=(const Matrix &assignmented);

    Matrix &operator+(const Matrix &other);

    Matrix &operator+=(const Matrix &other);

    Matrix &operator*(const Matrix &other);

    Matrix &operator*(float scalar) const;

    float operator()(const int i, const int j) const;

    float operator[](const int i) const;

    friend int operator>>(std::ifstream &is, Matrix &matrix);
    //friend Digit MlpNetwork::operator()( Matrix&  matrix );
};

std::ostream &operator<<(std::ostream &os, Matrix &matrix);

Matrix &operator*(float scalar, const Matrix &other);

int operator>>(std::ifstream &is, Matrix &matrix);

#endif //MATRIX_H
