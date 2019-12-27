#ifndef ACTIVATION_H
#define ACTIVATION_H
#include "Matrix.h"
/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    Relu,
    Softmax
};
/**
 * Activation, represent the Activation layer.
 */
class Activation
{
private:
    /**
     * reluFun, implementaion of the relu activation.
     * @param matrix, the given matrix.
     * @return the matrix after applay
     *  the relu function on each cell.
     */
    Matrix& _reluFun(Matrix &matrix);
    /**
     * Softmax, implementaion of the Softmax activation.
     * @param matrix, the given matrix.
     * @return the matrix after applay
     *  the Softmax function on each cell.
     */
    Matrix& _softmaxFun(Matrix &matrix);
    /**
     * the type of this spacific object, can be
     * ethior Relu or Softmax.
     * @param activationType [description]
     */
    ActivationType activationType;
public:
    /**
    * constructor, saving the type of the function,
     * @param activationType the type of the function.
     */
    Activation(ActivationType activationType);
    /**
     * apllay's the function on given matrix.
     * @return the new matrix after that the function
     * has been applayed on each cell.
     */
    Matrix &operator()(Matrix &);
    /**
     * getActivationType, returns the type of the
     * function.
     * @return the type of the function.
     */
    ActivationType getActivationType() const;

};

#endif
