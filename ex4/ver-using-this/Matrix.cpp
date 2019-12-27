#include "Matrix.h"


const int ZERO = 0;
const int PAIR = 2;
const int ONE = 1;
const int FIRSTMATRIX = 0;
const int SECONEDMATRIX = 1;
const int SUCCESS = 1;
const float ZEROF = 0.f;
const float LOWERBOUD = 0.1f;
const char * DOUBLESTAR = "**";
const char * DOUBLESPACE = "  ";
const char * SPACE = " ";


/**
 * initialize the matrix, allocates the memory.
 * @param rows, the number of the rows of the matrix.
 * @param cols, the number of the columns of the matrix.
 */
void Matrix::_init(int rows, int cols)
{

        this->matrix = new float *[rows];
        for (int i = ZERO; i < rows; i++)
        {
                this->matrix[i] = new float[cols];
        }

        this->cols = cols;
        this->rows = rows;

        LAMBDA(fun)
        {
                UNUSED_LAMBDA();
                s = ZEROF;
        };

        this->_forEach(fun, nullptr);
}
/**
 * initialize the matrix, assuming that the rows,
 * and the columns have been set.
 */
void Matrix::_init()
{
        this->_init(this->getRows(), this->getCols());
}
/**
 * initialize the matrix, allocates the memory.
 * @param rows, the number of the rows of the matrix.
 * @param cols, the number of the columns of the matrix.
 */
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols)
{

        this->_init(rows, cols);

}
/**
 * initialize matrix with 1 cell.
 */
Matrix::Matrix() : Matrix(ONE, ONE)
{

}
/**
 * copy constructor.
 * @param other, reference to the matrix which will be copied.
 */
Matrix::Matrix(const Matrix &other) : Matrix(other.getRows(), other.getCols())
{

        LAMBDA(fun)
        {
                s = float((*(Matrix *) args)(i, j));
        };

        void *args = (void *) &other;
        this->_forEach(fun, args);
}
/**
 * relase the memory which occupied by the matrix.
 */
void Matrix::_freeMatrix()
{
        if (this->matrix != nullptr && *this->matrix != nullptr)
        {
                for (int i = ZERO; i < this->getRows(); i++)
                {
                        delete[] this->matrix[i];
                }
                delete [] this->matrix;
                this->matrix = nullptr;
        }
}
/**
 * destructor.
 */
Matrix::~Matrix()
{

}
/**
 * getting the nunber of the rows.
 * @return the rows.
 */
int Matrix::getRows() const
{
        return this->rows;
}
/**
 * getting  the nunber of the columns.
 * @return the columns.
 */
int Matrix::getCols() const
{
        return this->cols;
}
/**
 * transform the matrix to one-colmun vector.
 * @return the matrix.
 */
Matrix &Matrix::vectorize()
{
        float ** new_matrix = new float *[this->getRows() * this->getCols()];

        for (int i = ZERO; i < this->getRows() * this->getCols(); i++)
        {
                new_matrix[i] = new float[ONE];
                new_matrix[i][ZERO] = (*this)[i];
        }

        this->_freeMatrix();
        this->matrix = new_matrix;

        this->rows = this->getRows() * this->getCols();
        this->cols = ONE;

        return *this;
}
/**
 * move assignmente.
 * @return the matrix.
 */
Matrix &Matrix::operator=(const Matrix &assignmented)
{

        if (this != &assignmented)
        {
                this->_freeMatrix();
                this->matrix = assignmented.matrix;
                this->rows = assignmented.getRows();
                this->cols = assignmented.getCols();
        }
        return *this;
}
/**
 * summing a matrix pair.
 * @return the matrix.
 */
Matrix &Matrix::operator+(const Matrix &other)
{
        Matrix *ref = new Matrix(this->getRows(), this->getCols());

        LAMBDA(fun)
        {
                Matrix **ptr = (Matrix **) args;
                s = (*ptr[FIRSTMATRIX])(i, j) + (*ptr[SECONEDMATRIX])(i, j);
        };

        void *args[PAIR] = {(void *) this, (void *) &other};
        ref->_forEach(fun, args);
        return *ref;
}
/**
 * multiplate the matrix by other matrix.
 * @return the multiplation of the two matrix.
 */
Matrix &Matrix::operator+=(const Matrix &other)
{
        LAMBDA(fun)
        {
                Matrix *ptr = (Matrix *) args;
                s += (*ptr)(i, j);
        };
        void *args = (void *) &other;
        this->_forEach(fun, args);
        return *this;

}
/**
 * multiplate the matrix by scalr.
 * @return the result of the multiplationa.
 */
Matrix &Matrix::operator*(const Matrix &other)
{
        Matrix *ref = new Matrix(this->getRows(), other.getCols());


        LAMBDA(fun)
        {
                UNUSED_LAMBDA();
                Matrix **ptr = (Matrix **) args;

                for (int k = ZERO; k < (ptr[FIRSTMATRIX])->getCols(); k++)
                {
                        s += (*ptr[FIRSTMATRIX])(i, k) *
                         (*ptr[SECONEDMATRIX])(k, j);
                }
        };

        void *args[PAIR] = {(void *) this, (void *) &other};
        ref->_forEach(fun, args);
        return *ref;
}
/**
 * getting clousers.
 * @param i - the row of the cell.
 * @param j - the colmun of the cell.
 * @return reference to the cell content.
 */
Matrix &Matrix::operator*(float scalar) const
{
        Matrix *ref = new Matrix(*this);
        LAMBDA(fun)
        {
                UNUSED_LAMBDA();
                s *= (*(float *) args);
        };
        ref->_forEach(fun, (void *) &scalar);
        return *ref;
}
/**
 * pair_col_os, struct which contain a pair,
 * output stream, and the columns nuber, it's will
 * be given to the function which will print the matrix,
 * ( the function will call to lambda function so, the columns has
 * mast have been pass as arguments, while the '[&]' catching is the
 * nutrual defintion, its fail becuse other problems )
 */
typedef struct pair_col_os
{
        std::ostream *os;
        int cols;

} pair_col_os;
/**
 * prints the matrix.
 */
void Matrix::plainPrint()
{
        LAMBDA(fun)
        {
                UNUSED_LAMBDA();

                pair_col_os *ptr = (pair_col_os *) args;
                *(ptr->os) << s << SPACE;

                if (j + ONE == ptr->cols)
                {
                        *(ptr->os) << std::endl;
                }
        };

        pair_col_os *args =
                (pair_col_os *) malloc(sizeof(pair_col_os));

        args->os = &std::cout;
        args->cols = this->getCols();
        this->_forEach(fun, (void *) args);
        *(args->os) << std::endl;
        free(args);


}
/**
 *  printing the matrix in aligan format.
 *  each cell ehich greater than 0.1 will be printed as
 *  double star '**'.
 *  @param os the output stream to print into.
 *  @matrix the matrix which wil printed.
 */
std::ostream &operator<<(std::ostream &os, Matrix  &matrix)
{

        LAMBDA(fun)
        {
                UNUSED_LAMBDA();
                pair_col_os *ptr = (pair_col_os *) args;
                if (s >LOWERBOUD)
                {
                        *(ptr->os) << DOUBLESTAR;
                }
                else
                {
                        *(ptr->os) << DOUBLESPACE;
                }
                if (j + ONE == ptr->cols)
                {
                        *(ptr->os) << std::endl;
                }
        };


        pair_col_os *args =
                (pair_col_os *) malloc(sizeof(pair_col_os));

        args->os = &os;
        args->cols = matrix.getCols();

        matrix._forEach(fun, (void *) args);
        free(args);
        return os;
}
/**
 * getting clousers.
 * @param i - the row of the cell.
 * @param j - the colmun of the cell.
 * @return reference to the cell content.
 */
float& Matrix::operator()(const int i, const int j) const
{
        return this->matrix[i][j];
}
/**
 * getting cell by single address.
 * @param i the order of the cell by counting.
 * @return reference to the cell content.
 */
float& Matrix::operator[](const int i)  const
{
        return this->matrix[i / this->getCols()][i % this->getCols()];
}
/**
 *  multiplate a scalar with matrix while the scalar 'located'
 *  left to the matrix.
 */
Matrix& operator*(float scalar, const Matrix &other)
{
        return other * scalar;
}
/**
 * feeding the matrix from given file streamm.
 * @param is, input stream.
 * @param matrix, the matrix which the values will be inserted to.
 */
int operator>>(std::ifstream &is, Matrix &matrix)
{

        if ( *matrix.matrix == nullptr )
        {
                matrix._init();
        }

        for (int i = ZERO; i < matrix.getRows(); i++)
        {
                for (int j = ZERO; j < matrix.getCols(); j++)
                {
                        is.seekg(sizeof(float) * (i * matrix.getCols() + j));
                        is.read(reinterpret_cast<char *>(
                                        &matrix.matrix[i][j]), sizeof(float));

                }
        }

        return SUCCESS;
}
/**
 * _forEach, applay's the given function on each cell
 * @param fun, the given function, accepting a void * args,
 * as parameters in addition to the cell indexs, and his
 * content.
 */
void Matrix::_forEach(void (*fun)(float &, void *, int, int), void *args)
{
        for (int i = ZERO; i < this->getRows(); i++)
        {
                for (int j = ZERO; j < this->getCols(); j++)
                {
                        fun(this->matrix[i][j], args, i, j);
                }
        }
}
