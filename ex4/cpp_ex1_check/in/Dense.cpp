#include "Dense.h"

/**
 * Dense constructor
 * @param w              the weights matrix.
 * @param bias           the bias matrix.
 * @param activationType the type of the activation function
 */
Dense::Dense(Matrix &w, Matrix &bias,
             ActivationType activationType) : w(w),  bias(bias),
             activation(activationType)
{

}
/**
 * getWeights returns a reffernce to the matrix weights.
 * @return a reffernce to the matrix weights.
 */
Matrix &Dense::getWeights()
{
        return this->w;
}
/**
 * getBias returns a reffernce to the matrix biases.
 * @return a reffernce to the matrix biases.
 */
Matrix &Dense::getBias()
{
        return this->bias;
}
/**
 * getActivation returns a reffernce to the activation function
 * @return a reffernce to the activation function.
 */
Activation &Dense::getActivation()
{
        return this->activation;
}
/**
 * operator() calculate the layer step on the given matrix.
 * @return [description]
 */
Matrix &Dense::operator()(Matrix &matrix)
{

        Matrix& ref  = (this->w * matrix) += this->bias;
        Matrix& ret  = *(new Matrix(this->activation(   ref)));
        ref._freeMatrix();
        delete &ref;
        matrix = ret;
        delete &ret;
        return matrix;
}
