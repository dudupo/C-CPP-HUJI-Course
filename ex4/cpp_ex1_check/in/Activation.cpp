#ifndef LAMBDA

#define UNUSED(x) (void)(x)
#define LAMBDA(fun)  void (*fun)(float&, void *, int, int) = \
        [] (float& s, void * args, int i, int j)


#define UNUSED_LAMBDA() \
        UNUSED(args); \
        UNUSED(i); \
        UNUSED(j)
#endif

#include "math.h"
#include "Activation.h"

const int ZERO = 0;
const float ZEROF = 0.f;
/**
 * reluFun, implementaion of the relu activation.
 * @param matrix, the given matrix.
 * @return the matrix after applay
 *  the relu function on each cell.
 */
Matrix& Activation::_reluFun(Matrix &matrix)
{
    LAMBDA(fun)
    {
        UNUSED_LAMBDA();

        if (s < ZERO)
        {
            s = ZERO;
        }
    };
    matrix._forEach(fun, nullptr);
    return matrix;
}
/**
 * Softmax, implementaion of the Softmax activation.
 * @param matrix, the given matrix.
 * @return the matrix after applay
 *  the Softmax function on each cell.
 */
Matrix& Activation::_softmaxFun(Matrix &matrix)
{

    LAMBDA(fun)
    {
        UNUSED_LAMBDA();
        s = expf(s);
        *((float *) args) = *((float *) args) + s;
    };

    float *args = new float(ZEROF);

    matrix._forEach(fun, (void *) args);

    LAMBDA(fun2)
    {
        UNUSED_LAMBDA();
        s = s / *((float *) args);
    };

    matrix._forEach(fun2, (void *) args);

    delete args;
    return matrix;
}
/**
* constructor, saving the type of the function,
 * @param activationType the type of the function.
 */
Activation::Activation(ActivationType activationType)
{
    this->activationType = activationType;
}
/**
 * apllay's the function on given matrix.
 * @return the new matrix after that the function
 * has been applayed on each cell.
 */
Matrix &Activation::operator()(Matrix &matrix)
{

    if (this->activationType == Relu)
    {
        return _reluFun(matrix);
    }
    else if (this->activationType == Softmax)
    {
        return _softmaxFun(matrix);
    }

    return matrix;
}
/**
 * getActivationType, returns the type of the
 * function.
 * @return the type of the function.
 */
ActivationType Activation::getActivationType() const
{
    return this->activationType;
}
