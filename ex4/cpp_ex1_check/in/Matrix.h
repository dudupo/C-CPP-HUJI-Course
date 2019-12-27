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
typedef struct MatrixDims
{
        int rows, cols;
} MatrixDims;

// Insert Matrix class here...

typedef class Matrix Matrix;
typedef class MlpNetwork MlpNetwork;
typedef class Activation Activation;
typedef class Dense Dense;

/**
 * The matrix class, implementes the mathematicl object.
 */
class Matrix
{
private:
        int rows = 0;
        int cols = 0;
        float ** matrix = nullptr;
        /**
         * initialize the matrix, allocates the memory.
         * @param rows, the number of the rows of the matrix.
         * @param cols, the number of the columns of the matrix.
         */
        void _init(int rows, int cols);
        /**
         * initialize the matrix, assuming that the rows,
         * and the columns have been set.
         */
        void _init();
        /**
         * forEach, applay's the given function on each cell
         * @param fun, the given function, accepting a void * args,
         * as parameters in addition to the cell indexs, and his
         * content.
         */
        void _forEach(void (*fun)(float &, void *, int, int), void *args);
        /**
         * relase the memory which occupied by the matrix.
         */
        void _freeMatrix();
        friend class MlpNetwork;
        friend class Activation;
        friend class Dense;
        friend int operator>>(std::ifstream &is, Matrix &matrix);
        friend std::ostream &operator<<(std::ostream &os, Matrix &matrix);
        friend Matrix& operator*(const Matrix&, const Matrix&);
        friend Matrix& operator+(const Matrix&, const Matrix&);

public:
        /**
         * initialize the matrix, allocates the memory.
         * @param rows, the number of the rows of the matrix.
         * @param cols, the number of the columns of the matrix.
         */
        Matrix(int rows, int cols);
        /**
         * initialize matrix with 1 cell.
         */
        Matrix();
        /**
         * copy constructor.
         * @param other, reference to the matrix which will be copied.
         */
        Matrix(const Matrix &other);
        /**
         * destructor.
         */
        ~Matrix();
        /**
         * getting the nunber of the rows.
         * @return the rows.
         */
        int getRows() const;
        /**
         * getting  the nunber of the columns.
         * @return the columns.
         */
        int getCols() const;
        /**
         * transform the matrix to one-colmun vector.
         * @return the matrix.
         */
        Matrix &vectorize();
        /**
         * prints the matrix.
         */
        void plainPrint() const;
        /**
         * move assignmente.
         * @return the matrix.
         */
        Matrix& operator=(const Matrix &assignmented);

        /**
         * add other matrix to the matrix and assignmente.
         * @return this matrix.
         */
        Matrix& operator+=(const Matrix &other);

        /**
         * multiplate the matrix by scalr.
         * @return the result of the multiplationa.
         */
        Matrix& operator*(float scalar) const;
        /**
         * getting clousers.
         * @param i - the row of the cell.
         * @param j - the colmun of the cell.
         * @return reference to the cell content.
         */
        float& operator()(const int i, const int j) const;
        /**
         * getting cell by single address.
         * @param i the order of the cell by counting.
         * @return reference to the cell content.
         */
        float& operator[] (const int i) const;


};
/**
 *  printing the matrix in aligan format.
 *  each cell ehich greater than 0.1 will be printed as
 *  double star '**'.
 *  @param os the output stream to print into.
 *  @matrix the matrix which wil printed.
 */
std::ostream &operator<<(std::ostream &os, Matrix &matrix);
/**
 *  multiplate a scalar with matrix while the scalar 'located'
 *  left to the matrix.
 */
Matrix &operator*(float scalar, const Matrix &other);
/**
 * feeding the matrix from given file streamm.
 * @param is, input stream.
 * @param matrix, the matrix which the values will be inserted to.
 */
int operator>>(std::ifstream &is, Matrix &matrix);

/**
 * multiplate the matrix by other matrix.
 * @return the multiplation of the two matrix.
 */
Matrix& operator*(const Matrix&, const Matrix&);

/**
 * summing a matrix pair.
 * @return the matrix.
 */
Matrix& operator+(const Matrix&, const Matrix&);

#endif //MATRIX_H
